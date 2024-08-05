//
// Created by pedro-pires on 7/4/24.
//

#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <string>

#include "BoardGame.hpp"
#include "Player.hpp"

enum Game {
    REVERSI = 'R',
    LIG4 = 'L',
    TTT = 'V'
};

class Manager {
    static const uint32_t maxCommandSize;

    static void printMenu();

    static void createPlayer(const std::string& arguments);

    static void deletePlayer(const std::string& arguments);

    static void listPlayers(const std::string& arguments);

    static BoardGame* createMatch(char game, const Player& player1, const Player& player2, const std::string& extraArguments);

    static void playMatch(const std::string& arguments);

public:
    static void menu();
};

#endif //MANAGER_HPP
