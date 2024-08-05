//
// Created by pedro-pires on 7/9/24.
//

#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

class Board final {
    uint32_t height;
    uint32_t width;
    std::vector<std::vector<char>> board;

public:
    static const char emptyCell;

    /**
     *
     * @param _height board height
     * @param _width board width
     */
    Board(uint32_t _height, uint32_t _width);

    /**
     *
     * @return board width
     */
    uint32_t getWidth() const;

    /**
     *
     * @return board height
     */
    uint32_t getHeight() const;

    /**
     * Print the current board state
     */
    void print() const;

    /**
     *
     * @param line
     * @param column
     * @return the symbol at the given position
     */
    char getSymbol(int line, int column) const;

    /**
     * Place symbol in the board, falling on the column or in the given coordinates
     * @param move vector with coordinates to place the symbol dim: 1-2
     * @param symbol symbol to be placed
     */
    void placeSymbol(const std::vector<int>& move, char symbol);
};

#endif //BOARD_HPP
