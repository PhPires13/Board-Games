#include "Reversi.hpp"  // Inclui o cabeçalho que contém as declarações da classe Reversi.
#include "exceptions.hpp"

const uint32_t Reversi::minimumBoardSize = 4;  // Define the minimum board size as 4.
const uint32_t Reversi::defaultBoardSize = 8;  // Define the default board size as 8.

Reversi::Reversi(Player _player1, Player _player2, uint32_t boardSize)
    : BoardGame(std::move(_player1), std::move(_player2), 
                (Reversi::isAValidHeight(boardSize) ? boardSize : Reversi::defaultBoardSize),  // Define the board height.
                (Reversi::isAValidWidth(boardSize) ? boardSize : Reversi::defaultBoardSize),   // Define the board width.
                "\033[38;2;255;255;0m", "\033[38;2;255;255;255m", "\033[30m",                 // Define players colors.
                "\033[48;2;0;150;23m", "\033[48;2;0;100;15m") {                               // Define board colors.
    if (!Reversi::isAValidHeight(boardSize))
        boardSize = Reversi::defaultBoardSize;  // If the board size is not valid, use the default size.

    const uint32_t mid = boardSize / 2;  // Calculate the board central position.

    // Initialize the board with the starting pieces in its middle.
    this->board.placeSymbol({mid - 1, mid - 1}, player1.getSymbol());
    this->board.placeSymbol({mid - 1, mid}, player2.getSymbol());
    this->board.placeSymbol({mid, mid - 1}, player2.getSymbol());
    this->board.placeSymbol({mid, mid}, player1.getSymbol());
}

bool Reversi::isAValidHeight(const uint32_t boardHeight) const {
    /**
     * Check if the board's height is valid.
     *
     * @param boardHeight
     * @return true if it is as valid height.
     */
    return boardHeight >= Reversi::minimumBoardSize && boardHeight % 2 == 0;
}

bool Reversi::isAValidWidth(const uint32_t boardWidth) const {
     /**
      * Check if the board's width is valid.
      *
      * @param boardWidth
      * @return true if it is as valid height.
      */
    return Reversi::isAValidHeight(boardWidth);
}

void Reversi::validateMove(const std::vector<uint32_t> &move) const {
    /**
     * Check if the move made is valid, according to Reversi rules.
     *
     * @param move Move coordinates (row, column)
     * @throws incorrect_format if the move is empty, has more than 2 values and less than 1 value.
     * @throws invalid_move if the move is invalid.
     */
    BoardGame::validateMove(move);  // Validate the move using the base game rules.

    if (move.size() != 2) throw incorrect_format();  // Check if the move has exactly two coordinates (row, column).

    const int row = move[0];
    const int col = move[1];

    // Check if the cell is already filled.
    if (this->board.getSymbol(row, col) != Board::emptyCell) throw invalid_move();

    // Get the symbol of the current player.
    const char currentPlayerSymbol = this->whoseTurn().getSymbol();
    
    // Check if the move is valid in any direction.
    if (!isAnyDirectionValid(row, col, currentPlayerSymbol)) {
        throw invalid_move();  // If it is not valid, throw exception invalid_move.
    }
}

void Reversi::makeMove(const std::vector<uint32_t> &move, const char symbol) {
     /**
      * Execute the move and flip the necessary pieces.
      *
      * @param move Move coordinates
      * @param symbol Symbol of the player who made the move
      */
    BoardGame::makeMove(move, symbol);  // Make the move on the board.
    flipPieces(move, symbol);  // Flip the opponent pieces surrounded by current symbol.
}

GameState Reversi::getGameState(const std::vector<uint32_t>& move) const {
    // Check if there are valid moves for any player.
    if ((!hasValidMoves(player1.getSymbol()) && this->whoseTurn().getSymbol() == player1.getSymbol()) ||
        (!hasValidMoves(player2.getSymbol()) && this->whoseTurn().getSymbol() == player2.getSymbol())) {
        
        // Count the pieces of each player to determine the winner.
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

        if (player1Count > player2Count) return GameState::PLAYER1_WINS;  // Return Player 1 Wins.
        if (player2Count > player1Count) return GameState::PLAYER2_WINS;  // Return Player 2 Wins.

        return GameState::TIE;  // Return tie.
    }

    return GameState::NOT_OVER;  // The game is not over.
}

