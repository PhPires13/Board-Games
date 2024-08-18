//
// Created by Paulo Henrique Pires  on 17/08/24.
//

#include "doctest.h"
#include "exceptions.hpp"

#include <sstream>
#include <iostream>

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

    TEST_CASE("Play Match") {
        CHECK_NOTHROW(std::remove(Player::filePath.c_str())); // Delete test file if exists
        CHECK_NOTHROW(Player::syncDatabase());

        std::streambuf* cinbuf = std::cin.rdbuf();  // Store the original buffer

        // Create players for match
        const std::string game = "V";
        const std::string nick1 = "Nick1", name1 = "Name1";
        const std::string nick2 = "Nick2", name2 = "Name2";
        const std::string arguments1 = nick1 + " " + name1;
        const std::string arguments2 = nick2 + " " + name2;
        CHECK_NOTHROW(Manager::createPlayer(arguments1));
        CHECK_NOTHROW(Manager::createPlayer(arguments2));

        // ---------------- Play match
        // Complete a row, player 1 wins
        const std::istringstream input1("0 0\n1 0\n0 1\n1 1\n0 2\n"); // Custom input
        std::cin.rdbuf(input1.rdbuf()); // Asign it to std::cin
        CHECK_NOTHROW(Manager::playMatch(game + " " + nick1 + " " + nick2));
        // Complete a row, player 2 wins
        const std::istringstream input2("0 0\n1 0\n0 1\n1 1\n2 2\n1 2\n");
        std::cin.rdbuf(input2.rdbuf());
        CHECK_NOTHROW(Manager::playMatch(game + " " + nick1 + " " + nick2));

        // Restore std::cin to its original state
        std::cin.rdbuf(cinbuf);

        // Invalid game
        CHECK_THROWS_AS(Manager::playMatch("Z " + nick1 + " " + nick2), game_not_found);

        // Empty game
        // Will get the player first letter as game, this functionality helps to avoid game_not_found for missing space
        CHECK_THROWS_AS(Manager::playMatch(" " + nick1 + " " + nick2), player_not_found);

        // Invalid nick
        CHECK_THROWS_AS(Manager::playMatch(game + " " + nick1 + " Nick3"), player_not_found);
        CHECK_THROWS_AS(Manager::playMatch(game + " Nick3 " + nick2), player_not_found);
        CHECK_THROWS_AS(Manager::playMatch(game + " Nick3 Nick4"), player_not_found);

        // Empty nick
        CHECK_THROWS_AS(Manager::playMatch(game + " " + nick1 + " "), incorrect_format);
        CHECK_THROWS_AS(Manager::playMatch(game + " " + nick2), incorrect_format);
        CHECK_THROWS_AS(Manager::playMatch(game + " "), incorrect_format);

        // Duplicated player
        CHECK_THROWS_AS(Manager::playMatch(game + " " + nick1 + " " + nick1), duplicated_player);

        // Delete test file
        CHECK_NOTHROW(std::remove(Player::filePath.c_str()));
    }

    TEST_CASE("Menu") {
        CHECK_NOTHROW(std::remove(Player::filePath.c_str())); // Delete test file if exists
        CHECK_NOTHROW(Player::syncDatabase());

        std::streambuf* cinbuf = std::cin.rdbuf();  // Store the original buffer

        const std::string ent = " \n";
        const std::string game = "V";
        const std::string nick1 = "Nick1", name1 = "Name1";
        const std::string nick2 = "Nick2", name2 = "Name2";
        const std::string nick3 = "Nick3", name3 = "Name3";

        const std::string cj1 = "CJ " + nick1 + " " + name1 + ent;
        const std::string cj2 = "CJ " + nick2 + " " + name2 + ent;
        const std::string cj3 = "CJ " + nick3 + " " + name3 + ent;
        const std::string ep1 = "EP " + game + " " + nick1 + " " + nick2 + ent;
        const std::string tttGameP1 = "0 0\n1 0\n0 1\n1 1\n0 2\n";
        const std::string ep2 = "EP " + game + " " + nick1 + " " + nick2 + ent;
        const std::string tttGameP2 = "0 0\n1 0\n0 1\n1 1\n2 2\n1 2\n";
        const std::string lj = "LJ" + ent;
        const std::string ljA = "LJ A" + ent;
        const std::string ljN = "LJ N" + ent;
        const std::string rj3 = "RJ " + nick3 + ent;
        const std::string invalid = "ZS ddw d4" + ent;
        const std::string fs = "FS" + ent;

        const std::string input = cj1 + ent + cj2 + ent + cj3 + ent +
            ep1 + tttGameP1 + ent + ep2 + tttGameP2 + ent +
            lj + ent + ljA + ent + ljN + ent +
            rj3 + ent +
            invalid + ent +
            fs; // Custom input
        const std::istringstream ss(input);
        std::cin.rdbuf(ss.rdbuf()); // Asign it to std::cin

        CHECK_NOTHROW(Manager::menu());

        // Restore std::cin to its original state
        std::cin.rdbuf(cinbuf);

        // Delete test file
        CHECK_NOTHROW(std::remove(Player::filePath.c_str()));
    }
}