#ifndef REVERSI_HPP
#define REVERSI_HPP

#include "BoardGame.hpp"
#include "Player.hpp"
#include "exceptions.hpp"
#include <vector>

class Reversi : public BoardGame {
public:
    Reversi(Player &_player1, Player &_player2);

    void validateMove(const std::vector<int> &move) const override;
    void makeMove(const std::vector<int> &move,char symbol) override;
    GameState getGameState() const override;

private:
    void flipPieces(const std::vector<int>& move, char playerSymbol);
    bool isValidDirection(int row, int col, int dRow, int dCol, char playerSymbol) const;
    void flipInDirection(int row, int col, int dRow, int dCol, char playerSymbol);
    bool isAnyDirectionValid(int row, int col, char playerSymbol) const;
    bool isWithinBounds(int row, int col) const;
    bool hasValidMoves(char playerSymbol) const;
    Player& getCurrentPlayer() const;
    void switchPlayer();

    Player &player1;
    Player &player2;
    int turn;
};

#endif
