//
// Created by pedro-pires on 7/9/24.
//

#include "Board.hpp"

#include <iostream>

Board::Board(const int _height, const int _width): height(_height), width(_width) {
    // Initializa o tabuleiro vazio
    this->board = std::vector<std::vector<char>>(
        this->height, std::vector<char>(this->width, ' ')
        );
}

int Board::getWidth() const {
    return this->width;
}

int Board::getHeight() const {
    return this->height;
}

void Board::print() const {
    for (int line = 0; line < this->height; line++) { // Each line
        // Print upper border
        if (line == 0) {
            for (int column = 0; column < this->width; column++) { // Each column
                std::cout << "=====";
                if (column < this->width - 1) std::cout << '=';
            }
            std::cout << std::endl;
        }

        /// Print the line content
        for (int column = 0; column < this->width; column++) { // Each column
            std::cout << "  " << this->board[line][column] << "  ";
            if (column < this->width - 1) std::cout << '|';
        }
        std::cout << std::endl;

        // Print the line border
        if (line < this->height - 1) { // Not the last line
            for (int column = 0; column < this->width; column++) { //
                std::cout << "-----";
                if (column < this->width - 1) std::cout << '+'; // Intersections
            }
            std::cout << std::endl;
        } else { // Print the lower border
            for (int column = 0; column < this->width; column++) { // Each column
                std::cout << "=====";
                if (column < this->width - 1) std::cout << '=';
            }
            std::cout << std::endl;
        }
    }
}

char Board::getSymbol(const int line, const int column) const {
    return this->board[line][column];
}

void Board::placeSymbol(const std::vector<int>& move, const char symbol) {
    if (move.size() == 2)
        this->board[move[0]][move[1]] = symbol;
    else {
        // Place the piece in the first empty space of the column
        for (int i = this->height - 1; i >= 0; i--) {
            if (this->board[i][move[0]] == ' ') {
                this->board[i][move[0]] = symbol;
                break;
            }
        }
    }
}
