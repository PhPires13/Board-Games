//
// Created by Carlos Eduardo Machado on 15/08/2024.
//

#include "ConnectFour.hpp"
#include "exceptions.hpp"
#include <vector>

const uint32_t ConnectFour::minimumBoardSize = 4;
const uint32_t ConnectFour::defaultBoardHeight = 6;
const uint32_t ConnectFour::defaultBoardWidth = 7;

ConnectFour::ConnectFour(Player _player1, Player _player2, uint32_t boardHeight, uint32_t boardWidth)
: BoardGame(std::move(_player1), std::move(_player2),
        (ConnectFour::isAValidHeight(boardHeight) ? boardHeight : ConnectFour::defaultBoardHeight),
        (ConnectFour::isAValidWidth(boardWidth) ? boardWidth : ConnectFour::defaultBoardWidth),
        "\033[38;5;11m", "\033[38;2;255;0;0m",
        "\033[38;2;0;159;235m", "\033[48;2;240;240;240m", "\033[48;2;240;240;240m") {
}

bool ConnectFour::isAValidHeight(const uint32_t boardHeight) {
    return boardHeight >= ConnectFour::minimumBoardSize;
}

bool ConnectFour::isAValidWidth(const uint32_t boardWidth) {
    return ConnectFour::isAValidHeight(boardWidth);
}

void ConnectFour::validateMove(const std::vector<int> &move) const {
    //Verify if the move is inside the board dimensions
    BoardGame::validateMove(move);

    //Move input size
    if(move.size() != 1) throw incorrect_format();

    //Verifiy if the selected column is full
    if(this->board.getSymbol(0,move[0])!=Board::emptyCell)
        throw invalid_move();
}

GameState ConnectFour::getGameState(const std::vector<int>& move) const {
    if (!move.empty()) {
        char currentSymbol = Board::emptyCell;
        std::vector<int> currentPosition;
        int i;
        //Geting the player's symbol who made the last move
        for (i = 0; i < this->board.getHeight(); i++) {
            currentSymbol = this->board.getSymbol(i, move[0]);
            if (currentSymbol != Board::emptyCell) break;
        }
        //Geting the symbol coordinates
        currentPosition.push_back(i);
        currentPosition.push_back(move[0]);

        //Verify if there is four equal symbols in a row/column/diagonal
        if(checkDirection(currentPosition,currentSymbol,0,1) || //Horizontal
        checkDirection(currentPosition,currentSymbol,1,0) || //Vertical
        checkDirection(currentPosition,currentSymbol,1,1) || //Diagonal /
        checkDirection(currentPosition,currentSymbol,1,-1)) //Diagonal \'
        {
            if(currentSymbol == player1.getSymbol()) return GameState::PLAYER1_WINS;

            return GameState::PLAYER2_WINS;
        }
    }
        return BoardGame::getGameState(move);
}

bool ConnectFour::checkDirection(const std::vector<int> &move, char symbol, int dRow, int dCol) const{
    int count = 0;
    int row = move[0];
    int col = move[1];

    // Check in the positive direction
    while (this->board.getSymbol(row,col) == symbol) {
        count++;
        row += dRow;
        col += dCol;
        std::vector<int> dMove = {row,col};
        //Verifying if the next place on the direction is part of the board
        try {
            BoardGame::validateMove(dMove);
        }catch (const invalid_move& e) {
            break;
        }
    }
    // Redefine positions
    row = move[0];
    col = move[1];

    // Check in the negative direction
    while (this->board.getSymbol(row,col) == symbol) {
        count++;
        row -= dRow;
        col -= dCol;
        std::vector<int> dMove = {row,col};
        //Verifying if the next place on the direction is part of the board
        try {
            BoardGame::validateMove(dMove);
        }catch (const invalid_move& e) {
            break;
        }
    }

    //Excluding the duplicated counter
    count--;

    return count >= 4;
}
