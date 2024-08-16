//
// Created by Carlos Eduardo on 05/08/2024.
//

#ifndef CONNECTFOUR_HPP
#define CONNECTFOUR_HPP

#include "BoardGame.hpp"
#include "Player.hpp"
#include <vector>

class ConnectFour final: public BoardGame {
    static const uint32_t minimumBoardSize;
    static const uint32_t defaultBoardSize;


public:
    ConnectFour(Player _player1, Player _player2, uint32_t boardSize = ConnectFour::defaultBoardSize);

private:

    /**
     * Check if it is a valid height for the game board
     *
     * @param boardHeight
     * @return true if it is a valid height
     */
    bool isAValidHeight(uint32_t boardHeight) override;

    /**
     * Check if it is a valid height for the game board
     *
     * @param boardWidth
     * @return true if it is a valid height
     */
    bool isAValidWidth(uint32_t boardWidth) override;

    void validateMove(const std::vector<int> &move)const override;

    GameState getGameState(const std::vector<int>& move) const override;

    bool checkDirection(const std::vector<int> &move, char symbol, char pSymbol, int dRow, int dCol);
};

#endif //CONNECTFOUR_HPP
