//
// Created by Paulo Henrique Pires  on 16/08/24.
//

#include "doctest.h"
#include "exceptions.hpp"

#define private public
#define protected public

#include "Board.hpp"

#undef private
#undef protected

TEST_SUITE("Board") {
    TEST_CASE("Constructor") {
        // Negative values
        CHECK_THROWS_AS(Board(8, -8), incorrect_data);
        CHECK_THROWS_AS(Board(-8, 8), incorrect_data);
        CHECK_THROWS_AS(Board(-8, -8), incorrect_data);

        // Zero values
        CHECK_THROWS_AS(Board(0, 8), incorrect_data);
        CHECK_THROWS_AS(Board(8, 0), incorrect_data);
        CHECK_THROWS_AS(Board(0, 0), incorrect_data);

        // Exceeding max board size
        CHECK_THROWS_AS(Board(Board::maxBoardSize + 1, 8), incorrect_data);
        CHECK_THROWS_AS(Board(8, Board::maxBoardSize + 1), incorrect_data);
        CHECK_THROWS_AS(Board(Board::maxBoardSize + 1, Board::maxBoardSize + 1), incorrect_data);

        // Right values
        CHECK_NOTHROW(Board(8, 8));
        CHECK_NOTHROW(Board(8, Board::maxBoardSize));
        CHECK_NOTHROW(Board(Board::maxBoardSize, 8));
        CHECK_NOTHROW(Board(Board::maxBoardSize, Board::maxBoardSize));
    }

    TEST_CASE("Get Dimensions") {
        constexpr int height = 7, width = 5;
        const Board board(height, width);
        CHECK(board.getHeight() == height);
        CHECK(board.getWidth() == width);
    }

    TEST_CASE("Print") {
        CHECK_NOTHROW(Board(1, 1).print());
        CHECK_NOTHROW(Board(Board::maxBoardSize, Board::maxBoardSize).print());
    }

    TEST_CASE("Place/Get Symbol") {
        constexpr char symbol = 'X';
        constexpr int height = 7, width = 5;

        // Placed right
        Board board1(height, width);
        board1.placeSymbol({0}, symbol);
        CHECK(board1.getSymbol(height-1, 0) == symbol);
        board1.placeSymbol({width-1}, symbol);
        CHECK(board1.getSymbol(height-1, width-1) == symbol);

        Board board2(height, width);
        board2.placeSymbol({0, 0}, symbol);
        CHECK(board2.getSymbol(0, 0) == symbol);
        board2.placeSymbol({0, width-1}, symbol);
        CHECK(board2.getSymbol(0, width-1) == symbol);
        board2.placeSymbol({height-1, 0}, symbol);
        CHECK(board2.getSymbol(height-1, 0) == symbol);
        board2.placeSymbol({height-1, width-1}, symbol);
        CHECK(board2.getSymbol(height-1, width-1) == symbol);

        // Get out of range
        CHECK_THROWS_AS(board2.getSymbol(-1, 0), invalid_move);
        CHECK_THROWS_AS(board2.getSymbol(0, -1), invalid_move);
        CHECK_THROWS_AS(board2.getSymbol(-1, -1), invalid_move);
        CHECK_THROWS_AS(board2.getSymbol(height, 0), invalid_move);
        CHECK_THROWS_AS(board2.getSymbol(0, width), invalid_move);
        CHECK_THROWS_AS(board2.getSymbol(height, width), invalid_move);

        // Place out of range
        CHECK_THROWS_AS(board1.placeSymbol({width}, symbol), invalid_move);
        CHECK_THROWS_AS(board2.placeSymbol({height, 0}, symbol), invalid_move);
        CHECK_THROWS_AS(board2.placeSymbol({0, width}, symbol), invalid_move);
        CHECK_THROWS_AS(board2.placeSymbol({height, width}, symbol), invalid_move);
    }
}