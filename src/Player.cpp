//
// Created by pedro-pires on 7/3/24.
//

#include "Player.hpp"

#include <cctype>
#include <fstream>
#include <ios>
#include <memory>
#include <utility>

#include "exceptions.hpp"
#include "Manager.hpp"

const std::string Player::filePath = "players.bin";

const uint32_t Player::firstValidSymbol = 33;
const char Player::lastValidSymbol = 126;

Player::Player(std::string _nick, std::string _name, const char symbol
    ): nick(std::move(_nick)), name(std::move(_name)), reversiWins(0), reversiLosses(0), lig4Wins(0), lig4Losses(0), tttWins(0), tttLosses(0) {

    // If the symbol is not valid and has been choosen
    if ((symbol < firstValidSymbol || symbol > lastValidSymbol) && symbol != 0)
        throw incorrect_data();

    this->symbol = symbol;
}

std::string Player::getNick() const {
    return this->nick;
}

std::string Player::getName() const {
    return this->name;
}

char Player::getSymbol() const {
    return this->symbol;
}

void Player::setSymbol(const char symbol) {
    this->symbol = symbol;
}

uint32_t Player::getWins(const char game) const {
    uint32_t wins = 0 ;

    if (game == Game::REVERSI)
        wins = this->reversiWins;
    else if (game == Game::LIG4)
        wins = this->lig4Wins;
    else if (game == Game::TTT)
        wins = this->tttWins;

    return wins;
}

uint32_t Player::getLosses(const char game) const {
    uint32_t losses = 0;

    if (game == Game::LIG4)
        losses = this->lig4Losses;
    else if (game == Game::REVERSI)
        losses = this->reversiLosses;
    else if (game == Game::TTT)
        losses = this->tttLosses;

    return losses;
}

void Player::addStats(const char game, const bool toAddWin, const bool toAddLoss) {
    if (toAddWin) {
        if (game == Game::LIG4)
            this->lig4Wins++;
        else if (game == Game::REVERSI)
            this->reversiWins++;
        else if (game == Game::TTT)
            this->tttWins++;
    } else if (toAddLoss) {
        if (game == Game::LIG4)
            this->lig4Losses++;
        else if (game == Game::REVERSI)
            this->reversiLosses++;
        else if (game == Game::TTT)
            this->tttLosses++;
    }
}

void Player::serialize(std::ofstream& outputFile) const {
    const size_t nickSize = nick.size();
    const size_t nameSize = name.size();

    outputFile.write(reinterpret_cast<const char*>(&nickSize), sizeof(nickSize));
    outputFile.write(nick.c_str(), nickSize);

    outputFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
    outputFile.write(name.c_str(), nameSize);

    outputFile.write(reinterpret_cast<const char*>(&symbol), sizeof(symbol));
    outputFile.write(reinterpret_cast<const char*>(&reversiWins), sizeof(reversiWins));
    outputFile.write(reinterpret_cast<const char*>(&reversiLosses), sizeof(reversiLosses));
    outputFile.write(reinterpret_cast<const char*>(&lig4Wins), sizeof(lig4Wins));
    outputFile.write(reinterpret_cast<const char*>(&lig4Losses), sizeof(lig4Losses));
    outputFile.write(reinterpret_cast<const char*>(&tttWins), sizeof(tttWins));
    outputFile.write(reinterpret_cast<const char*>(&tttLosses), sizeof(tttLosses));
}

void Player::deserialize(std::ifstream& inputFile) {
    size_t nickSize;
    size_t nameSize;

    inputFile.read(reinterpret_cast<char*>(&nickSize), sizeof(nickSize));
    nick.resize(nickSize);
    inputFile.read(&nick[0], nickSize);

    inputFile.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
    name.resize(nameSize);
    inputFile.read(&name[0], nameSize);

    inputFile.read(reinterpret_cast<char*>(&symbol), sizeof(symbol));
    inputFile.read(reinterpret_cast<char*>(&reversiWins), sizeof(reversiWins));
    inputFile.read(reinterpret_cast<char*>(&reversiLosses), sizeof(reversiLosses));
    inputFile.read(reinterpret_cast<char*>(&lig4Wins), sizeof(lig4Wins));
    inputFile.read(reinterpret_cast<char*>(&lig4Losses), sizeof(lig4Losses));
    inputFile.read(reinterpret_cast<char*>(&tttWins), sizeof(tttWins));
    inputFile.read(reinterpret_cast<char*>(&tttLosses), sizeof(tttLosses));
}

