//
// Created by Paulo Henrique Pires  on 17/08/24.
//

#include "doctest.h"
#include "exceptions.hpp"

#define private public
#define protected public

#include "TicTacToe.hpp"
#include "Player.hpp"

#undef private
#undef protected

TEST_SUITE("TicTacToe") {
    TEST_CASE("Constructor") {
        const Player player1("Nick1", "Name1");
        const Player player2("Nick2", "Name2");
        CHECK_NOTHROW(TicTacToe(player1, player2));
    }

    TEST_CASE("Validate Move") {
        const Player player1("Nick1", "Name1");
        const Player player2("Nick2", "Name2");

        TicTacToe ttt(player1, player2);

        // Valid moves
        CHECK_NOTHROW(ttt.validateMove({0, 0}));
        CHECK_NOTHROW(ttt.validateMove({0, TicTacToe::defaultBoardSize-1}));
        CHECK_NOTHROW(ttt.validateMove({TicTacToe::defaultBoardSize-1, 0}));
        CHECK_NOTHROW(ttt.validateMove({TicTacToe::defaultBoardSize-1, TicTacToe::defaultBoardSize-1}));

        // Size invalid
        CHECK_THROWS_AS(ttt.validateMove({}), incorrect_format);
        CHECK_THROWS_AS(ttt.validateMove({0}), incorrect_format);
        CHECK_THROWS_AS(ttt.validateMove({0, 0, 0}), incorrect_format);

        // Out of range
        CHECK_THROWS_AS(ttt.validateMove({TicTacToe::defaultBoardSize, 0}), invalid_move);
        CHECK_THROWS_AS(ttt.validateMove({0, TicTacToe::defaultBoardSize}), invalid_move);
        CHECK_THROWS_AS(ttt.validateMove({TicTacToe::defaultBoardSize, TicTacToe::defaultBoardSize}), invalid_move);

        // Place is not empty
        ttt.makeMove({0, 0}, 'X');
        CHECK_THROWS_AS(ttt.validateMove({0, 0}), invalid_move);
    }

    TEST_CASE("Get game state") {
        const Player player1("Nick1", "Name1", 'X');
        const Player player2("Nick2", "Name2", 'O');

        // Complete a row, player 1 wins
        TicTacToe ttt1(player1, player2);
        ttt1.makeMove({0, 0}, player1.getSymbol());
        ttt1.makeMove({1, 0}, player2.getSymbol());
        CHECK(ttt1.getGameState({1, 0}) == GameState::NOT_OVER);
        ttt1.makeMove({0, 1}, player1.getSymbol());
        ttt1.makeMove({1, 1}, player2.getSymbol());
        ttt1.makeMove({0, 2}, player1.getSymbol());
        CHECK(ttt1.getGameState({0, 2}) == GameState::PLAYER1_WINS);

        // Complete a row, player 2 wins
        TicTacToe ttt2(player1, player2);
        ttt2.makeMove({0, 0}, player1.getSymbol());
        ttt2.makeMove({1, 0}, player2.getSymbol());
        ttt2.makeMove({0, 1}, player1.getSymbol());
        CHECK(ttt2.getGameState({0, 0}) == GameState::NOT_OVER);
        ttt2.makeMove({1, 1}, player2.getSymbol());
        ttt2.makeMove({2, 2}, player1.getSymbol());
        ttt2.makeMove({1, 2}, player2.getSymbol());
        CHECK(ttt2.getGameState({1, 2}) == GameState::PLAYER2_WINS);

        // Complete a column, player 1 wins
        TicTacToe ttt3(player1, player2);
        ttt3.makeMove({0, 0}, player1.getSymbol());
        ttt3.makeMove({0, 1}, player2.getSymbol());
        ttt3.makeMove({1, 0}, player1.getSymbol());
        CHECK(ttt3.getGameState({1, 0}) == GameState::NOT_OVER);
        ttt3.makeMove({1, 1}, player2.getSymbol());
        ttt3.makeMove({2, 0}, player1.getSymbol());
        CHECK(ttt3.getGameState({2, 0}) == GameState::PLAYER1_WINS);

        // Complete a column, player 2 wins
        TicTacToe ttt4(player1, player2);
        ttt4.makeMove({0, 0}, player1.getSymbol());
        ttt4.makeMove({0, 1}, player2.getSymbol());
        ttt4.makeMove({1, 0}, player1.getSymbol());
        CHECK(ttt4.getGameState({1, 0}) == GameState::NOT_OVER);
        ttt4.makeMove({1, 1}, player2.getSymbol());
        ttt4.makeMove({0, 2}, player1.getSymbol());
        ttt4.makeMove({2, 1}, player2.getSymbol());
        CHECK(ttt4.getGameState({2, 1}) == GameState::PLAYER2_WINS);

        // Tie
        TicTacToe ttt5(player1, player2);
        ttt5.makeMove({0, 0}, player1.getSymbol());
        ttt5.makeMove({0, 1}, player2.getSymbol());
        ttt5.makeMove({0, 2}, player1.getSymbol());
        ttt5.makeMove({1, 1}, player2.getSymbol());
        CHECK(ttt5.getGameState({1, 1}) == GameState::NOT_OVER);
        ttt5.makeMove({1, 0}, player1.getSymbol());
        ttt5.makeMove({1, 2}, player2.getSymbol());
        ttt5.makeMove({2, 1}, player1.getSymbol());
        ttt5.makeMove({2, 0}, player2.getSymbol());
        ttt5.makeMove({2, 2}, player1.getSymbol());
        CHECK(ttt5.getGameState({2, 2}) == GameState::TIE);
    }
}