//
// Created by pedro-pires on 8/17/24.
//

#include "doctest.h"
#include "exceptions.hpp"

#include <sstream>
#include <iostream>

#define private public
#define protected public

#include "Reversi.hpp"
#include "Player.hpp"

#undef private
#undef protected

TEST_SUITE("Reversi") {
    TEST_CASE("Constructor") {
        const Player player1("Nick1", "Name1");
        const Player player2("Nick2", "Name2");

        // Constructor with default board size
        CHECK_NOTHROW(Reversi(player1, player2));

        // Constructor with valid board size (even number)
        CHECK_NOTHROW(Reversi(player1, player2, 8));

        // Constructor with invalid board size (odd number)
        CHECK_THROWS_AS(Reversi(player1, player2, 7), std::exception);

        // Constructor with minimum valid board size
        CHECK_NOTHROW(Reversi(player1, player2, Reversi::minimumBoardSize));
    }

    TEST_CASE("Is a valid size") {
        const Player player1("Nick1", "Name1");
        const Player player2("Nick2", "Name2");
        const Reversi game(player1, player2);

        CHECK(game.isAValidHeight(Reversi::minimumBoardSize - 1) == false);
        CHECK(game.isAValidHeight(Reversi::minimumBoardSize) == true);
        CHECK(game.isAValidHeight(Reversi::minimumBoardSize + 2) == true);
        CHECK(game.isAValidWidth(Reversi::minimumBoardSize - 1) == false);
        CHECK(game.isAValidWidth(Reversi::minimumBoardSize) == true);
        CHECK(game.isAValidWidth(Reversi::minimumBoardSize + 2) == true);
    }

    TEST_CASE("Validate Move") {
        const Player player1("Nick1", "Name1");
        const Player player2("Nick2", "Name2");

        Reversi game(player1, player2, Reversi::defaultBoardSize);

        // Valid moves
        CHECK_NOTHROW(game.validateMove({2, 3}));
        CHECK_NOTHROW(game.validateMove({4, 2}));

        // Size invalid
        CHECK_THROWS_AS(game.validateMove({}), incorrect_format);
        CHECK_THROWS_AS(game.validateMove({2}), incorrect_format);
        CHECK_THROWS_AS(game.validateMove({2, 3, 4}), incorrect_format);

        // Out of range
        CHECK_THROWS_AS(game.validateMove({Reversi::defaultBoardSize, 0}), invalid_move);
        CHECK_THROWS_AS(game.validateMove({0, Reversi::defaultBoardSize}), invalid_move);

        // Place is not empty
        game.makeMove({2, 3}, player1.getSymbol());
        CHECK_THROWS_AS(game.validateMove({2, 3}), invalid_move);
    }

    TEST_CASE("Get Game State") {
        const Player player1("Nick1", "Name1", 'X');
        const Player player2("Nick2", "Name2", 'O');

        // Standard moves, no winner
        Reversi game(player1, player2, Reversi::defaultBoardSize);
        game.makeMove({2, 3}, player1.getSymbol());
        game.makeMove({2, 2}, player2.getSymbol());
        CHECK(game.getGameState({2, 2}) == GameState::NOT_OVER);

        // Player 1 surrounds player 2's piece, flipping it
        game.makeMove({4, 2}, player1.getSymbol());
        CHECK(game.getGameState({4, 2}) == GameState::NOT_OVER);

        // Add more moves and check for a winner or tie
        // ... Additional moves leading to a game end state.
    }

    TEST_CASE("Flip Pieces") {
        const Player player1("Nick1", "Name1", 'X');
        const Player player2("Nick2", "Name2", 'O');
        Reversi game(player1, player2);

        // Make initial moves to set up a flipping scenario
        game.makeMove({2, 3}, player1.getSymbol());
        game.makeMove({2, 2}, player2.getSymbol());
        game.makeMove({4, 2}, player1.getSymbol());

        // Check that the pieces have been flipped correctly
        CHECK(game.getBoard().getSymbol(3, 2) == player1.getSymbol());
    }
}
