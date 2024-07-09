//
// Created by pedro-pires on 7/3/24.
//

#include "Player.hpp"

Player::Player(
    const std::string& _nick, const std::string& _name, const std::unordered_map<char, uint>& _wins,
    const std::unordered_map<char, uint>& _losses
    ): nick(_nick), name(_name), wins(_wins), losses(_losses) {
    this->symbol = ' ';
}

std::string Player::getNick() const {
    return this->nick;
}

std::string Player::getName() const {
    return this->name;
}

std::unordered_map<char, uint> Player::getWins() const {
    return this->wins;
}

std::unordered_map<char, uint> Player::getLosses() const {
    return this->losses;
}

uint Player::getWins(const char game) const {
    return this->wins.at(game);
}

uint Player::getLosses(const char game) const {
    return this->losses.at(game);
}

void Player::addWin(const char game) {
    this->wins[game]++;
}

void Player::addLoss(const char game) {
    this->losses[game]++;
}

void Player::setSymbol(const char symbol) {
    this->symbol = symbol;
}

char Player::getSymbol() const {
    return this->symbol;
}

CreationStatus Player::createPlayer(const std::string& nick, const std::string& name) {
    // TODO: Implementar
    return CreationStatus::CREATED;
}

Player* Player::loadPlayer(const std::string& nick) {
    // TODO: Implementar
    return nullptr;
}

int Player::updatePlayer(const std::string& nick, const char game, const bool toAddWin, const bool toAddLoss, const std::string& name) {
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