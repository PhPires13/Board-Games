//
// Created by pedro-pires on 7/4/24.
//

#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <string>

#include "Player.hpp"

class BoardGame;

class Manager {
    std::string databasePath;

public:
    Manager(const std::string& _databasePath);

    static void printMenu();

    void createPlayer(const std::string& arguments) const;

    void deletePlayer(const std::string& arguments) const;

    void listPlayers(const std::string& arguments) const;

    BoardGame* createMatch(char game, const Player& player1, const Player& player2, const std::string& extraArguments) const;

    void playMatch(const std::string& arguments) const;

    void menu() const;
};

#endif //MANAGER_HPP
