//
// Created by pires on 6/28/2024.
//

#ifndef BOARDGAME_HPP
#define BOARDGAME_HPP

#include <vector>

#include "Board.hpp"
#include "Player.hpp"

enum MoveStatus {
    INCORRECT_FORMAT = -1,
    INVALID_MOVE = 0,
    VALID_MOVE = 1,
};

enum GameState {
    NOT_OVER = 0,
    PLAYER1_WINS = 1,
    PLAYER2_WINS = 2,
    TIE = 3,
};

/**
 * Class to represent a board game, it is responsible for controlling all the processes of the game and the players in the match
 */
class BoardGame {
protected:
    static constexpr int defaultBoardHeight = 4;
    static constexpr int defaultBoardWidth = 4;

    static constexpr char defaultSymbol1 = 'X';
    static constexpr char defaultSymbol2 = 'O';

    Player& player1;
    Player& player2;

    Board board;

public:
    /**
     * Create a BoardGame instance
     *
     * @param _player1 Player 1 of the game
     * @param _player2 Player 2 of the game
     * @param boardHeight Height of the board
     * @param boardWidth Width of the board
     */
    BoardGame(Player& _player1, Player& _player2, int boardHeight = BoardGame::defaultBoardHeight,
        int boardWidth = BoardGame::defaultBoardWidth);

    /**
     * Print the current board state
     */
    void printBoard() const;

    /**
     * Read a move from the whole input line (int values separated by space)
     *
     * @return A vector with the move coordinates
     */
    static std::vector<int> readMove();

    /**
     * Check if the move is valid
     *
     * @param move The move to be checked
     *
     * @return MovieStatus enum
     */
    virtual MoveStatus isMoveValid(const std::vector<int>& move) const;

    /**
     * Execute move on the board
     *
     * @param move The move to be executed
     * @param symbol The symbol to be placed on the board
     */
    virtual void makeMove(const std::vector<int>& move, char symbol);

    /**
     * Check if the game is over
     *
     * @return GameState enum
     */
    virtual GameState getGameState() const;

    /**
     * Check whose turn is it
     *
     * @param turn The current turn number
     */
    Player& whoseTurn(int turn) const;

    /**
     * Play the game
     *
     * @return The game state at the end
     */
    GameState playGame();
};

#endif //BOARDGAME_HPP
