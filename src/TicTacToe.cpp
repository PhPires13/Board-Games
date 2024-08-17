//
// Created by Pedro Henrique Pires  on 30/07/24.
//

#include "TicTacToe.hpp"

#include "exceptions.hpp"

const uint32_t TicTacToe::defaultBoardSize = 3;

TicTacToe::TicTacToe(Player _player1, Player _player2
): BoardGame(std::move(_player1), std::move(_player2), TicTacToe::defaultBoardSize, TicTacToe::defaultBoardSize,
    "\033[38;2;180;180;180m", "\033[38;2;240;240;240m", "\033[38;2;128;128;128m", "\033[48;2;153;101;21m", "\033[48;2;101;67;33m") {}

void TicTacToe::validateMove(const std::vector<uint32_t>& move) const {
    BoardGame::validateMove(move);

    // Move input size
    if (move.size() != 2) throw incorrect_format();

    // Place is empty
    if (this->board.getSymbol(move[0], move[1]) != Board::emptyCell) throw invalid_move();
}

GameState TicTacToe::getGameState(const std::vector<uint32_t>& move) const {
    if (!move.empty()) {
        // Check the row of the move
        if ((this->board.getSymbol(move[0], 0) != Board::emptyCell) &&
            (this->board.getSymbol(move[0], 0) == this->board.getSymbol(move[0], 1)) &&
            (this->board.getSymbol(move[0], 1) == this->board.getSymbol(move[0], 2))) {
            return (this->board.getSymbol(move[0], 0) == player1.getSymbol() ? GameState::PLAYER1_WINS : GameState::PLAYER2_WINS);
            }

        // Check the line of the move
        if ((this->board.getSymbol(0, move[1]) != Board::emptyCell) &&
            (this->board.getSymbol(0, move[1]) == this->board.getSymbol(1, move[1])) &&
            (this->board.getSymbol(1, move[1]) == this->board.getSymbol(2, move[1]))) {
            return (this->board.getSymbol(0, move[1]) == player1.getSymbol() ? GameState::PLAYER1_WINS : GameState::PLAYER2_WINS);
        }

        // If move is in amin diagonal
        if (move[0] == move[1]) {
            if ((this->board.getSymbol(0, 0) != Board::emptyCell) &&
                (this->board.getSymbol(0, 0) == this->board.getSymbol(1, 1)) &&
                (this->board.getSymbol(1, 1) == this->board.getSymbol(2, 2))) {
                return (this->board.getSymbol(0, 0) == player1.getSymbol() ? GameState::PLAYER1_WINS : GameState::PLAYER2_WINS);
            }
        }

        // If move is in secondary diagonal
        if (move[0] + move[1] == TicTacToe::defaultBoardSize-1) {
            if ((this->board.getSymbol(0, 2) != Board::emptyCell) &&
                (this->board.getSymbol(0, 2) == this->board.getSymbol(1, 1)) &&
                (this->board.getSymbol(1, 1) == this->board.getSymbol(2, 0))) {
                return (this->board.getSymbol(0, 2) == player1.getSymbol() ? GameState::PLAYER1_WINS : GameState::PLAYER2_WINS);
            }
        }
    }

    return BoardGame::getGameState(move);
}
