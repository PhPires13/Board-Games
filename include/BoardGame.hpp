//
// Created by pires on 6/28/2024.
//

#ifndef BOARDGAME_HPP
#define BOARDGAME_HPP

#include <vector>

#include "Board.hpp"
#include "Player.hpp"

/**
 * Enum to represent the possible states during a game
 */
enum GameState {
    NOT_OVER = 0,
    PLAYER1_WINS = 1,
    PLAYER2_WINS = 2,
    TIE = 3,
};

/**
 * Class to represent a generic board game, it is responsible for controlling all the processes of the game and the players in the match
 */
class BoardGame {
protected:
    static const uint32_t defaultBoardHeight; /**< Default height of the board */
    static const uint32_t defaultBoardWidth; /**< Default width of the board */

    static const char defaultSymbol1; /**< Default symbol for player 1 */
    static const char defaultSymbol2; /**< Default symbol for player 2 */

    Player player1; /**< Player 1 of the game */
    Player player2; /**< Player 2 of the game */

    Board board; /**< The board of the game */

    uint32_t turn; /**< The current turn of the game, first turn is 1 */

public:
    /**
     * Create a BoardGame instance
     *
     * @param _player1 Player 1 of the game
     * @param _player2 Player 2 of the game
     * @param boardHeight Height of the board
     * @param boardWidth Width of the board
     * @param indexColor Color of the indexes
     * @param piecesColor Color of the pieces
     * @param borderColor Color of the board
     * @param evenBg Background color of the even cells
     * @param oddBg Background color of the odd cells
     */
    BoardGame(Player _player1, Player _player2, uint32_t boardHeight = BoardGame::defaultBoardHeight, uint32_t boardWidth = BoardGame::defaultBoardWidth,
     const std::string& indexColor = "", const std::string& piecesColor = "", const std::string& borderColor = "",
     const std::string& evenBg = "", const std::string& oddBg = "");

    /**
     * Play the game
     *
     * @return The game state at the end
     */
    GameState playGame();

protected:
    /**
     * Check if it is a valid height for the game board
     *
     * @param boardHeight
     * @return true if it is a valid height
     */
    virtual bool isAValidHeight(uint32_t boardHeight) const;

    /**
     * Check if it is a valid height for the game board
     *
     * @param boardWidth
     * @return true if it is a valid height
     */
    virtual bool isAValidWidth(uint32_t boardWidth) const;

    /**
     * Print the current board state
     */
    void printBoard() const;

    /**
     * Read a move from the whole input line (int values separated by space)
     *
     * @return A vector with the move coordinates
     */
    static std::vector<uint32_t> readMove();

    /**
     * Validate if move is valid by throwing exceptions if not
     *
     * @param move The move to be checked
     *
     * @throws incorrect_format if the move is empty or has more than 2 values
     * @throws invalid_move if the move is outside the board
     */
    virtual void validateMove(const std::vector<uint32_t>& move) const;

    /**
     * Execute move on the board
     *
     * @param move The move to be executed
     * @param symbol The symbol to be placed on the board
     *
     * @throw invalid_move if the move is outside the board
     */
    virtual void makeMove(const std::vector<uint32_t>& move, char symbol);

    /**
     * Check if the game is over
     *
     * @param move The last move made, can be used for optimal checks
     *
     * @return GameState enum
     */
    virtual GameState getGameState(const std::vector<uint32_t>& move) const;

    /**
     * Check whose turn is it
     */
    Player whoseTurn() const;
};

#endif //BOARDGAME_HPP
