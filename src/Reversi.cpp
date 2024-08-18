#include "Reversi.hpp"  // Inclui o cabeçalho que contém as declarações da classe Reversi.
#include <iostream>     // Inclui a biblioteca para entrada e saída padrão.
#include "exceptions.hpp"

const uint32_t Reversi::minimumBoardSize = 4;  // Define o tamanho mínimo do tabuleiro como 4.
const uint32_t Reversi::defaultBoardSize = 8;  // Define o tamanho padrão do tabuleiro como 8.

Reversi::Reversi(Player _player1, Player _player2, uint32_t boardSize)
    : BoardGame(std::move(_player1), std::move(_player2), 
                (Reversi::isAValidHeight(boardSize) ? boardSize : Reversi::defaultBoardSize),  // Define a altura do tabuleiro.
                (Reversi::isAValidWidth(boardSize) ? boardSize : Reversi::defaultBoardSize),   // Define a largura do tabuleiro.
                "\033[38;2;255;255;0m", "\033[38;2;255;255;255m", "\033[30m",                 // Define as cores dos jogadores.
                "\033[48;2;0;150;23m", "\033[48;2;0;100;15m") {                               // Define as cores do tabuleiro.
    if (!Reversi::isAValidHeight(boardSize))
        boardSize = Reversi::defaultBoardSize;  // Se o tamanho do tabuleiro não for válido, usa o tamanho padrão.

    const uint32_t mid = boardSize / 2;  // Calcula a posição central do tabuleiro.

    // Inicializa o tabuleiro com as peças iniciais no meio.
    this->board.placeSymbol({mid - 1, mid - 1}, player1.getSymbol());
    this->board.placeSymbol({mid - 1, mid}, player2.getSymbol());
    this->board.placeSymbol({mid, mid - 1}, player2.getSymbol());
    this->board.placeSymbol({mid, mid}, player1.getSymbol());
}

bool Reversi::isAValidHeight(const uint32_t boardHeight) const {
    /**
     * Verifica se a altura do tabuleiro é válida.
     *
     * @param boardHeight Altura do tabuleiro
     * @return true se a altura é maior ou igual ao tamanho mínimo e é um número par, false caso contrário
     */
    return boardHeight >= Reversi::minimumBoardSize && boardHeight % 2 == 0;
}

bool Reversi::isAValidWidth(const uint32_t boardWidth) const {
    /**
     * Verifica se a largura do tabuleiro é válida.
     *
     * @param boardWidth Largura do tabuleiro
     * @return true se a largura é válida, false caso contrário
     */
    return Reversi::isAValidHeight(boardWidth);
}

void Reversi::validateMove(const std::vector<uint32_t> &move) const {
    /**
     * Valida o movimento dado de acordo com as regras do jogo Reversi.
     *
     * @param move Vetor com as coordenadas do movimento (linha e coluna)
     * @throw incorrect_format se o movimento não tiver exatamente duas coordenadas
     * @throw invalid_move se o movimento não for válido
     */
    BoardGame::validateMove(move);  // Valida o movimento usando as regras do jogo base.

    if (move.size() != 2) throw incorrect_format();  // Verifica se o movimento tem exatamente duas coordenadas (linha, coluna).

    const int row = move[0];
    const int col = move[1];

    // Verifica se a célula já está ocupada.
    if (this->board.getSymbol(row, col) != Board::emptyCell) throw invalid_move();

    // Obtém o símbolo do jogador atual.
    const char currentPlayerSymbol = this->whoseTurn().getSymbol();
    
    // Verifica se o movimento é válido em qualquer direção.
    if (!isAnyDirectionValid(row, col, currentPlayerSymbol)) {
        throw invalid_move();  // Se não for válido, lança exceção de movimento inválido.
    }
}

void Reversi::makeMove(const std::vector<uint32_t> &move, const char symbol) {
    /**
     * Executa o movimento no tabuleiro e vira as peças do oponente conforme necessário.
     *
     * @param move Coordenadas do movimento
     * @param symbol Símbolo do jogador que está realizando o movimento
     */
    BoardGame::makeMove(move, symbol);  // Faz o movimento no tabuleiro.
    flipPieces(move, symbol);  // Vira as peças do oponente cercadas pelo símbolo atual.
}

GameState Reversi::getGameState(const std::vector<uint32_t>& move) const {
    // Verifica se há movimentos válidos para qualquer jogador
    if ((!hasValidMoves(player1.getSymbol()) && this->whoseTurn().getSymbol() == player1.getSymbol()) ||
        (!hasValidMoves(player2.getSymbol()) && this->whoseTurn().getSymbol() == player2.getSymbol())) {
        
        // Conta as peças de cada jogador para determinar o vencedor.
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

        if (player1Count > player2Count) return GameState::PLAYER1_WINS;  // Retorna vitória do jogador 1.
        if (player2Count > player1Count) return GameState::PLAYER2_WINS;  // Retorna vitória do jogador 2.

        return GameState::TIE;  // Retorna empate.
    }

    return GameState::NOT_OVER;  // O jogo ainda não acabou.
}

