#ifndef REVERSI_HPP
#define REVERSI_HPP

#include "BoardGame.hpp"
#include "Player.hpp"
#include "exceptions.hpp"
#include <vector>

class Reversi final: public BoardGame {
    static constexpr uint32_t minimumBoardSize = 4;
    static constexpr uint32_t defaultBoardSize = 8;

public:
    Reversi(Player &_player1, Player &_player2, uint32_t boardSize = Reversi::defaultBoardSize);

    void validateMove(const std::vector<int> &move) const override;

    /**
     * Fazer movimento e virar peças necessárias
     *
     * @param move Coordenadas do movimento
     * @param symbol Símbolo do jogador
     */
    void makeMove(const std::vector<int> &move, char symbol) override;

    GameState getGameState() const override;

private:
    void flipPieces(const std::vector<int>& move, char playerSymbol);

    bool isValidDirection(int row, int col, int directionRow, int directionCol, char playerSymbol) const;

    void flipInDirection(int row, int col, int directionRow, int directionCol, char playerSymbol);

    bool isAnyDirectionValid(int row, int col, char playerSymbol) const;

    bool isWithinBounds(int row, int col) const;

    bool hasValidMoves(char playerSymbol) const;
};

#endif
