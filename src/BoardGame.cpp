//
// Created by pires on 6/28/2024.
//

#include "BoardGame.hpp"

#include <iostream>
#include <sstream>
#include <utility>

#include "exceptions.hpp"
#include "Utils.hpp"

const uint32_t BoardGame::defaultBoardHeight = 4;
const uint32_t BoardGame::defaultBoardWidth = 4;

const char BoardGame::defaultSymbol1 = 'X';
const char BoardGame::defaultSymbol2 = 'O';

BoardGame::BoardGame(Player _player1, Player _player2, const uint32_t boardHeight, const uint32_t boardWidth,
    const std::string& indexColor, const std::string& piecesColor, const std::string& borderColor,
    const std::string& evenBg, const std::string& oddBg
): player1(std::move(_player1)), player2(std::move(_player2)), board(boardHeight, boardWidth, indexColor, piecesColor, borderColor, evenBg, oddBg), turn(0) {
    // If player has no symbol
    if (player1.getSymbol() == 0) player1.setSymbol(BoardGame::defaultSymbol1);
    if (player2.getSymbol() == 0) player2.setSymbol(BoardGame::defaultSymbol2);

    // Check if the players have the same symbol
    if (player1.getSymbol() == player2.getSymbol()) {
        // Change temporarily all the symbols to the default ones
        player1.setSymbol(BoardGame::defaultSymbol1);
        player2.setSymbol(BoardGame::defaultSymbol2);
    }
}

bool BoardGame::isAValidHeight(const uint32_t boardHeight) const {
    return boardHeight > 0;
}

bool BoardGame::isAValidWidth(const uint32_t boardWidth) const {
    return BoardGame::isAValidHeight(boardWidth);
}

void BoardGame::printBoard() const {
    this->board.print();
}

std::vector<uint32_t> BoardGame::readMove() {
    // Read all inputted numbers separated by spaces and add to the vector
    std::vector<uint32_t> move;

    std::string line;
    std::getline(std::cin, line);
    line = Utils::cleanString(line);
    std::stringstream lineStream(line);

    std::string token;
    while (lineStream >> token) {
        try {
            std::stringstream tokenStream(token);
            uint32_t value;
            tokenStream >> value;
            if (tokenStream.fail() || !tokenStream.eof()) throw incorrect_format();
            move.push_back(value);
        } catch (const std::exception& e) {}
    }

    return move;
}

void BoardGame::validateMove(const std::vector<uint32_t>& move) const {
    // Move input size
    if (move.empty() || (move.size() > 2)) throw incorrect_format();

    // If move is inside board
    if (move.size() == 1) {
        if (move[0] >= this->board.getWidth()) throw invalid_move(); // Verifica coluna
    } else if (move.size() == 2) {
        if (move[0] >= this->board.getHeight()) throw invalid_move(); // Verifica linha
        if (move[1] >= this->board.getWidth()) throw invalid_move(); // Verifica coluna
    }
}

void BoardGame::makeMove(const std::vector<uint32_t>& move, const char symbol) {
    this->board.placeSymbol(move, symbol);
}

GameState BoardGame::getGameState(const std::vector<uint32_t>& move) const {
    // Check if board is full
    for (int i = 0; i < this->board.getHeight(); i++) {
        for (int j = 0; j < this->board.getWidth(); j++) {
            if (this->board.getSymbol(i, j) == Board::emptyCell) return GameState::NOT_OVER; // Game is not over
        }
    }

    return GameState::TIE; // Tie
}

Player BoardGame::whoseTurn() const {
    return (this->turn%2 != 0 ? this->player1 : this->player2);
}

GameState BoardGame::playGame() {
    std::vector<uint32_t> move = {};

    while (true) {
        turn++;

        Utils::clearTerminal();

        this->printBoard();

        // Check game state
        const GameState gameState = this->getGameState(move);
        if (gameState != GameState::NOT_OVER) {
            if (gameState == GameState::TIE) std::cout << "O jogo empatou!" << std::endl;
            else if (gameState == GameState::PLAYER1_WINS) std::cout << player1.getNick() << " ganhou!" << std::endl;
            else if (gameState == GameState::PLAYER2_WINS) std::cout << player2.getNick() << " ganhou!" << std::endl;

            return gameState;
        }

        // Make the move
        Player turnPlayer = this->whoseTurn();
        while (true) { // While it is valid
            std::cout << "Turno de jogador " << turnPlayer.getNick() << ": ";
            move = BoardGame::readMove();

            try {
                this->validateMove(move);
            } catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                continue;
            }

            this->makeMove(move, turnPlayer.getSymbol());

            break;
        }
    }
}