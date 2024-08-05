#ifndef REVERSI_HPP
#define REVERSI_HPP

#include "BoardGame.hpp"
#include "Player.hpp"
#include "exceptions.hpp"
#include <vector>

class Reversi final: public BoardGame {
    static const uint32_t minimumBoardSize;
    static const uint32_t defaultBoardSize;

public:
    Reversi(Player _player1, Player _player2, uint32_t boardSize = Reversi::defaultBoardSize);

private:
    /**
     * Check if it is a valid height for the game board
     *
     * @param boardHeight
     * @return true if it is a valid height
     */
    virtual bool isAValidHeight(uint32_t boardHeight);

    /**
     * Check if it is a valid height for the game board
     *
     * @param boardWidth
     * @return true if it is a valid height
     */
    virtual bool isAValidWidth(uint32_t boardWidth);

    void validateMove(const std::vector<int> &move) const override;

    /**
     * Fazer movimento e virar peças necessárias
     *
     * @param move Coordenadas do movimento
     * @param symbol Símbolo do jogador
     */
    void makeMove(const std::vector<int> &move, char symbol) override;

    GameState getGameState() const override;

    void flipPieces(const std::vector<int>& move, char playerSymbol);

    bool isValidDirection(int row, int col, int directionRow, int directionCol, char playerSymbol) const;

    void flipInDirection(int row, int col, int directionRow, int directionCol, char playerSymbol);

    bool isAnyDirectionValid(int row, int col, char playerSymbol) const;

    bool isWithinBounds(int row, int col) const;

    bool hasValidMoves(char playerSymbol) const;
};

#endif
