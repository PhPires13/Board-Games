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
    /*
    * Create a BoardGame instance
    *
    * @param _player1: Player 1 of the game
    * @param _player2: Player 2 of the game
    * @param _boardWidth: Width of the board
    * @param _boardHeight: Height of the board
    * @param symbol1: Symbol of player 1
    * @param symbol2: Symbol of player 2
    */
    BoardGame(Player& _player1, Player& _player2, int _boardWidth = BoardGame::defaultBoardWidth,
    int _boardHeight = BoardGame::defaultBoardHeight, char symbol1 = BoardGame::defaultSymbol1,
    char symbol2 = BoardGame::defaultSymbol2);

    /*
    * Print the current board state
    */
    void printBoard() const;

    /*
    * Read a move from the whole input line (int values separated by space)
    *
    * @return: A vector with the move coordinates
    */
    static std::vector<int> readMove();

    /*
    * Check if the move is valid
    *
    * @param move: The move to be checked
    *
    * @return: incorrectFormat (-1), invalidMove (0) or validMove (1)
    */
    int isMoveValid(const std::vector<int>& move) const;

    /*
    * Execute move on the board
    *
    * @param move: The move to be executed
    * @param symbol: The symbol to be placed on the board
    */
    void makeMove(const std::vector<int>& move, char symbol);

    /*
    * Check if the game is over
    *
    * @return: notOver (0), player1Wins (1), player2Wins (2) or tie (3)
    */
    int getGameState() const;

    /*
    * Check whose turn is it
    *
    * @Param turn: The current turn number
    */
    Player& whoseTurn(int turn) const;

    /*
    * Play the game
    */
    void playGame();
};

#endif //BOARDGAME_HPP
