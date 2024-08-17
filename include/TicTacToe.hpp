//
// Created by Pedro Henrique Pires  on 30/07/24.
//

#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include "BoardGame.hpp"

class TicTacToe final: public BoardGame {
private:
    static const uint32_t defaultBoardSize;

public:
    TicTacToe(Player _player1, Player _player2);

private:
    void validateMove(const std::vector<uint32_t>& move) const override;

    GameState getGameState(const std::vector<uint32_t>& move) const override;
};

#endif //TICTACTOE_HPP
