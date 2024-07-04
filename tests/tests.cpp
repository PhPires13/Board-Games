//
// Created by Pedro Henrique Pires  on 04/07/24.
//

#include "doctest.h"

TEST_CASE("Test BoardGame::isMoveValid()") {
    Player player1 = Player("Nick1", "Name1");
    Player player2 = Player("Nick2", "Name2");

    BoardGame boardGame = BoardGame(player1, player2);

    CHECK(boardGame.isMoveValid({0, 0}) == MoveStatus::VALID_MOVE);
    CHECK(boardGame.isMoveValid({-1, 0}) == MoveStatus::INVALID_MOVE);
    CHECK(boardGame.isMoveValid({0, -1}) == MoveStatus::INVALID_MOVE);
    CHECK(boardGame.isMoveValid({-1, -1}) == MoveStatus::INVALID_MOVE);

    CHECK(boardGame.isMoveValid({0}) == MoveStatus::VALID_MOVE);
    CHECK(boardGame.isMoveValid({-1}) == MoveStatus::INVALID_MOVE);

    CHECK(boardGame.isMoveValid({}) == MoveStatus::INCORRECT_FORMAT);
    CHECK(boardGame.isMoveValid({0, 0, 0}) == MoveStatus::INCORRECT_FORMAT);
}

TEST_CASE("Test BoardGame::whoseTurn(int turn)") {
    Player player1 = Player("Nick1", "Name1");
    Player player2 = Player("Nick2", "Name2");

    BoardGame boardGame = BoardGame(player1, player2);

    CHECK(boardGame.whoseTurn(0) == player1);
    CHECK(boardGame.whoseTurn(1) == player2);
    CHECK(boardGame.whoseTurn(2) == player1);
    CHECK(boardGame.whoseTurn(3) == player2);
}