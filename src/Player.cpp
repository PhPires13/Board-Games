//
// Created by pedro-pires on 7/3/24.
//

#include "Player.hpp"

#include <cctype>
#include <fstream>
#include <ios>
#include <memory>

#include "exceptions.hpp"
#include "Manager.hpp"

Player::Player(const std::string& _nick, std::string _name, const char symbol, const uint32_t _reversiWins, const uint32_t _reversiLosses,
               const uint32_t _lig4Wins, const uint32_t _lig4Losses, const uint32_t _tttWins, const uint32_t _tttLosses
): nick(_nick), name(std::move(_name)), reversiWins(_reversiWins), reversiLosses(_reversiLosses),
   lig4Wins(_lig4Wins), lig4Losses(_lig4Losses), tttWins(_tttWins), tttLosses(_tttLosses) {

    // If the symbol is not valid or hasnt't been choosen
    if (symbol < firstValidSymbol || symbol > lastValidSymbol)
        // the symbol will be the first letter of the nickname
        this->symbol = static_cast<char>(std::toupper(_nick[0]));
    else
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

void Player::setFilePath(const std::string& filePath) {
    Player::filePath = filePath;
}

void Player::createPlayer(const std::string& nick, const std::string& name, const char symbol) {
    // Check if player is not duplicated
    bool duplicated = true;
    try {
        Player::loadPlayer(nick);
    } catch (player_not_found&) {
        // If the player is not found, it is not duplicated
        duplicated = false;
    }

    if (duplicated) throw duplicated_player();

    // Create the player
    const Player newPlayer(nick, name, symbol);

    std::ofstream file(Player::filePath, std::ios::binary | std::ios::app);
    if (!file) throw file_error();

    file.write(reinterpret_cast<const char*>(&newPlayer), sizeof(Player));

    file.close();
}

Player Player::loadPlayer(const std::string& nick) {
    std::ifstream file(Player::filePath, std::ios::binary);
    if (!file) throw file_error();

    std::unique_ptr<Player> iterPlayer;
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&iterPlayer), sizeof(Player))) {
        if (iterPlayer->getNick() == nick) {
            found = true;
            break;
        }
    }

    file.close();

    if (!found) throw player_not_found();

    return *iterPlayer;
}

void Player::updatePlayerStats(const std::string& nick, const char game, const bool toAddWin, const bool toAddLoss) {
    const std::string tempFilePath = "temp.bin";

    // Get all players with the edition
    std::list<Player> players;

    std::ifstream oldFile(Player::filePath, std::ios::binary);
    if (!oldFile) throw file_error();

    std::unique_ptr<Player> iterPlayer;
    bool found = false;
    while (oldFile.read(reinterpret_cast<char*>(&iterPlayer), sizeof(Player))) {
        if (iterPlayer->getNick() == nick) {
            found = true;
            iterPlayer->addStats(game, toAddWin, toAddLoss);
        }

        players.push_back(*iterPlayer);
    }

    oldFile.close();

    if (!found) throw player_not_found();

    // Pass all the players with edition to the new file
    std::ofstream newFile(tempFilePath, std::ios::binary);
    if (!newFile) throw file_error();

    for (const Player &player : players) {
        newFile.write(reinterpret_cast<const char*>(&player), sizeof(Player));
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

    std::unique_ptr<Player> iterPlayer;
    bool found = false;
    while (oldFile.read(reinterpret_cast<char*>(&iterPlayer), sizeof(Player))) {
        if (iterPlayer->getNick() != nick)
            remainingPlayers.push_back(*iterPlayer);
        else
            found = true;
    }

    oldFile.close();

    if (!found) throw player_not_found();

    // Pass the remaining players to the new file
    std::ofstream newFile(tempFilePath, std::ios::binary);
    if (!newFile) throw file_error();

    for (const Player &remainingPlayer : remainingPlayers) {
        newFile.write(reinterpret_cast<const char*>(&remainingPlayer), sizeof(Player));
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

    std::unique_ptr<Player> iterPlayer;
    while (file.read(reinterpret_cast<char*>(&iterPlayer), sizeof(Player))) {
        players.push_back(*iterPlayer);
    }

    file.close();

    return players;
}