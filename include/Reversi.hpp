//
// Created by Pedro Henrique Pires  on 30/07/24.
//

#ifndef REVERSI_HPP
#define REVERSI_HPP

#include "BoardGame.hpp"

class Reversi final: public BoardGame {
    static constexpr int defaultBoardHeight = 3;
    static constexpr int defaultBoardWidth = 3;

public:
    Reversi(Player& _player1, Player& _player2);

    void validateMove(const std::vector<int> &move) const override;
    // Necessário para mudar o movimento
    void makeMove(const std::vector<int> &move, char symbol) override;
    GameState getGameState() const override;
};

#endif