void Player::createPlayer(const std::string& nick, const std::string& name, const char symbol) {
    // Check if player is not duplicated
    bool duplicated = true;
    try {
        Player::loadPlayer(nick);
    } catch (const std::exception& e) {
        // If the player is not found, it is not duplicated
        duplicated = false;
    }

    if (duplicated) throw duplicated_player();

    // Create the player
    const Player newPlayer(nick, name, symbol);

    std::ofstream file(Player::filePath, std::ios::binary | std::ios::app);
    if (!file) throw file_error();

    newPlayer.serialize(file);

    file.close();
}

Player Player::loadPlayer(const std::string& nick) {
    std::ifstream file(Player::filePath, std::ios::binary);
    if (!file) throw file_error();

    Player iterPlayer("", "");
    bool found = false;
    while (file.peek() != EOF) {
        iterPlayer.deserialize(file);
        if (iterPlayer.getNick() == nick) {
            found = true;
            break;
        }
    }

    file.close();

    if (!found) throw player_not_found();

    return iterPlayer;
}

void Player::updatePlayerStats(const std::string& nick, const char game, const bool toAddWin, const bool toAddLoss) {
    const std::string tempFilePath = "temp.bin";

    // Get all players with the edition
    std::list<Player> players;

    std::ifstream oldFile(Player::filePath, std::ios::binary);
    if (!oldFile) throw file_error();

    Player iterPlayer("", "");
    bool found = false;
    while (oldFile.peek() != EOF) {
        iterPlayer.deserialize(oldFile);
        if (iterPlayer.getNick() == nick) {
            found = true;
            iterPlayer.addStats(game, toAddWin, toAddLoss);
        }

        players.push_back(iterPlayer);
    }

    oldFile.close();

    if (!found) throw player_not_found();

    // Pass all the players with edition to the new file
    std::ofstream newFile(tempFilePath, std::ios::binary);
    if (!newFile) throw file_error();

    for (const Player &player : players) {
        player.serialize(newFile);
    }

    newFile.close();

    // Exchange the files
    if (std::remove(Player::filePath.c_str())) throw file_error();

    if (std::rename(tempFilePath.c_str(), Player::filePath.c_str())) throw file_error();
}

void Player::updatePlayerInfo(const std::string& nick, const std::string& name, const char symbol) {
    // TODO: validar juntamente com player sem simbolo padrao
}


void Player::deletePlayer(const std::string& nick) {
    const std::string tempFilePath = "temp.bin";

    // Get all the remaining players
    std::list<Player> remainingPlayers;

    std::ifstream oldFile(Player::filePath, std::ios::binary);
    if (!oldFile) throw file_error();

    Player iterPlayer("", "");
    bool found = false;
    while (oldFile.peek() != EOF) {
        iterPlayer.deserialize(oldFile);
        if (iterPlayer.getNick() != nick)
            remainingPlayers.push_back(iterPlayer);
        else
            found = true;
    }

    oldFile.close();

    if (!found) throw player_not_found();

    // Pass the remaining players to the new file
    std::ofstream newFile(tempFilePath, std::ios::binary);
    if (!newFile) throw file_error();

    for (const Player &remainingPlayer : remainingPlayers) {
        remainingPlayer.serialize(newFile);
    }

    newFile.close();

    // Exchange the files
    if (std::remove(Player::filePath.c_str())) throw file_error();

    if (std::rename(tempFilePath.c_str(), Player::filePath.c_str())) throw file_error();
}

std::list<Player> Player::getAllPlayers() {
    std::list<Player> players;

    std::ifstream file(Player::filePath, std::ios::binary);
    if (!file) throw file_error();

    Player iterPlayer("", "");
    while (file.peek() != EOF) {
        iterPlayer.deserialize(file);
        players.push_back(iterPlayer);
    }

    file.close();

    return players;
}

bool Player::compareByNick(const Player& player1, const Player& player2) {
    return player1.getNick() < player2.getNick();
}

bool Player::compareByName(const Player& player1, const Player& player2) {
    return player1.getName() < player2.getName();
}

void Player::syncDatabase() {
    std::ofstream file(Player::filePath, std::ios::binary | std::ios::app);
    if (!file) throw file_error();
    file.close();
}