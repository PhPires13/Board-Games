//
// Created by Pedro Henrique Pires  on 30/07/24.
//

#include "TicTacToe.hpp"

#include "exceptions.hpp"

const uint32_t TicTacToe::defaultBoardHeight = 3;
const uint32_t TicTacToe::defaultBoardWidth = 3;

TicTacToe::TicTacToe(Player &_player1, Player &_player2
): BoardGame(_player1, _player2, TicTacToe::defaultBoardHeight, TicTacToe::defaultBoardHeight) {}

void TicTacToe::validateMove(const std::vector<int> &move) const {
    BoardGame::validateMove(move);

    // Move input size
    if (move.size() != 2) throw incorrect_format();

    // Place is empty
    if (this->board.getSymbol(move[0], move[1]) != ' ') throw invalid_move();
}

GameState TicTacToe::getGameState() const {
    // Check rows
    for (int i = 0; i < this->board.getHeight(); i++) {
        if ((this->board.getSymbol(i, 0) == this->board.getSymbol(i, 1)) &&
            (this->board.getSymbol(i, 1) == this->board.getSymbol(i, 2)) &&
            (this->board.getSymbol(i, 0) != ' ')) {
            return (this->board.getSymbol(i, 0) == player1.getSymbol() ? GameState::PLAYER1_WINS : GameState::PLAYER2_WINS);
        }
    }

    // Check columns
    for (int i = 0; i < this->board.getWidth(); i++) {
        if ((this->board.getSymbol(0, i) == this->board.getSymbol(1, i)) &&
            (this->board.getSymbol(1, i) == this->board.getSymbol(2, i)) &&
            (this->board.getSymbol(0, i) != ' ')) {
            return (this->board.getSymbol(0, i) == player1.getSymbol() ? GameState::PLAYER1_WINS : GameState::PLAYER2_WINS);
        }
    }

    // Check main diagonal
    if ((this->board.getSymbol(0, 0) == this->board.getSymbol(1, 1)) &&
        (this->board.getSymbol(1, 1) == this->board.getSymbol(2, 2)) &&
        (this->board.getSymbol(0, 0) != ' ')) {
        return (this->board.getSymbol(0, 0) == player1.getSymbol() ? GameState::PLAYER1_WINS : GameState::PLAYER2_WINS);
    }

    // Check secondary diagonal
    if ((this->board.getSymbol(0, 2) == this->board.getSymbol(1, 1)) &&
        (this->board.getSymbol(1, 1) == this->board.getSymbol(2, 0)) &&
        (this->board.getSymbol(0, 2) != ' ')) {
        return (this->board.getSymbol(0, 2) == player1.getSymbol() ? GameState::PLAYER1_WINS : GameState::PLAYER2_WINS);
    }

    return BoardGame::getGameState();
}
