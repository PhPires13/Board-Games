#include "Reversi.hpp"
#include <iostream>

const int BOARD_SIZE = 3;  // Corrigido para 8x8
const char EMPTY_CELL = ' ';

Reversi::Reversi(Player &_player1, Player &_player2)
    : BoardGame(_player1, _player2, BOARD_SIZE, BOARD_SIZE), player1(_player1), player2(_player2), turn(0) {
    int mid = BOARD_SIZE / 2;

    // Inicializa o tabuleiro com as peças iniciais no meio
    this->board.placeSymbol({mid - 1, mid - 1}, player1.getSymbol());
    this->board.placeSymbol({mid - 1, mid}, player2.getSymbol());
    this->board.placeSymbol({mid, mid - 1}, player2.getSymbol());
    this->board.placeSymbol({mid, mid}, player1.getSymbol());
}

void Reversi::validateMove(const std::vector<int> &move) const {
    BoardGame::validateMove(move);

    if (move.size() != 2) throw incorrect_format();
    int row = move[0];
    int col = move[1];
    //Já existe peça
    if (this->board.getSymbol(row, col) != EMPTY_CELL) throw invalid_move();
    //Pegando o simbolo do jogador atual
    char currentPlayerSymbol = getCurrentPlayer().getSymbol();
    //Verifica se a jogada é valida
    if (!isAnyDirectionValid(row, col, currentPlayerSymbol)) {
        throw invalid_move();
    }
}

// Fazer movimento e virar peças necessárias
void Reversi::makeMove(const std::vector<int> &move, char Symbol) {
    //Validando movimento
    validateMove(move);
    char currentPlayerSymbol = getCurrentPlayer().getSymbol();
    this->board.placeSymbol(move, currentPlayerSymbol);
    flipPieces(move, currentPlayerSymbol);
    this->switchPlayer();
}

GameState Reversi::getGameState() const {
    // Verifica se há movimentos válidos para qualquer jogador
    if ((!hasValidMoves(player1.getSymbol()) && getCurrentPlayer().getSymbol() == player1.getSymbol()) || (!hasValidMoves(player2.getSymbol()) && getCurrentPlayer().getSymbol() == player2.getSymbol())) {
        // Contar peças para determinar o vencedor
        int player1Count = 0;
        int player2Count = 0;
        for (int row = 0; row < BOARD_SIZE; ++row) {
            for (int col = 0; col < BOARD_SIZE; ++col) {
                if (this->board.getSymbol(row, col) == player1.getSymbol()) {
                    ++player1Count;
                } else if (this->board.getSymbol(row, col) == player2.getSymbol()) {
                    ++player2Count;
                }
            }
        }

        std::cout << "Game Over! ";
        if (player1Count > player2Count) {
            std::cout << "Player 1 wins!\n";
        return GameState::PLAYER1_WINS;
        } else if (player2Count > player1Count) {
            std::cout << "Player 2 wins!\n";
        return GameState::PLAYER2_WINS;
        } else {
            std::cout << "It's a tie!\n";
        return GameState::TIE;
        }

    }

    return GameState::NOT_OVER;
}

void Reversi::flipPieces(const std::vector<int>& move, char playerSymbol) {
    int row = move[0];
    int col = move[1];
    for (int directionRow = -1; directionRow <= 1; ++directionRow) {
        for (int directionCol = -1; directionCol <= 1; ++directionCol) {
            if (directionRow != 0 || directionCol != 0) {
                if (isValidDirection(row, col, directionRow, directionCol, playerSymbol)) {
                    flipInDirection(row, col, directionRow, directionCol, playerSymbol);
                }
            }
        }
    }
}

bool Reversi::isValidDirection(int row, int col, int directionRow, int directionCol, char playerSymbol) const {
    int r = row + directionRow;
    int c = col + directionCol;
    char opponentSymbol = (playerSymbol == player1.getSymbol()) ? player2.getSymbol() : player1.getSymbol();

    if (!isWithinBounds(r, c) || this->board.getSymbol(r, c) != opponentSymbol) {
        return false;
    }

    r += directionRow;
    c += directionCol;

    while (isWithinBounds(r, c)) {
        if (this->board.getSymbol(r, c) == EMPTY_CELL) {
            return false;
        }
        if (this->board.getSymbol(r, c) == playerSymbol) {
            return true;
        }
        r += directionRow;
        c += directionCol;
    }

    return false;
}

void Reversi::flipInDirection(int row, int col, int directionRow, int directionCol, char playerSymbol) {
    int r = row + directionRow;
    int c = col + directionCol;
    while (this->board.getSymbol(r, c) != playerSymbol) {
        this->board.placeSymbol({r, c}, playerSymbol);
        r += directionRow;
        c += directionCol;
    }
}

bool Reversi::isAnyDirectionValid(int row, int col, char playerSymbol) const {
    for (int directionRow = -1; directionRow <= 1; directionRow++) {
        for (int directionCol = -1; directionCol <= 1; directionCol++) {
            if (directionRow != 0 || directionCol != 0) {  // Ignora a direção (0, 0), que não é válida
                if (isValidDirection(row, col, directionRow, directionCol, playerSymbol)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Reversi::isWithinBounds(int row, int col) const {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

bool Reversi::hasValidMoves(char playerSymbol) const {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (this->board.getSymbol(row, col) == EMPTY_CELL && isAnyDirectionValid(row, col, playerSymbol)) {
                return true;
            }
        }
    }
    return false;
}

Player& Reversi::getCurrentPlayer() const {
    return (turn % 2 == 0) ? player1 : player2;
}

void Reversi::switchPlayer() {
    turn++;
}
