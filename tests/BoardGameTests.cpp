//
// Created by Pedro Henrique Pires  on 04/07/24.
//

#include "doctest.h"
#include "exceptions.hpp"

#define private public
#define protected public

#include "BoardGame.hpp"
#include "Player.hpp"

#undef private
#undef protected

TEST_SUITE("BoardGame") {
    TEST_CASE("Constructor") {
        // Player has no symbol
        const Player player1("Nick1", "Name1");
        const Player player2("Nick2", "Name2");
        const BoardGame boardGame1(player1, player2);
        CHECK(boardGame1.player1.getSymbol() != player1.getSymbol());
        CHECK(boardGame1.player2.getSymbol() != player2.getSymbol());

        // Players have the same symbol
        const Player player3("Nick3", "Name3", 'X');
        const Player player4("Nick4", "Name4", 'X');
        const BoardGame boardGame2(player3, player4);
        CHECK(boardGame2.player1.getSymbol() != boardGame2.player2.getSymbol());

        // Players are fine with their symbols
        const Player player5("Nick5", "Name5", 'X');
        const Player player6("Nick6", "Name6", 'O');
        const BoardGame boardGame3(player5, player6);
        CHECK(boardGame3.player1.getSymbol() == player5.getSymbol());
        CHECK(boardGame3.player2.getSymbol() == player6.getSymbol());
    }

    TEST_CASE("Is a valid size") {
        const Player player1("Nick1", "Name1");
        const Player player2("Nick2", "Name2");
        const BoardGame boardGame(player1, player2);
        CHECK(boardGame.isAValidHeight(0) == false);
        CHECK(boardGame.isAValidHeight(1) == true);
        CHECK(boardGame.isAValidWidth(0) == false);
        CHECK(boardGame.isAValidWidth(1) == true);
    }

    TEST_CASE("Print Board") {
        const Player player1("Nick1", "Name1");
        const Player player2("Nick2", "Name2");
        const BoardGame boardGame(player1, player2);
        CHECK_NOTHROW(boardGame.printBoard());
    }

    TEST_CASE("Validate Move") {
        constexpr int height = 7, width = 5;

        Player player1("Nick1", "Name1");
        Player player2("Nick2", "Name2");

        BoardGame boardGame(player1, player2, height, width);

        // Valid moves
        CHECK_NOTHROW(boardGame.validateMove({0}));
        CHECK_NOTHROW(boardGame.validateMove({width-1}));
        CHECK_NOTHROW(boardGame.validateMove({0, 0}));
        CHECK_NOTHROW(boardGame.validateMove({0, width-1}));
        CHECK_NOTHROW(boardGame.validateMove({height-1, 0}));
        CHECK_NOTHROW(boardGame.validateMove({height-1, width-1}));

        // Negative values are not possible since its uint

        CHECK_NOTHROW(boardGame.validateMove({0}));

        // Size invalid
        CHECK_THROWS_AS(boardGame.validateMove({}), incorrect_format);
        CHECK_THROWS_AS(boardGame.validateMove({0, 0, 0}), incorrect_format);

        // Out of range
        CHECK_THROWS_AS(boardGame.validateMove({width}), invalid_move);
        CHECK_THROWS_AS(boardGame.validateMove({height, 0}), invalid_move);
        CHECK_THROWS_AS(boardGame.validateMove({0, width}), invalid_move);
        CHECK_THROWS_AS(boardGame.validateMove({height, width}), invalid_move);
    }

    TEST_CASE("Make Move") {
        constexpr int height = 7, width = 5;

        Player player1("Nick1", "Name1");
        Player player2("Nick2", "Name2");

        BoardGame boardGame(player1, player2, height, width);

        // Valid moves
        CHECK_NOTHROW(boardGame.makeMove({0}, 'X'));
        CHECK_NOTHROW(boardGame.makeMove({0, 0}, 'C'));

        // Further tst is not necessary, since makeMove just calls board.placeSymbol that already has its own tests
    }

    TEST_CASE("Get game state") {
        constexpr int height = 7, width = 5;
        BoardGame boardGame(Player("Nick1", "Name1"), Player("Nick2", "Name2"), height, width);
        for (uint32_t i =0; i < height; i++) {
            for (uint32_t j = 0; j < width; j++) {
                boardGame.makeMove({j}, 'X');
                if (i != height-1 || j != width-1) CHECK(boardGame.getGameState({}) == GameState::NOT_OVER);
            }
        }
        CHECK(boardGame.getGameState({}) == GameState::TIE);
    }

    TEST_CASE("Whose Turn") {
        Player player1("Nick1", "Name1");
        Player player2("Nick2", "Name2");

        BoardGame boardGame(player1, player2);

        // Turn 0 does not exists
        boardGame.turn++;
        CHECK(boardGame.whoseTurn().getNick() == player1.getNick());
        boardGame.turn++;
        CHECK(boardGame.whoseTurn().getNick() == player2.getNick());
        boardGame.turn++;
        CHECK(boardGame.whoseTurn().getNick() == player1.getNick());
        boardGame.turn++;
        CHECK(boardGame.whoseTurn().getNick() == player2.getNick());
    }
}