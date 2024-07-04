//
// Created by pedro-pires on 7/3/24.
//

#include "Player.hpp"

Player::Player(
    const std::string _nick, const std::string _name, const uint _wins, const uint _losses
    ): nick(_nick), name(_name), wins(_wins), losses(_losses) {
    this->symbol = ' ';
}

std::string Player::getNick() const {
    return this->nick;
}

std::string Player::getName() const {
    return this->name;
}

uint Player::getWins() const {
    return this->wins;
}

uint Player::getLosses() const {
    return this->losses;
}

void Player::addWin() {
    this->wins++;
}

void Player::addLoss() {
    this->losses++;
}

void Player::setSymbol(const char symbol) {
    this->symbol = symbol;
}

char Player::getSymbol() const {
    return this->symbol;
}

int Player::createPlayer(const std::string _nick, const std::string _name) {
    // TODO: Implementar
    return 0;
}

Player Player::loadPlayer(const std::string nick) {
    // TODO: Implementar
    return Player("", "");
}

int Player::updatePlayer(const std::string nick, const bool toAddWin, const bool toAddLoss, const std::string name) {
    // TODO: Implementar
    return 0;
}

int Player::deletePlayer(const std::string nick) {
    // TODO: Implementar
    return 0;
}

std::list<Player> Player::loadAllPlayers() {
    // TODO: Implementar
    return std::list<Player>();
}