void Reversi::flipPieces(const std::vector<uint32_t>& move, const char playerSymbol) {
    /**
     * Flip the opponent pieces according to Reversi rules, after a valid move.
     *
     * @param move Move coordinates
     * @param playerSymbol Symbol of the player who made the move
     */
    const int row = move[0];
    const int col = move[1];
    for (int directionRow = -1; directionRow <= 1; ++directionRow) {
        for (int directionCol = -1; directionCol <= 1; ++directionCol) {
            if (directionRow != 0 || directionCol != 0) {
                // Check if the direction is valid to flip pieces.
                if (isValidDirection(row, col, directionRow, directionCol, playerSymbol)) {
                    flipInDirection(row, col, directionRow, directionCol, playerSymbol);
                }
            }
        }
    }
}

bool Reversi::isValidDirection(const int row, const int col, const int directionRow, const int directionCol, const char playerSymbol) const {
    /**
     * Check a specific direction from a valid position to flip the pieces.
     *
     * @param row Move row
     * @param col Move column
     * @param directionRow Line direction (-1, 0, 1)
     * @param directionCol Column direction (-1, 0, 1)
     * @param playerSymbol Symbol of the current player
     * @return true if it is a valid direction
     */
    int r = row + directionRow;
    int c = col + directionCol;
    const char opponentSymbol = (playerSymbol == player1.getSymbol()) ? player2.getSymbol() : player1.getSymbol();

    // Check if the initial position of the direction has an opponent piece.
    if (!isWithinBounds(r, c) || this->board.getSymbol(r, c) != opponentSymbol) {
        return false;
    }

    r += directionRow;
    c += directionCol;

    // Scroll in the specified direction to check if there is one current player piece.
    while (isWithinBounds(r, c)) {
        if (this->board.getSymbol(r, c) == Board::emptyCell) {
            return false;
        }
        if (this->board.getSymbol(r, c) == playerSymbol) {
            return true;  // Valid direction.
        }
        r += directionRow;
        c += directionCol;
    }

    return false;
}

void Reversi::flipInDirection(const int row, const int col, const int directionRow, const int directionCol, const char playerSymbol) {
    /**
     * Flip the opponent pieces in a specific direction.
     *
     * @param row Move row
     * @param col Move column
     * @param directionRow Line direction (-1, 0, 1)
     * @param directionCol Column direction (-1, 0, 1)
     * @param playerSymbol Symbol of the current player
     */
    uint32_t r = row + directionRow;
    uint32_t c = col + directionCol;
    while (this->board.getSymbol(r, c) != playerSymbol) {
        // Flip the piece on the specified direction until it finds the current player piece.
        this->board.placeSymbol({r, c}, playerSymbol);
        r += directionRow;
        c += directionCol;
    }
}

bool Reversi::isAnyDirectionValid(const int row, const int col, const char playerSymbol) const {
    /**
     * Check if there is any valid direction for the given move.
     *
     * @param row Move row
     * @param col Move column
     * @param playerSymbol Symbol of the current player
     * @return true if there is at least one valid direction.
     */
    for (int directionRow = -1; directionRow <= 1; directionRow++) {
        for (int directionCol = -1; directionCol <= 1; directionCol++) {
            // Check all directions (except for (0,0) which is invalid).
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
     * Check if the coordinates are inside the board edges.
     *
     * @param row Row to be checked
     * @param col Column to be checked.
     * @return true if the coordinates are insde the board edges.
     */
    return row >= 0 && row < this->board.getHeight() && col >= 0 && col < this->board.getWidth();
}

bool Reversi::hasValidMoves(const char playerSymbol) const {
    /**
     * Check if there are still possiblemoves for a given player.
     *
     * @param playerSymbol Player symbol
     * @return true if there are still available valid moves.
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
