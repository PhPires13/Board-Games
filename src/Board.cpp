//
// Created by pedro-pires on 7/9/24.
//

#include "Board.hpp"

#include <iostream>
#include <utility>

#include "exceptions.hpp"

const char Board::emptyCell = ' ';

const uint32_t Board::maxBoardSize = 12;

Board::Board(const uint32_t _height, const uint32_t _width, std::string indexColor, std::string piecesColor,
    std::string borderColor, std::string evenBg, std::string oddBg
    ): height(_height), width(_width), indexColor(std::move(indexColor)), piecesColor(std::move(piecesColor)),
       borderColor(std::move(borderColor)), evenBg(std::move(evenBg)), oddBg(std::move(oddBg)) {
    if (_height <= 0 || _width <= 0) throw incorrect_data();
    if (_height > Board::maxBoardSize || _width > Board::maxBoardSize) throw incorrect_data();

    // Initializa o tabuleiro vazio
    this->board = std::vector<std::vector<char>>(
        this->height, std::vector<char>(this->width, Board::emptyCell)
        );
}

uint32_t Board::getWidth() const {
    return this->width;
}

uint32_t Board::getHeight() const {
    return this->height;
}

void Board::print() const {
    const std::string RESET = "\033[0m";
    const std::string BOLD = "\033[1m";

    // Print column indexes above the lines
    std::cout << "   ";
    for (int column = 0; column < this->width; column++) {
        std::cout << this->indexColor << "  " << column << "  " << RESET;
        if (column < this->width - 1) std::cout << ' ';
    }
    std::cout << std::endl;

    // Print upper border
    std::cout << "   ";
    for (int column = 0; column < this->width; column++) { // Each column
        std::cout << this->borderColor << "=====" << RESET;
        if (column < this->width - 1) std::cout << this->borderColor << '=' << RESET;
    }
    std::cout << std::endl;

    for (int line = 0; line < this->height; line++) { // Each line
        // Print the line index
        std::cout << this->indexColor << line << "  " << RESET;

        // Print the line content
        for (int column = 0; column < this->width; column++) { // Each column
            // Alternate background colors
            std::string bgColor = (line + column) % 2 == 0 ? this->evenBg : this->oddBg;
            std::cout << bgColor << BOLD << this->piecesColor << "  " << this->board[line][column] << "  " << RESET;
            if (column < this->width - 1) std::cout << this->borderColor << '|' << RESET;
        }
        std::cout << std::endl;

        // Print the line border
        if (line < this->height - 1) { // Not the last line
            std::cout << "   ";
            for (int column = 0; column < this->width; column++) { //
                std::cout << this->borderColor << "-----" << RESET;
                if (column < this->width - 1) std::cout << this->borderColor << '+' << RESET; // Intersections
            }
            std::cout << std::endl;
        }
    }

    // Print the lower border
    std::cout << "   ";
    for (int column = 0; column < this->width; column++) { // Each column
        std::cout << borderColor << "=====" << RESET;
        if (column < this->width - 1) std::cout << borderColor << '=' << RESET;
    }
    std::cout << std::endl;
}

char Board::getSymbol(const uint32_t line, const uint32_t column) const {
    if (line >= this->height || column >= this->width) throw invalid_move();
    return this->board[line][column];
}

void Board::placeSymbol(const std::vector<uint32_t>& move, const char symbol) {
    if (move.size() == 2) {
        if (move[0] >= this->height || move[1] >= this->width) throw invalid_move();
        this->board[move[0]][move[1]] = symbol;
    } else {
        if (move[0] >= this->width) throw invalid_move();
        // Place the piece in the first empty space of the column
        for (int i = this->height - 1; i >= 0; i--) {
            if (this->board[i][move[0]] == Board::emptyCell) {
                this->board[i][move[0]] = symbol;
                break;
            }
        }
    }
}
