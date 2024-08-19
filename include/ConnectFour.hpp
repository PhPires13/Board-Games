//
// Created by Carlos Eduardo on 05/08/2024.
//

#ifndef CONNECTFOUR_HPP
#define CONNECTFOUR_HPP


#include "BoardGame.hpp"
#include "Player.hpp"
#include <vector>

/**
 * Class that represents the Connect Four game
 */
class ConnectFour final: public BoardGame {
private:
    static const uint32_t minimumBoardSize; /**< Minimum size of the board (height == width) */
    static const uint32_t defaultBoardHeight; /**< Default height of the board */
    static const uint32_t defaultBoardWidth; /**< Default width of the board */

public:
    /**
     * ConectFour class Cconstructor. Initialize the game with two players and the board's dimensions.
     *
     * @param _player1 Player 1
     * @param _player2 Player 2
     * @param boardHeight Board's Height
     * @param boardWidth Board's Width
     */
    ConnectFour(Player _player1, Player _player2, uint32_t boardHeight = ConnectFour::defaultBoardHeight, uint32_t boardWidth = ConnectFour::defaultBoardWidth);

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
     *  Check if the selected column is full and execute piece move if it's not.
     *
     * @param move Column coordinates.
     *
     * @throws incorrect_format if the move is empty or has more than 1 values.
     * @throws invalid_move if the move is outside the board.
     */
    void validateMove(const std::vector<uint32_t> &move)const override;

    /**
     * Check the current state of the game, according to ConnectFour rules.
     *
     *
     * @param move 1D vector representing the last move
     * @return The current state of the game
     */
    GameState getGameState(const std::vector<uint32_t>& move) const override;

   /**
     * Check if there are four identical pieces in a row in certain direction after a move.
     *
     * @param move Move coordinates
     * @param symbol Symbol of the player who made the move
     * @param dRow Flag to analyse cells on horizontal direction
     * @param dCol Flag to analyse cells on vertical direction
     */
    bool checkDirection(const std::vector<uint32_t> &move, char symbol, int dRow, int dCol) const;
};

#endif //CONNECTFOUR_HPP
