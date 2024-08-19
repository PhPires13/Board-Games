//
// Created by Carlos Eduardo Machado on 17/08/24.
//

#include "doctest.h"
#include "exceptions.hpp"

#include <sstream>
#include <iostream>

#define private public
#define protected public

#include "ConnectFour.hpp"
#include "Player.hpp"

#undef private
#undef protected

TEST_SUITE("ConnectFour") {
    TEST_CASE("Constructor") {
        const Player player1("Nick1", "Name1");
        const Player player2("Nick2", "Name2");
        int BoardHeight, BoardWidth;

        //Constructor with no board dimension inputs
        CHECK_NOTHROW(ConnectFour(player1, player2));
        //Constructor with one valid board dimension input (Height)
        BoardHeight = 5;
        CHECK_NOTHROW(ConnectFour(player1,player2, BoardHeight));
        //Constructor with one non-valid boar dimension input (Height)
        BoardHeight = 1;
        CHECK_NOTHROW(ConnectFour(player1,player2, BoardHeight));
        //Constructor with two valid board dimension inputs (Height, Width)
        BoardHeight = BoardWidth = 5;
        CHECK_NOTHROW(ConnectFour(player1,player2, BoardHeight, BoardWidth));
        //Constructor with two non-valid board dimension inputs (Height, Width)
        BoardHeight = BoardWidth = 1;
        CHECK_NOTHROW(ConnectFour(player1,player2, BoardHeight, BoardWidth));
        //Constructor with one valid board dimension inputs (Height) and another invalid (Width)
        BoardHeight = 5;
        CHECK_NOTHROW(ConnectFour(player1,player2, BoardHeight, BoardWidth));
        //Constructor with one valid board dimension inputs (Width) and another invalid (Height)
        BoardHeight = 1;
        BoardWidth = 5;
        CHECK_NOTHROW(ConnectFour(player1,player2, BoardHeight, BoardWidth));
    }

    TEST_CASE("Validate Move") {
        const Player player1("Nick1", "Name1");
        const Player player2("Nick2", "Name2");

        ConnectFour cf(player1, player2, ConnectFour::defaultBoardHeight, ConnectFour::defaultBoardWidth);

        // Valid moves
        CHECK_NOTHROW(cf.validateMove({0}));
        CHECK_NOTHROW(cf.validateMove({ConnectFour::defaultBoardWidth-1}));

        // Size invalid
        CHECK_THROWS_AS(cf.validateMove({}), incorrect_format);
        CHECK_THROWS_AS(cf.validateMove({0, 0}), incorrect_format);
        CHECK_THROWS_AS(cf.validateMove({0, 0, 0}), incorrect_format);

        // Out of range
        CHECK_THROWS_AS(cf.validateMove({ConnectFour::defaultBoardWidth}), invalid_move);

        // Column is full
        for(int i=0;i<=5;i++) {
            if(i%2==0) cf.makeMove({1},'X');
            else cf.makeMove({1},'O');
        }
        CHECK_THROWS_AS(cf.validateMove({1}), invalid_move);
    }

    TEST_CASE("Get Game State") {
        const Player player1("Nick1", "Name1", 'X');
        const Player player2("Nick2", "Name2", 'O');

        // Complete Horizontal _
        ConnectFour cf1(player1, player2, ConnectFour::minimumBoardSize, ConnectFour::minimumBoardSize);
        cf1.makeMove({0}, player1.getSymbol());
        cf1.makeMove({0}, player2.getSymbol());
        cf1.makeMove({1}, player1.getSymbol());
        cf1.makeMove({1}, player2.getSymbol());
        cf1.makeMove({3}, player1.getSymbol());
        cf1.makeMove({3}, player2.getSymbol());
        CHECK(cf1.getGameState({3}) == GameState::NOT_OVER);
        // Completing the four by the middle
        cf1.makeMove({2}, player1.getSymbol());
        CHECK(cf1.getGameState({2}) == GameState::PLAYER1_WINS);

        // Complete Vertical |
        ConnectFour cf2(player1, player2);
        cf2.makeMove({0}, player1.getSymbol());
        cf2.makeMove({1}, player2.getSymbol());
        cf2.makeMove({0}, player1.getSymbol());
        cf2.makeMove({1}, player2.getSymbol());
        cf2.makeMove({0}, player1.getSymbol());
        cf2.makeMove({1}, player2.getSymbol());
        CHECK(cf1.getGameState({1}) == GameState::NOT_OVER);
        cf2.makeMove({0}, player1.getSymbol());
        CHECK(cf2.getGameState({0}) == GameState::PLAYER1_WINS);

        // Complete Positive Diagonal /
        ConnectFour cf3(player1, player2);
        cf3.makeMove({0}, player1.getSymbol());
        cf3.makeMove({1}, player2.getSymbol());
        cf3.makeMove({1}, player1.getSymbol());
        cf3.makeMove({2}, player2.getSymbol());
        cf3.makeMove({2}, player1.getSymbol());
        cf3.makeMove({3}, player2.getSymbol());
        cf3.makeMove({3}, player1.getSymbol());
        cf3.makeMove({3}, player2.getSymbol());
        cf3.makeMove({3}, player1.getSymbol());
        cf3.makeMove({0}, player2.getSymbol());
        CHECK(cf3.getGameState({0}) == GameState::NOT_OVER);
        // Completing the four by the middle
        cf3.makeMove({2}, player1.getSymbol());
        CHECK(cf3.getGameState({2}) == GameState::PLAYER1_WINS);

        // Complete Negative Diagonal \'
        ConnectFour cf4(player1, player2);
        cf4.makeMove({0}, player1.getSymbol());
        cf4.makeMove({3}, player2.getSymbol());
        cf4.makeMove({2}, player1.getSymbol());
        cf4.makeMove({2}, player2.getSymbol());
        cf4.makeMove({1}, player1.getSymbol());
        cf4.makeMove({1}, player2.getSymbol());
        cf4.makeMove({0}, player1.getSymbol());
        cf4.makeMove({0}, player2.getSymbol());
        cf4.makeMove({3}, player1.getSymbol());
        cf4.makeMove({0}, player2.getSymbol());
        cf4.makeMove({3}, player1.getSymbol());
        CHECK(cf4.getGameState({3}) == GameState::NOT_OVER);
        // Completing the four by the middle
        cf4.makeMove({1}, player2.getSymbol());
        CHECK(cf4.getGameState({1}) == GameState::PLAYER2_WINS);

        // Tie
        ConnectFour cf5(player1, player2);
        cf5.makeMove({0}, player1.getSymbol());
        cf5.makeMove({0}, player2.getSymbol());
        cf5.makeMove({0}, player1.getSymbol());
        cf5.makeMove({0}, player2.getSymbol());
        cf5.makeMove({1}, player1.getSymbol());
        cf5.makeMove({1}, player2.getSymbol());
        cf5.makeMove({1}, player1.getSymbol());
        cf5.makeMove({3}, player2.getSymbol());
        cf5.makeMove({3}, player1.getSymbol());
        cf5.makeMove({1}, player2.getSymbol());
        cf5.makeMove({2}, player1.getSymbol());
        cf5.makeMove({2}, player2.getSymbol());
        cf5.makeMove({2}, player1.getSymbol());
        cf5.makeMove({3}, player2.getSymbol());
        cf5.makeMove({2}, player1.getSymbol());
        CHECK(cf5.getGameState({2}) == GameState::NOT_OVER);
        cf5.makeMove({3}, player2.getSymbol());
        CHECK(cf4.getGameState({3}) == GameState::TIE);
    }

    TEST_CASE("Play Game") {
        //TODO: Finalize this test scenario
    }
}