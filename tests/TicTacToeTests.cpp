//
// Created by Paulo Henrique Pires  on 17/08/24.
//

#include "doctest.h"
#include "exceptions.hpp"

#include <sstream>
#include <iostream>

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

    TEST_CASE("Get Game State") {
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

        // Complete diagonal, player 1 wins
        TicTacToe ttt5(player1, player2);
        ttt5.makeMove({0, 0}, player1.getSymbol());
        ttt5.makeMove({0, 1}, player2.getSymbol());
        ttt5.makeMove({1, 1}, player1.getSymbol());
        CHECK(ttt5.getGameState({1, 1}) == GameState::NOT_OVER);
        ttt5.makeMove({1, 0}, player2.getSymbol());
        ttt5.makeMove({2, 2}, player1.getSymbol());
        CHECK(ttt5.getGameState({2, 2}) == GameState::PLAYER1_WINS);

        // Complete diagonal, player 2 wins
        TicTacToe ttt6(player1, player2);
        ttt6.makeMove({0, 1}, player1.getSymbol());
        ttt6.makeMove({0, 0}, player2.getSymbol());
        ttt6.makeMove({1, 0}, player1.getSymbol());
        CHECK(ttt6.getGameState({1, 0}) == GameState::NOT_OVER);
        ttt6.makeMove({1, 1}, player2.getSymbol());
        ttt6.makeMove({2, 0}, player1.getSymbol());
        ttt6.makeMove({2, 2}, player2.getSymbol());
        CHECK(ttt6.getGameState({2, 2}) == GameState::PLAYER2_WINS);

        // Complete sub-diagonal, player 1 wins
        TicTacToe ttt7(player1, player2);
        ttt7.makeMove({0, 2}, player1.getSymbol());
        ttt7.makeMove({0, 1}, player2.getSymbol());
        ttt7.makeMove({1, 1}, player1.getSymbol());
        CHECK(ttt7.getGameState({1, 1}) == GameState::NOT_OVER);
        ttt7.makeMove({1, 0}, player2.getSymbol());
        ttt7.makeMove({2, 0}, player1.getSymbol());
        CHECK(ttt7.getGameState({2, 0}) == GameState::PLAYER1_WINS);

        // Complete sub-diagonal, player 2 wins
        TicTacToe ttt8(player1, player2);
        ttt8.makeMove({0, 1}, player1.getSymbol());
        ttt8.makeMove({0, 2}, player2.getSymbol());
        ttt8.makeMove({1, 0}, player1.getSymbol());
        CHECK(ttt8.getGameState({1, 0}) == GameState::NOT_OVER);
        ttt8.makeMove({1, 1}, player2.getSymbol());
        ttt8.makeMove({2, 2}, player1.getSymbol());
        ttt8.makeMove({2, 0}, player2.getSymbol());
        CHECK(ttt8.getGameState({2, 0}) == GameState::PLAYER2_WINS);

        // Tie
        TicTacToe ttt9(player1, player2);
        ttt9.makeMove({0, 0}, player1.getSymbol());
        ttt9.makeMove({0, 1}, player2.getSymbol());
        ttt9.makeMove({0, 2}, player1.getSymbol());
        ttt9.makeMove({1, 1}, player2.getSymbol());
        CHECK(ttt9.getGameState({1, 1}) == GameState::NOT_OVER);
        ttt9.makeMove({1, 0}, player1.getSymbol());
        ttt9.makeMove({1, 2}, player2.getSymbol());
        ttt9.makeMove({2, 1}, player1.getSymbol());
        ttt9.makeMove({2, 0}, player2.getSymbol());
        ttt9.makeMove({2, 2}, player1.getSymbol());
        CHECK(ttt9.getGameState({2, 2}) == GameState::TIE);
    }

    TEST_CASE("Play Game") {
        std::streambuf* cinbuf = std::cin.rdbuf();  // Store the original buffer

        const Player player1("Nick1", "Name1", 'X');
        const Player player2("Nick2", "Name2", 'O');

        // Complete a row, player 1 wins
        const std::istringstream input1("0 0\n1 0\n0 1\n1 1\n0 2\n\n"); // Custom input
        std::cin.rdbuf(input1.rdbuf()); // Asign it to std::cin
        TicTacToe ttt1(player1, player2);
        GameState gamteState;
        CHECK_NOTHROW(gamteState = ttt1.playGame());
        CHECK(gamteState == GameState::PLAYER1_WINS);

        // Complete a row, player 2 wins
        const std::istringstream input2("0 0\n1 0\n0 1\n1 1\n2 2\n1 2\n\n");
        std::cin.rdbuf(input2.rdbuf());
        TicTacToe ttt2(player1, player2);
        CHECK_NOTHROW(gamteState = ttt2.playGame());
        CHECK(gamteState == GameState::PLAYER2_WINS);

        // Complete a column, player 1 wins
        const std::istringstream input3("0 0\n0 1\n1 0\n1 1\n2 0\n\n");
        std::cin.rdbuf(input3.rdbuf());
        TicTacToe ttt3(player1, player2);
        CHECK_NOTHROW(gamteState = ttt3.playGame());
        CHECK(gamteState == GameState::PLAYER1_WINS);

        // Complete a column, player 2 wins
        const std::istringstream input4("0 0\n0 1\n1 0\n1 1\n0 2\n2 1\n\n");
        std::cin.rdbuf(input4.rdbuf());
        TicTacToe ttt4(player1, player2);
        CHECK_NOTHROW(gamteState = ttt4.playGame());
        CHECK(gamteState == GameState::PLAYER2_WINS);

        // Complete diagonal, player 1 wins
        const std::istringstream input5("0 0\n0 1\n1 1\n1 0\n2 2\n\n");
        std::cin.rdbuf(input5.rdbuf());
        TicTacToe ttt5(player1, player2);
        CHECK_NOTHROW(gamteState = ttt5.playGame());
        CHECK(gamteState == GameState::PLAYER1_WINS);

        // Complete diagonal, player 2 wins
        const std::istringstream input6("0 1\n0 0\n1 0\n1 1\n2 0\n2 2\n\n");
        std::cin.rdbuf(input6.rdbuf());
        TicTacToe ttt6(player1, player2);
        CHECK_NOTHROW(gamteState = ttt6.playGame());
        CHECK(gamteState == GameState::PLAYER2_WINS);

        // Complete sub-diagonal, player 1 wins
        const std::istringstream input7("0 2\n0 1\n1 1\n1 0\n2 0\n\n");
        std::cin.rdbuf(input7.rdbuf());
        TicTacToe ttt7(player1, player2);
        CHECK_NOTHROW(gamteState = ttt7.playGame());
        CHECK(gamteState == GameState::PLAYER1_WINS);

        // Complete sub-diagonal, player 2 wins
        const std::istringstream input8("0 1\n0 2\n1 0\n1 1\n2 2\n2 0\n\n");
        std::cin.rdbuf(input8.rdbuf());
        TicTacToe ttt8(player1, player2);
        CHECK_NOTHROW(gamteState = ttt8.playGame());
        CHECK(gamteState == GameState::PLAYER2_WINS);

        // Tie
        const std::istringstream input9("0 0\n0 1\n0 2\n1 1\n1 0\n1 2\n2 1\n2 0\n2 2\n\n");
        std::cin.rdbuf(input9.rdbuf());
        TicTacToe ttt9(player1, player2);
        CHECK_NOTHROW(gamteState = ttt9.playGame());
        CHECK(gamteState == GameState::TIE);

        // Player sends invalid move in the middle of the game
        // Complete a row, player 2 wins
        const std::istringstream input10("0 0\n1 0\na1 bc\n1 c\n0 1\n1 1\n2 2\nc 1\n1 2\n\n");
        std::cin.rdbuf(input10.rdbuf());
        TicTacToe ttt10(player1, player2);
        CHECK_NOTHROW(gamteState = ttt10.playGame());
        CHECK(gamteState == GameState::PLAYER2_WINS);

        // Tie
        const std::istringstream input11("0 0\n0 1\n  ola ola ssm  \n0 2\n1 1\n1 0\n  1  \t  2     \n2 1\n2 0\n2 2\n\n");
        std::cin.rdbuf(input11.rdbuf());
        TicTacToe ttt11(player1, player2);
        CHECK_NOTHROW(gamteState = ttt11.playGame());
        CHECK(gamteState == GameState::TIE);

        // Restore std::cin to its original state
        std::cin.rdbuf(cinbuf);
    }
}