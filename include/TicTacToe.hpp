//
// Created by Paulo Henrique Pires  on 30/07/24.
//

#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include "BoardGame.hpp"

class TicTacToe final: public BoardGame {
    static constexpr int defaultBoardHeight = 3;
    static constexpr int defaultBoardWidth = 3;

public:
    TicTacToe(Player& _player1, Player& _player2);

    MoveStatus isMoveValid(const std::vector<int> &move) const override;

    // TODO: remover nota, makeMove() não foi necessário, também não será para o Lig4, mas para o Reversi será para virrar demias peças

    GameState getGameState() const override;
};

#endif //TICTACTOE_HPP