void Reversi::flipPieces(const std::vector<uint32_t>& move, const char playerSymbol) {
    /**
     * Vira as peças do oponente de acordo com as regras do Reversi, após um movimento válido.
     *
     * @param move Coordenadas do movimento
     * @param playerSymbol Símbolo do jogador que fez o movimento
     */
    const int row = move[0];
    const int col = move[1];
    for (int directionRow = -1; directionRow <= 1; ++directionRow) {
        for (int directionCol = -1; directionCol <= 1; ++directionCol) {
            if (directionRow != 0 || directionCol != 0) {
                // Verifica se a direção é válida para virar peças.
                if (isValidDirection(row, col, directionRow, directionCol, playerSymbol)) {
                    flipInDirection(row, col, directionRow, directionCol, playerSymbol);
                }
            }
        }
    }
}

bool Reversi::isValidDirection(const int row, const int col, const int directionRow, const int directionCol, const char playerSymbol) const {
    /**
     * Verifica se uma direção específica a partir de uma posição é válida para virar peças.
     *
     * @param row Linha de origem do movimento
     * @param col Coluna de origem do movimento
     * @param directionRow Direção na linha (-1, 0, 1)
     * @param directionCol Direção na coluna (-1, 0, 1)
     * @param playerSymbol Símbolo do jogador atual
     * @return true se a direção é válida, false caso contrário
     */
    int r = row + directionRow;
    int c = col + directionCol;
    const char opponentSymbol = (playerSymbol == player1.getSymbol()) ? player2.getSymbol() : player1.getSymbol();

    // Verifica se a posição inicial da direção contém uma peça do oponente.
    if (!isWithinBounds(r, c) || this->board.getSymbol(r, c) != opponentSymbol) {
        return false;
    }

    r += directionRow;
    c += directionCol;

    // Percorre na direção especificada para verificar se há uma peça do jogador atual.
    while (isWithinBounds(r, c)) {
        if (this->board.getSymbol(r, c) == Board::emptyCell) {
            return false;
        }
        if (this->board.getSymbol(r, c) == playerSymbol) {
            return true;  // Direção válida.
        }
        r += directionRow;
        c += directionCol;
    }

    return false;
}

void Reversi::flipInDirection(const int row, const int col, const int directionRow, const int directionCol, const char playerSymbol) {
    /**
     * Vira as peças do oponente em uma direção específica.
     *
     * @param row Linha de origem do movimento
     * @param col Coluna de origem do movimento
     * @param directionRow Direção na linha (-1, 0, 1)
     * @param directionCol Direção na coluna (-1, 0, 1)
     * @param playerSymbol Símbolo do jogador atual
     */
    uint32_t r = row + directionRow;
    uint32_t c = col + directionCol;
    while (this->board.getSymbol(r, c) != playerSymbol) {
        // Vira a peça na direção especificada até encontrar uma peça do jogador atual.
        this->board.placeSymbol({r, c}, playerSymbol);
        r += directionRow;
        c += directionCol;
    }
}

bool Reversi::isAnyDirectionValid(const int row, const int col, const char playerSymbol) const {
    /**
     * Verifica se existe alguma direção válida para o movimento dado.
     *
     * @param row Linha de origem do movimento
     * @param col Coluna de origem do movimento
     * @param playerSymbol Símbolo do jogador atual
     * @return true se ao menos uma direção for válida, false caso contrário
     */
    for (int directionRow = -1; directionRow <= 1; directionRow++) {
        for (int directionCol = -1; directionCol <= 1; directionCol++) {
            // Verifica todas as direções (exceto a direção (0,0) que é inválida).
            if (directionRow != 0 || directionCol != 0) {
                if (isValidDirection(row, col, directionRow, directionCol, playerSymbol)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Reversi::isWithinBounds(const int row, const int col) const {
    /**
     * Verifica se as coordenadas estão dentro dos limites do tabuleiro.
     *
     * @param row Linha a ser verificada
     * @param col Coluna a ser verificada
     * @return true se as coordenadas estão dentro dos limites, false caso contrário
     */
    return row >= 0 && row < this->board.getHeight() && col >= 0 && col < this->board.getWidth();
}

bool Reversi::hasValidMoves(const char playerSymbol) const {
    /**
     * Verifica se ainda existem movimentos válidos para um determinado jogador.
     *
     * @param playerSymbol Símbolo do jogador
     * @return true se há movimentos válidos disponíveis, false caso contrário
     */
    for (int row = 0; row < this->board.getHeight(); ++row) {
        for (int col = 0; col < this->board.getWidth(); ++col) {
            if (this->board.getSymbol(row, col) == Board::emptyCell && isAnyDirectionValid(row, col, playerSymbol)) {
                return true;
            }
        }
    }
    return false;
}
