//
// Created by pedro-pires on 7/3/24.
//

#include "Player.hpp"

#include <cctype>

Player::Player(const std::string& _nick, std::string _name, const char symbol,
    const uint _reversiWins, const uint _reversiLosses, const uint _lig4Wins, const uint _lig4Losses
    ): nick(_nick), name(std::move(_name)), reversiWins(_reversiWins), reversiLosses(_reversiLosses), lig4Wins(_lig4Wins), lig4Losses(_lig4Losses) {
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

uint Player::getWins(const char game) const {
    if (game == 'L')
        return this->lig4Wins;

    if (game == 'R')
        return this->reversiWins;

    return 0;
}

uint Player::getLosses(const char game) const {
    if (game == 'L')
        return this->lig4Losses;

    if (game == 'R')
        return this->reversiLosses;

    return 0;
}

void Player::addWin(const char game) {
    if (game == 'L')
        this->lig4Wins++;
    else if (game == 'R')
        this->reversiWins++;
}

void Player::addLoss(const char game) {
    if (game == 'L')
        this->lig4Losses++;
    else if (game == 'R')
        this->reversiLosses++;
}

CreationStatus Player::createPlayer(const std::string& nick, const std::string& name, const char symbol) {
    // TODO: Implementar
    return CreationStatus::CREATED;
}

Player* Player::loadPlayer(const std::string& nick) {
    // TODO: Implementar
    return nullptr;
}

int Player::updatePlayer(const std::string& nick, const char game, const bool toAddWin, const bool toAddLoss,
    const std::string& name, const char symbol) {
    // TODO: Implementar
    return 0;
}

DeletionStatus Player::deletePlayer(const std::string& nick) {
    // TODO: Implementar
    return DeletionStatus::DELETED;
}

std::list<Player> Player::getAllPlayers() {
    // TODO: Implementar
    return std::list<Player>();
}