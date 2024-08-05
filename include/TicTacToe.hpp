//
// Created by Pedro Henrique Pires  on 30/07/24.
//

#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include "BoardGame.hpp"

class TicTacToe final: public BoardGame {
    static const uint32_t defaultBoardHeight;
    static const uint32_t defaultBoardWidth;

public:
    TicTacToe(Player _player1, Player _player2);

private:
    void validateMove(const std::vector<int> &move) const override;

    GameState getGameState() const override;
};

#endif //TICTACTOE_HPP
