//
// Created by pires on 6/28/2024.
//

#include "Manager.hpp"
#include "Player.hpp"

int main(int argc, char* argv[]) {
    Player::syncDatabase();

    Manager::menu();

    return 0;
}
