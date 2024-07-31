//
// Created by pires on 6/28/2024.
//

#include "BoardGame.hpp"

#include <iostream>
#include <sstream>

#include "Utils.hpp"

BoardGame::BoardGame(Player& _player1, Player& _player2, const int boardHeight, const int boardWidth
): player1(_player1), player2(_player2), board(boardHeight, boardWidth) {

    // Check if the players have the same symbol
    if (player1.getSymbol() == player2.getSymbol()) {
        // Change temporarily all the symbols to the default ones
        player1.setSymbol(BoardGame::defaultSymbol1);
        player2.setSymbol(BoardGame::defaultSymbol2);
    }
}

void BoardGame::printBoard() const {
    this->board.print();
}

std::vector<int> BoardGame::readMove() {
    // Read all inputted numbers separated by spaces and add to the vector
    std::vector<int> move;

    std::string line;
    std::getline(std::cin, line);
    line = Utils::removeNonAlphaNum(line);
    std::stringstream lineStream(line);

    int value;
    while (lineStream >> value) {
        move.push_back(value);
    }

    return move;
}

MoveStatus BoardGame::isMoveValid(const std::vector<int>& move) const {
    // Move input size
    if (move.empty() || (move.size() > 2)) return MoveStatus::INCORRECT_FORMAT;

    // If move is inside board
    if (move.size() == 1) {
        if ((move[0] < 0) || (move[0] >= this->board.getWidth())) return MoveStatus::INVALID_MOVE; // Verifica coluna
    } else if (move.size() == 2) {
        if ((move[0] < 0) || (move[0] >= this->board.getHeight())) return MoveStatus::INVALID_MOVE; // Verifica linha
        if ((move[1] < 0) || (move[1] >= this->board.getHeight())) return MoveStatus::INVALID_MOVE; // Verifica coluna
    }

    return MoveStatus::VALID_MOVE;
}

void BoardGame::makeMove(const std::vector<int>& move, const char symbol) {
    this->board.placeSymbol(move, symbol);
}

GameState BoardGame::getGameState() const {
    // Check if board is full
    for (int i = 0; i < this->board.getHeight(); i++) {
        for (int j = 0; j < this->board.getWidth(); j++) {
            if (this->board.getSymbol(i, j) == ' ') return GameState::NOT_OVER; // Game is not over
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

        #ifdef _WIN32
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