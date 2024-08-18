//
// Created by Pedro Henrique Pires  on 30/07/24.
//

#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include "BoardGame.hpp"

/**
 * Class that represents the Tic Tac Toe game
 */
class TicTacToe final: public BoardGame {
private:
    static const uint32_t defaultBoardSize; /**< Default size of the board (height == width) */

public:
    /**
     * Create a new Tic Tac Toe game
     *
     * @param _player1 Player 1
     * @param _player2 Player 2
     */
    TicTacToe(Player _player1, Player _player2);

private:
    /**
     * If it is a valid move, inside the board and the place is empty
     *
     * @param move 2D vector representing the move
     *
     * @throws incorrect_format if the move is empty or has more than 2 values
     * @throws invalid_move if the move is outside the board
     */
    void validateMove(const std::vector<uint32_t>& move) const override;

    /**
     * Check the current state of the game
     *
     * @param move 2D vector representing the last move
     * @return The current state of the game
     */
    GameState getGameState(const std::vector<uint32_t>& move) const override;
};

#endif //TICTACTOE_HPP
