//
// Created by pires on 6/28/2024.
//

#ifndef BOARDGAME_HPP
#define BOARDGAME_HPP

#include <vector>

#include "Player.hpp"

class BoardGame {
    static constexpr int defaultBoardWidth = 4;
    static constexpr int defaultBoardHeight = 4;

    static constexpr char defaultSymbol1 = 'X';
    static constexpr char defaultSymbol2 = 'O';

    static constexpr int incorrectFormat = -1;
    static constexpr int invalidMove = 0;
    static constexpr int validMove = 1;

    static constexpr int notOver = 0;
    static constexpr int player1Wins = 1;
    static constexpr int player2Wins = 2;
    static constexpr int tie = 3;

    Player& player1;
    Player& player2;

    int boardWidth;
    int boardHeight;
    std::vector<std::vector<char>> board;

public:
    BoardGame(Player& _player1, Player& _player2, int _boardWidth = BoardGame::defaultBoardWidth,
        int _boardHeight = BoardGame::defaultBoardHeight, char symbol1 = BoardGame::defaultSymbol1,
        char symbol2 = BoardGame::defaultSymbol2);
    void printBoard() const;

    static std::vector<int> readMove();
    int isMoveValid(const std::vector<int>& move) const;
    void makeMove(const std::vector<int>& move, char symbol);
    int getGameState() const;
    Player& whoseTurn(int turn) const;
    void playGame();
};

#endif //BOARDGAME_HPP
