#include "Reversi.hpp"
#include <iostream>

const uint32_t Reversi::minimumBoardSize = 4;
const uint32_t Reversi::defaultBoardSize = 8;

Reversi::Reversi(Player _player1, Player _player2, uint32_t boardSize)
    : BoardGame(std::move(_player1), std::move(_player2), (Reversi::isAValidHeight(boardSize) ? boardSize : Reversi::defaultBoardSize),
        (Reversi::isAValidWidth(boardSize) ? boardSize : Reversi::defaultBoardSize),
        "\033[38;2;255;255;0m", "\033[38;2;255;255;255m", "\033[30m", "\033[48;2;0;150;23m", "\033[48;2;0;100;15m") {
    if (!Reversi::isAValidHeight(boardSize))
        boardSize = Reversi::defaultBoardSize;

    const int mid = boardSize / 2;

    // Inicializa o tabuleiro com as peças iniciais no meio
    this->board.placeSymbol({mid - 1, mid - 1}, player1.getSymbol());
    this->board.placeSymbol({mid - 1, mid}, player2.getSymbol());
    this->board.placeSymbol({mid, mid - 1}, player2.getSymbol());
    this->board.placeSymbol({mid, mid}, player1.getSymbol());
}

bool Reversi::isAValidHeight(const uint32_t boardHeight) {
    return boardHeight >= Reversi::minimumBoardSize && boardHeight % 2 == 0;
}

bool Reversi::isAValidWidth(const uint32_t boardWidth) {
    return Reversi::isAValidHeight(boardWidth);
}

void Reversi::validateMove(const std::vector<int> &move) const {
    BoardGame::validateMove(move);

    if (move.size() != 2) throw incorrect_format();

    const int row = move[0];
    const int col = move[1];

    //Já existe peça
    if (this->board.getSymbol(row, col) != Board::emptyCell) throw invalid_move();

    //Pegando o simbolo do jogador atual
    const char currentPlayerSymbol = this->whoseTurn().getSymbol();
    //Verifica se a jogada é valida
    if (!isAnyDirectionValid(row, col, currentPlayerSymbol)) {
        throw invalid_move();
    }
}

void Reversi::makeMove(const std::vector<int> &move, const char symbol) {
    BoardGame::makeMove(move, symbol);
    flipPieces(move, symbol);
}

GameState Reversi::getGameState() const {
    // Verifica se há movimentos válidos para qualquer jogador
    if ((!hasValidMoves(player1.getSymbol()) && this->whoseTurn().getSymbol() == player1.getSymbol()) ||
        (!hasValidMoves(player2.getSymbol()) && this->whoseTurn().getSymbol() == player2.getSymbol())) {
        // Contar peças para determinar o vencedor
        int player1Count = 0;
        int player2Count = 0;
        for (int row = 0; row < this->board.getHeight(); ++row) {
            for (int col = 0; col < this->board.getWidth(); ++col) {
                if (this->board.getSymbol(row, col) == player1.getSymbol()) {
                    ++player1Count;
                } else if (this->board.getSymbol(row, col) == player2.getSymbol()) {
                    ++player2Count;
                }
            }
        }

        if (player1Count > player2Count) return GameState::PLAYER1_WINS;

        if (player2Count > player1Count) return GameState::PLAYER2_WINS;

        return GameState::TIE;
    }

    return GameState::NOT_OVER;
}

void Reversi::flipPieces(const std::vector<int>& move, const char playerSymbol) {
    const int row = move[0];
    const int col = move[1];
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

bool Reversi::isValidDirection(const int row, const int col, const int directionRow, const int directionCol, const char playerSymbol) const {
    int r = row + directionRow;
    int c = col + directionCol;
    const char opponentSymbol = (playerSymbol == player1.getSymbol()) ? player2.getSymbol() : player1.getSymbol();

    if (!isWithinBounds(r, c) || this->board.getSymbol(r, c) != opponentSymbol) {
        return false;
    }

    r += directionRow;
    c += directionCol;

    while (isWithinBounds(r, c)) {
        if (this->board.getSymbol(r, c) == Board::emptyCell) {
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

void Reversi::flipInDirection(const int row, const int col, const int directionRow, const int directionCol, const char playerSymbol) {
    int r = row + directionRow;
    int c = col + directionCol;
    while (this->board.getSymbol(r, c) != playerSymbol) {
        this->board.placeSymbol({r, c}, playerSymbol);
        r += directionRow;
        c += directionCol;
    }
}

bool Reversi::isAnyDirectionValid(const int row, const int col, const char playerSymbol) const {
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

bool Reversi::isWithinBounds(const int row, const int col) const {
    return row >= 0 && row < this->board.getHeight() && col >= 0 && col < this->board.getWidth();
}

bool Reversi::hasValidMoves(const char playerSymbol) const {
    for (int row = 0; row < this->board.getHeight(); ++row) {
        for (int col = 0; col < this->board.getWidth(); ++col) {
            if (this->board.getSymbol(row, col) == Board::emptyCell && isAnyDirectionValid(row, col, playerSymbol)) {
                return true;
            }
        }
    }
    return false;
}
