//
// Created by Paulo Henrique Pires  on 17/08/24.
//

#include "doctest.h"
#include "exceptions.hpp"

#define private public
#define protected public

#include "Manager.hpp"

#undef private
#undef protected

TEST_SUITE("Manager") {
    TEST_CASE("Print menu") {
        CHECK_NOTHROW(Manager::printMenu());
    }

    TEST_CASE("Create Match") {
        // Correct game and attributes
        CHECK_NOTHROW(Manager::createMatch(Game::REVERSI, Player("Nick1", "Name1"), Player("Nick2", "Name2"), ""));
        CHECK_NOTHROW(Manager::createMatch(Game::CONNECT_FOUR, Player("Nick1", "Name1"), Player("Nick2", "Name2"), ""));
        CHECK_NOTHROW(Manager::createMatch(Game::TTT, Player("Nick1", "Name1"), Player("Nick2", "Name2"), ""));

        // Explicit size
        CHECK_NOTHROW(Manager::createMatch(Game::REVERSI, Player("Nick1", "Name1"), Player("Nick2", "Name2"), "10"));
        CHECK_NOTHROW(Manager::createMatch(Game::CONNECT_FOUR, Player("Nick1", "Name1"), Player("Nick2", "Name2"), "8 7"));
        CHECK_NOTHROW(Manager::createMatch(Game::TTT, Player("Nick1", "Name1"), Player("Nick2", "Name2"), "3 3"));

        // Invalid game
        CHECK_THROWS_AS(Manager::createMatch(0, Player("Nick1", "Name1"), Player("Nick2", "Name2"), ""), game_not_found);
    }

    TEST_CASE("CRUD Players") {
    }
}