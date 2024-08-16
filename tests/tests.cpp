//
// Created by Pedro Henrique Pires  on 04/07/24.
//

#define private public
#define protected public

#include "BoardGame.hpp"
#include "doctest.h"
#include "exceptions.hpp"
#include "Player.hpp"

#undef private
#undef protected

TEST_CASE("Test BoardGame::validateMove()") {
    Player player1("Nick1", "Name1");
    Player player2("Nick2", "Name2");

    BoardGame boardGame(player1, player2);

    CHECK_NOTHROW(boardGame.validateMove({0, 0}));
    CHECK_THROWS_AS(boardGame.validateMove({-1, 0}), invalid_move);
    CHECK_THROWS_AS(boardGame.validateMove({0, -1}), invalid_move);
    CHECK_THROWS_AS(boardGame.validateMove({-1, -1}), invalid_move);

    CHECK_NOTHROW(boardGame.validateMove({0}));
    CHECK_THROWS_AS(boardGame.validateMove({-1}), invalid_move);

    CHECK_THROWS_AS(boardGame.validateMove({}), incorrect_format);
    CHECK_THROWS_AS(boardGame.validateMove({0, 0, 0}), incorrect_format);
}

TEST_CASE("Test BoardGame::whoseTurn()") {
    Player player1("Nick1", "Name1", 'X');
    Player player2("Nick2", "Name2", 'O');

    BoardGame boardGame(player1, player2);

    CHECK(boardGame.whoseTurn().getSymbol() == player1.getSymbol());
    boardGame.turn++;
    CHECK(boardGame.whoseTurn().getSymbol() == player2.getSymbol());
    boardGame.turn++;
    CHECK(boardGame.whoseTurn().getSymbol() == player1.getSymbol());
    boardGame.turn++;
    CHECK(boardGame.whoseTurn().getSymbol() == player2.getSymbol());
}