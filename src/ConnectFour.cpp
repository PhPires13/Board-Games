//
// Created by Carlos Eduardo Machado on 15/08/2024.
//

#include "ConnectFour.hpp"
#include "exceptions.hpp"
#include <vector>

const uint32_t ConnectFour::minimumBoardSize = 4;
const uint32_t ConnectFour::defaultBoardSize = 4;

ConnectFour::ConnectFour(Player _player1, Player _player2, uint32_t boardSize
): BoardGame(std::move(_player1), std::move(_player2), (ConnectFour::isAValidHeight(boardSize) ? boardSize : ConnectFour::defaultBoardSize),
        (ConnectFour::isAValidWidth(boardSize) ? boardSize : ConnectFour::defaultBoardSize),
        "\033[38;2;255;255;0m", "\033[38;2;255;255;255m", "\033[30m", "\033[48;2;0;150;23m", "\033[48;2;0;100;15m") {
    if(!ConnectFour::isAValidHeight(boardSize))
        boardSize = ConnectFour::defaultBoardSize;
}

bool ConnectFour::isAValidHeight(const uint32_t boardHeight) {
    return boardHeight >= ConnectFour::minimumBoardSize;
}

bool ConnectFour::isAValidWidth(const uint32_t boardWidth) {
    return ConnectFour::isAValidHeight(boardWidth);
}

void ConnectFour::validateMove(const std::vector<int> &move) const {
    //Verify if the move is inside the board places
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
        for (int i = 0; i < this->board.getHeight(); i++) {
            currentSymbol = this->board.getSymbol(i, move[0]);
            if (currentSymbol != Board::emptyCell) break;
        }

        //Verify if there is four equal symbols in a row/column/diagonal
        // if(checkDirection(this->currentPosition,this->board.getSymbol(this->currentPosition[0],this->currentPosition[1]),this->currentSymbol,1,0) || //Horizontal
        // checkDirection(this->currentPosition,this->board.getSymbol(this->currentPosition[0],this->currentPosition[1]),this->currentSymbol,0,1) || //Vertical
        // checkDirection(this->currentPosition,this->board.getSymbol(this->currentPosition[0],this->currentPosition[1]),this->currentSymbol,1,1) || //Diagonal /'
        // checkDirection(this->currentPosition,this->board.getSymbol(this->currentPosition[0],this->currentPosition[1]),this->currentSymbol,1,-1)) //Diagonal \'
        // {
        //     if(this->board.getSymbol(currentPosition[0],currentPosition[1])==player1.getSymbol())
        //         return GameState::PLAYER1_WINS;
        //     else return GameState::PLAYER2_WINS;
        // }
    }

    return BoardGame::getGameState(move);
}

bool checkDirection(const std::vector<int> &move, char symbol, char pSymbol, int dRow, int dCol) {
    int count = 0;
    int row = move[0];
    int col = move[1];

    // Check in the positive direction
    while (pSymbol == symbol) {
        count++;
        row += dRow;
        col += dCol;
    }

    row = move[0];
    col = move[1];

    // Check in the negative direction
    while (pSymbol == symbol) {
        count++;
        row -= dRow;
        col -= dCol;
    }

    return count >= 4;
}
