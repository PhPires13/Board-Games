#ifndef REVERSI_HPP
#define REVERSI_HPP

#include "BoardGame.hpp"
#include "Player.hpp"
#include <vector>

/**
 * Class that represents the Reversi game
 */
class Reversi final : public BoardGame {
private:
    static const uint32_t minimumBoardSize; /**< Minimum board size (height == width) */
    static const uint32_t defaultBoardSize; /**< Default board size (height == width) */

public:
    /**
     * Reversi class Cconstructor. Initialize the game with two players and one board size.
     *
     * @param _player1 Player 1
     * @param _player2 Player 2
     * @param boardSize Board size (it must be an even number, otherwise, it will be used the default size)
     */
    Reversi(Player _player1, Player _player2, uint32_t boardSize = Reversi::defaultBoardSize);

private:
    /**
     * Check if the board's height is valid.
     *
     * @param boardHeight
     * @return true if it is as valid height.
     */
    bool isAValidHeight(uint32_t boardHeight) const override;

     /**
      * Check if the board's width is valid.
      *
      * @param boardWidth
      * @return true if it is as valid height.
      */
    bool isAValidWidth(uint32_t boardWidth) const override;

    /**
     * Check if the move made is valid, according to Reversi rules.
     *
     * @param move Move coordinates (row, column)
     * @throws incorrect_format if the move is empty, has more than 2 values and less than 1 value.
     * @throws invalid_move if the move is invalid.
     */
    void validateMove(const std::vector<uint32_t> &move) const override;

    /**
     * Execute the move and flip the necessary pieces.
     *
     * @param move Move coordinates
     * @param symbol Symbol of the player who made the move
     *
     * @throws invalid_move if the move is invalid.
     */
    void makeMove(const std::vector<uint32_t> &move, char symbol) override;

    /**
     * Check the current state of the game, according to Reversi rules.
     *
     * @param move Last move
     *
     * @param move 2D vector representing the last move
     * @return The current state of the game
     */
    GameState getGameState(const std::vector<uint32_t>& move) const override;

    /**
     * Flip the opponent pieces according to Reversi rules, after a valid move.
     *
     * @param move Move coordinates
     * @param playerSymbol Symbol of the player who made the move
     */
    void flipPieces(const std::vector<uint32_t>& move, char playerSymbol);

    /**
     * Check a specific direction from a valid position to flip the pieces.
     *
     * @param row Move row
     * @param col Move column
     * @param directionRow Line direction (-1, 0, 1)
     * @param directionCol Column direction (-1, 0, 1)
     * @param playerSymbol Symbol of the current player
     * @return true if it is a valid direction
     */
    bool isValidDirection(int row, int col, int directionRow, int directionCol, char playerSymbol) const;

    /**
     * Flip the opponent pieces in a specific direction.
     *
     * @param row Move row
     * @param col Move column
     * @param directionRow Line direction (-1, 0, 1)
     * @param directionCol Column direction (-1, 0, 1)
     * @param playerSymbol Symbol of the current player
     */
    void flipInDirection(int row, int col, int directionRow, int directionCol, char playerSymbol);

    /**
     * Check if there is any valid direction for the given move.
     *
     * @param row Move row
     * @param col Move column
     * @param playerSymbol Symbol of the current player
     * @return true if there is at least one valid direction.
     */
    bool isAnyDirectionValid(int row, int col, char playerSymbol) const;

    /**
     * Check if the coordinates are inside the board edges.
     *
     * @param row Row to be checked
     * @param col Column to be checked.
     * @return true if the coordinates are insde the board edges.
     */
    bool isWithinBounds(int row, int col) const;

    /**
     * Check if there are still possiblemoves for a given player.
     *
     * @param playerSymbol Player symbol
     * @return true if there are still available valid moves.
     */
    bool hasValidMoves(char playerSymbol) const;
};

#endif
