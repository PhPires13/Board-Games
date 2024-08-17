//
// Created by Paulo Henrique Pires  on 17/08/24.
//

#include "doctest.h"
#include "exceptions.hpp"

#define private public
#define protected public

#include "Manager.hpp"
#include "Player.hpp"

#undef private
#undef protected

TEST_SUITE("Player") {
    TEST_CASE("Constructor") {
        // Without symbol
        CHECK_NOTHROW(Player("Nick1", "Name1"));

        // With symbol
        CHECK_NOTHROW(Player("Nick2", "Name2", 'X'));

        // With invalid symbol
        CHECK_THROWS_AS(Player("Nick3", "Name3", Player::firstValidSymbol-1), incorrect_data);
        CHECK_THROWS_AS(Player("Nick3", "Name3", Player::lastValidSymbol+1), incorrect_data);
    }

    TEST_CASE("Getters/Setters Attributes") {
        const std::string nick = "Nick1", name = "Name1";
        constexpr char symbol = 'X';
        constexpr char newSymbol = 'O';
        Player player(nick, name, symbol);

        // Getters
        CHECK(player.getNick() == nick);
        CHECK(player.getName() == name);
        CHECK(player.getSymbol() == symbol);

        // Incorrect change symbol
        CHECK_THROWS_AS(player.setSymbol(Player::firstValidSymbol-1), incorrect_data);
        CHECK_THROWS_AS(player.setSymbol(Player::lastValidSymbol+1), incorrect_data);

        // Correct change symbol
        CHECK_NOTHROW(player.setSymbol(newSymbol));
        CHECK(player.getSymbol() == newSymbol);
    }

    TEST_CASE("Getters/Setters Stats") {
        Player player("Nick1", "Name1");

        // Get wins and losses
        CHECK(player.getWins(Game::REVERSI) == 0);
        CHECK(player.getWins(Game::CONNECT_FOUR) == 0);
        CHECK(player.getWins(Game::TTT) == 0);
        CHECK(player.getWins(0) == 0);
        CHECK(player.getLosses(Game::REVERSI) == 0);
        CHECK(player.getLosses(Game::CONNECT_FOUR) == 0);
        CHECK(player.getLosses(Game::TTT) == 0);
        CHECK(player.getLosses(0) == 0);

        // Add wins and losses
        CHECK_NOTHROW(player.addStats(Game::REVERSI, true, false));
        CHECK_NOTHROW(player.addStats(Game::REVERSI, true, false));
        CHECK_NOTHROW(player.addStats(Game::REVERSI, false, true));
        CHECK_NOTHROW(player.addStats(Game::CONNECT_FOUR, true, false));
        CHECK_NOTHROW(player.addStats(Game::CONNECT_FOUR, false, true));
        CHECK_NOTHROW(player.addStats(Game::CONNECT_FOUR, false, true));
        CHECK_NOTHROW(player.addStats(Game::TTT, true, false));
        CHECK_NOTHROW(player.addStats(Game::TTT, false, true));
        CHECK_NOTHROW(player.addStats(0, true, false));
        CHECK_NOTHROW(player.addStats(0, false, true));

        // Check additions
        CHECK(player.getWins(Game::REVERSI) == 2);
        CHECK(player.getWins(Game::CONNECT_FOUR) == 1);
        CHECK(player.getWins(Game::TTT) == 1);
        CHECK(player.getWins(0) == 0);
        CHECK(player.getLosses(Game::REVERSI) == 1);
        CHECK(player.getLosses(Game::CONNECT_FOUR) == 2);
        CHECK(player.getLosses(Game::TTT) == 1);
        CHECK(player.getLosses(0) == 0);
    }

    TEST_CASE("File Functions") {
        // Sync file
        CHECK_NOTHROW(std::remove(Player::filePath.c_str())); // Delete test file if exists
        CHECK_NOTHROW(Player::syncDatabase());

        // Create player
        const std::string nick = "Nick1", name = "Name1";
        constexpr char symbol = 'X';
        CHECK_NOTHROW(Player::createPlayer(nick, name, symbol));

        // Update player stats
        CHECK_NOTHROW(Player::updatePlayerStats(nick, Game::REVERSI, true, false));
        CHECK_NOTHROW(Player::updatePlayerStats(nick, Game::REVERSI, true, false));
        CHECK_NOTHROW(Player::updatePlayerStats(nick, Game::REVERSI, false, true));
        CHECK_NOTHROW(Player::updatePlayerStats(nick, Game::CONNECT_FOUR, true, false));
        CHECK_NOTHROW(Player::updatePlayerStats(nick, Game::CONNECT_FOUR, false, true));
        CHECK_NOTHROW(Player::updatePlayerStats(nick, Game::CONNECT_FOUR, false, true));
        CHECK_NOTHROW(Player::updatePlayerStats(nick, Game::TTT, true, false));
        CHECK_NOTHROW(Player::updatePlayerStats(nick, Game::TTT, false, true));
        CHECK_NOTHROW(Player::updatePlayerStats(nick, 0, true, false));
        CHECK_NOTHROW(Player::updatePlayerStats(nick, 0, false, true));

        // Load player
        Player recoveredPlayer("", "");
        CHECK_NOTHROW(recoveredPlayer = Player::loadPlayer(nick));
        CHECK(recoveredPlayer.getNick() == nick);
        CHECK(recoveredPlayer.getName() == name);
        CHECK(recoveredPlayer.getSymbol() == symbol);

        // Check stats
        CHECK(recoveredPlayer.getWins(Game::REVERSI) == 2);
        CHECK(recoveredPlayer.getWins(Game::CONNECT_FOUR) == 1);
        CHECK(recoveredPlayer.getWins(Game::TTT) == 1);
        CHECK(recoveredPlayer.getWins(0) == 0);
        CHECK(recoveredPlayer.getLosses(Game::REVERSI) == 1);
        CHECK(recoveredPlayer.getLosses(Game::CONNECT_FOUR) == 2);
        CHECK(recoveredPlayer.getLosses(Game::TTT) == 1);
        CHECK(recoveredPlayer.getLosses(0) == 0);

        // Create duplicate player
        const std::string nick2 = "Nick2";
        CHECK_THROWS_AS(Player::createPlayer(nick, nick2), duplicated_player);

        // Load non-existent player
        const std::string nick3 = "Nick3";
        CHECK_THROWS_AS(Player::loadPlayer(nick3), player_not_found);

        // Upddate non-existent player
        CHECK_THROWS_AS(Player::updatePlayerStats(nick3, Game::REVERSI, true, false), player_not_found);

        // Delete player
        CHECK_NOTHROW(Player::deletePlayer(nick));
        CHECK_THROWS_AS(Player::loadPlayer(nick), player_not_found);

        // Get all players
        CHECK_NOTHROW(Player::getAllPlayers());

        // Delete test file
        CHECK_NOTHROW(std::remove(Player::filePath.c_str()));
    }

    TEST_CASE("Compare Players") {
        const std::string greaterNick = "Anick", smallerNick = "Bnick";
        const std::string greaterName = "Aname", smallerName = "Bname";

        Player player1(greaterNick, smallerName);
        Player player2(smallerNick, greaterName);

        // Compare nick
        CHECK(Player::compareByNick(player1, player2));
        CHECK_FALSE(Player::compareByNick(player2, player1));

        // Compare name
        CHECK_FALSE(Player::compareByName(player1, player2));
        CHECK(Player::compareByName(player2, player1));
    }
}