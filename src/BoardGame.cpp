//
// Created by pires on 6/28/2024.
//

#include "BoardGame.hpp"

#include <iostream>

BoardGame::BoardGame(
    Player& _player1, Player& _player2, const int _boardWidth, const int _boardHeight, const char symbol1,
    const char symbol2
    ): player1(_player1), player2(_player2), boardWidth(_boardWidth), boardHeight(_boardHeight) {
    this->board = std::vector<std::vector<char>>(
        this->boardHeight, std::vector<char>(this->boardWidth, ' ')
        );

    player1.setSymbol(symbol1);
    player2.setSymbol(symbol2);
}

void BoardGame::printBoard() const {
    for (int i = 0; i < this->boardHeight; i++) { // Each line
        for (int j = 0; j < this->boardWidth; j++) { // Each column
            std::cout << this->board[i][j];
            if (j < this->boardWidth - 1) std::cout << '|';
        }

        std::cout << std::endl;

        if (i < this->boardHeight - 1) { // Not the last line
            for (int j = 0; j < this->boardWidth; j++) { //
                std::cout << '-';
                if (j < this->boardWidth - 1) std::cout << '+'; // Intersections
            }

            std::cout << std::endl;
        }
    }
}

std::vector<int> BoardGame::readMove() {
    // Read all inputted numbers separated by spaces and add to the vector
    std::vector<int> move;
    int value;
    while (std::cin >> value) {
        move.push_back(value);
    }
    return move;
}

int BoardGame::isMoveValid(const std::vector<int>& move) const {
    if (move.empty() || (move.size() > 2)) return BoardGame::incorrectFormat;

    if (move.size() == 1) {
        if ((move[0] < 0) || (move[0] >= this->boardWidth)) return BoardGame::invalidMove; // Verifica coluna
    }

    if (move.size() == 2) {
        if ((move[0] < 0) || (move[0] >= this->boardHeight)) return BoardGame::invalidMove; // Verifica linha
        if ((move[1] < 0) || (move[1] >= this->boardWidth)) return BoardGame::invalidMove; // Verifica coluna
    }

    return BoardGame::validMove;
}

void BoardGame::makeMove(const std::vector<int>& move, const char symbol) {
    if (move.size() == 2)
        this->board[move[1]][move[0]] = symbol;
    else {
        // Place the piece in the first empty space of the column
        for (int i = this->boardHeight - 1; i >= 0; i--) {
            if (this->board[i][move[0]] == ' ') {
                this->board[i][move[0]] = symbol;
                break;
            }
        }
    }
}

int BoardGame::getGameState() const {
    // Check if board is full
    for (int i = 0; i < this->boardHeight; i++) {
        for (int j = 0; j < this->boardWidth; j++) {
            if (this->board[i][j] == ' ') return BoardGame::notOver; // Game is not over
        }
    }

    return BoardGame::tie; // Tie
}

Player& BoardGame::whoseTurn(const int turn) const {
    return (turn%2 != 0 ? this->player1 : this->player2);
}

void BoardGame::playGame() {
    int turn = 0;

    while (true) {
        turn++;

        #ifdef WINDOWS
        system("cls");
        #else
        system("clear");
        #endif

        this->printBoard();

        // Verifica o estado do jogo
        const int gameState = this->getGameState();
        if (gameState != BoardGame::notOver) {
            if (gameState == BoardGame::tie) std::cout << "O jogo empatou!" << std::endl;
            else if (gameState == BoardGame::player1Wins) std::cout << player1.getNick() << " wins!" << std::endl;
            else if (gameState == BoardGame::player2Wins) std::cout << player2.getNick() << " wins!" << std::endl;
            break;
        }

        // Realiza a jogada
        Player& turnPlayer = this->whoseTurn(turn);
        while (true) {
            std::cout << "Turno de jogador " << turnPlayer.getName() << ": ";
            std::vector<int> move = BoardGame::readMove();

            const int moveValidation = this->isMoveValid(move);
            if (moveValidation != BoardGame::validMove) {
                if (moveValidation == BoardGame::invalidMove) std::cout << "ERRO: jogada inválida" << std::endl;
                else if (moveValidation == BoardGame::incorrectFormat) std::cout << "ERRO: formato incorreto" << std::endl;
                continue;
            }

            this->makeMove(move, turnPlayer.getSymbol());

            break;
        }
    }
}