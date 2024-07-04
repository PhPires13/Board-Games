//
// Created by pedro-pires on 7/3/24.
//

#include "Player.hpp"

Player::Player(
    const std::string _nick, const std::string _name, const int _wins, const int _losses
    ): nick(_nick), name(_name), wins(_wins), losses(_losses) {
    this->symbol = ' ';
}

std::string Player::getNick() const {
    return this->nick;
}

std::string Player::getName() const {
    return this->name;
}

int Player::getWins() const {
    return this->wins;
}

int Player::getLosses() const {
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

bool Player::savePlayer(const Player& player) {
    // TODO: Implementar
    return true;
}

Player Player::loadPlayer(const std::string nick) {
    // TODO: Implementar
    return Player("", "");
}

bool Player::deletePlayer(const std::string nick) {
    // TODO: Implementar
    return true;
}

std::list<Player> Player::loadAllPlayers() {
    // TODO: Implementar
    return std::list<Player>();
}