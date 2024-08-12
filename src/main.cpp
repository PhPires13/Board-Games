//
// Created by pires on 6/28/2024.
//

#include "BoardGame.hpp"
#include "Manager.hpp"
#include "Player.hpp"
#include "Reversi.hpp"
#include "TicTacToe.hpp"

int main(int argc, char* argv[]) {
    Player::syncDatabase();

    Manager::menu();

    return 0;
}
