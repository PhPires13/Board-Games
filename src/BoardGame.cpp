//
// Created by pires on 6/28/2024.
//

#include "BoardGame.hpp"

#include <iostream>
#include <sstream>

BoardGame::BoardGame(
    Player& _player1, Player& _player2, const int _boardWidth, const int _boardHeight, const char symbol1,
    const char symbol2
    ): player1(_player1), player2(_player2), boardWidth(_boardWidth), boardHeight(_boardHeight) {
    // Initializa o tabuleiro vazio
    this->board = std::vector<std::vector<char>>(
        this->boardHeight, std::vector<char>(this->boardWidth, ' ')
        );

    // Define os simbolos para cada jogador
    player1.setSymbol(symbol1);
    player2.setSymbol(symbol2);
}

void BoardGame::printBoard() const {
    for (int line = 0; line < this->boardHeight; line++) { // Each line
        // Print upper border
        if (line == 0) {
            for (int column = 0; column < this->boardWidth; column++) { // Each column
                std::cout << "=====";
                if (column < this->boardWidth - 1) std::cout << '=';
            }
            std::cout << std::endl;
        }

        /// Print the line content
        for (int column = 0; column < this->boardWidth; column++) { // Each column
            std::cout << "  " << this->board[line][column] << "  ";
            if (column < this->boardWidth - 1) std::cout << '|';
        }
        std::cout << std::endl;

        // Print the line border
        if (line < this->boardHeight - 1) { // Not the last line
            for (int column = 0; column < this->boardWidth; column++) { //
                std::cout << "-----";
                if (column < this->boardWidth - 1) std::cout << '+'; // Intersections
            }
            std::cout << std::endl;
        } else { // Print the lower border
            for (int column = 0; column < this->boardWidth; column++) { // Each column
                std::cout << "=====";
                if (column < this->boardWidth - 1) std::cout << '=';
            }
            std::cout << std::endl;
        }
    }
}

std::vector<int> BoardGame::readMove() {
    // Read all inputted numbers separated by spaces and add to the vector
    std::vector<int> move;

    std::string line;
    std::getline(std::cin, line);
    std::stringstream lineStream(line);

    int value;
    while (lineStream >> value) {
        move.push_back(value);
    }

    return move;
}

MoveStatus BoardGame::isMoveValid(const std::vector<int>& move) const {
    if (move.empty() || (move.size() > 2)) return MoveStatus::INCORRECT_FORMAT;

    if (move.size() == 1) {
        if ((move[0] < 0) || (move[0] >= this->boardWidth)) return MoveStatus::INVALID_MOVE; // Verifica coluna
    }

    if (move.size() == 2) {
        if ((move[0] < 0) || (move[0] >= this->boardHeight)) return MoveStatus::INVALID_MOVE; // Verifica linha
        if ((move[1] < 0) || (move[1] >= this->boardWidth)) return MoveStatus::INVALID_MOVE; // Verifica coluna
    }

    return MoveStatus::VALID_MOVE;
}

void BoardGame::makeMove(const std::vector<int>& move, const char symbol) {
    if (move.size() == 2)
        this->board[move[0]][move[1]] = symbol;
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

GameState BoardGame::getGameState() const {
    // Check if board is full
    for (int i = 0; i < this->boardHeight; i++) {
        for (int j = 0; j < this->boardWidth; j++) {
            if (this->board[i][j] == ' ') return GameState::NOT_OVER; // Game is not over
        }
    }

    return GameState::TIE; // Tie
}

Player& BoardGame::whoseTurn(const int turn) const {
    return (turn%2 != 0 ? this->player1 : this->player2);
}

GameState BoardGame::playGame() {
    int turn = 0;

    while (true) {
        turn++;

        #ifdef WINDOWS
        system("cls");
        #else
        system("clear");
        #endif

        this->printBoard();

        // Check game satate
        const GameState gameState = this->getGameState();
        if (gameState != GameState::NOT_OVER) {
            if (gameState == GameState::TIE) std::cout << "O jogo empatou!" << std::endl;
            else if (gameState == GameState::PLAYER1_WINS) std::cout << player1.getNick() << " ganhou!" << std::endl;
            else if (gameState == GameState::PLAYER2_WINS) std::cout << player2.getNick() << " ganhou!" << std::endl;

            return gameState;
        }

        // Make the move
        Player& turnPlayer = this->whoseTurn(turn);
        while (true) { // While it is valid
            std::cout << "Turno de jogador " << turnPlayer.getName() << ": ";
            std::vector<int> move = BoardGame::readMove();

            const MoveStatus moveValidation = this->isMoveValid(move);
            if (moveValidation != MoveStatus::VALID_MOVE) {
                if (moveValidation == MoveStatus::INVALID_MOVE) std::cout << "ERRO: jogada inválida" << std::endl;
                else if (moveValidation == MoveStatus::INCORRECT_FORMAT) std::cout << "ERRO: formato incorreto" << std::endl;
                continue;
            }

            this->makeMove(move, turnPlayer.getSymbol());

            break;
        }
    }
}