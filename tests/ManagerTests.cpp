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
        // Sync file
        CHECK_NOTHROW(std::remove(Player::filePath.c_str())); // Delete test file if exists
        CHECK_NOTHROW(Player::syncDatabase());

        // Create player correct attributes with symbol
        const std::string nick = "Nick1", name = "Name1";
        constexpr char symbol = 'X';
        const std::string arguments = nick + " " + name + " " + symbol;
        CHECK_NOTHROW(Manager::createPlayer(arguments));

        // Validate player attributes
        Player recoveredPlayer("", "");
        CHECK_NOTHROW(recoveredPlayer = Player::loadPlayer(nick));
        CHECK(recoveredPlayer.getNick() == nick);
        CHECK(recoveredPlayer.getName() == name);
        CHECK(recoveredPlayer.getSymbol() == symbol);

        // Crate player correct attributes without symbol
        const std::string nick2 = "Nick2", name2 = "Name2";
        const std::string arguments2 = nick2 + " " + name2;
        CHECK_NOTHROW(Manager::createPlayer(arguments2));
        Player recoveredPlayer2("", "");
        CHECK_NOTHROW(recoveredPlayer2 = Player::loadPlayer(nick2));
        CHECK(recoveredPlayer2.getNick() == nick2);
        CHECK(recoveredPlayer2.getName() == name2);
        CHECK(recoveredPlayer2.getSymbol() == 0);

        // Create duplicate player
        CHECK_THROWS_AS(Manager::createPlayer(arguments), duplicated_player);

        // Create player incorrect attributes
        const std::string consequentSymbol = "f";
        const std::string nick3 = "Nick3", name3 = "Name3 3r r45"; // Will consider last character as symbol
        const std::string arguments3 = nick3 + " " + name3 + " " + consequentSymbol;
        CHECK_NOTHROW(Manager::createPlayer(arguments3));
        Player recoveredPlayer3("", "");
        CHECK_NOTHROW(recoveredPlayer3 = Player::loadPlayer(nick3));
        CHECK(recoveredPlayer3.getNick() == nick3);
        CHECK(recoveredPlayer3.getName() == name3);
        CHECK(recoveredPlayer3.getSymbol() == consequentSymbol[0]);

        // List player no order
        CHECK_NOTHROW(Manager::listPlayers(""));
        // List player by nick
        const std::string nickOrder = "A";
        CHECK_NOTHROW(Manager::listPlayers(nickOrder));
        // List player by name
        const std::string nameOrder = "N";
        CHECK_NOTHROW(Manager::listPlayers(nameOrder));
        // List player by unknown order
        const std::string unknownOrder = "Z";
        CHECK_NOTHROW(Manager::listPlayers(unknownOrder));

        // Create match
        CHECK_NOTHROW(Manager::createMatch(Game::REVERSI, recoveredPlayer, recoveredPlayer2, ""));
        CHECK_NOTHROW(Manager::createMatch(Game::CONNECT_FOUR, recoveredPlayer, recoveredPlayer2, ""));
        CHECK_NOTHROW(Manager::createMatch(Game::TTT, recoveredPlayer, recoveredPlayer2, ""));
        CHECK_NOTHROW(Manager::createMatch(Game::REVERSI, recoveredPlayer, recoveredPlayer2, "10"));
        CHECK_NOTHROW(Manager::createMatch(Game::CONNECT_FOUR, recoveredPlayer, recoveredPlayer2, "8 7"));
        CHECK_NOTHROW(Manager::createMatch(Game::TTT, recoveredPlayer, recoveredPlayer2, "4 5"));
        CHECK_THROWS_AS(Manager::createMatch('Z', recoveredPlayer, recoveredPlayer2, "4 5"), game_not_found);

        // Delete player
        CHECK_NOTHROW(Manager::deletePlayer(nick));
        CHECK_NOTHROW(Manager::deletePlayer(nick2));

        // Delete test file
        CHECK_NOTHROW(std::remove(Player::filePath.c_str()));
    }
}