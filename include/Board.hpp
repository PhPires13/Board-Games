//
// Created by pedro-pires on 7/9/24.
//

#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

class Board final {
    int height;
    int width;
    std::vector<std::vector<char>> board;

public:
    /**
     *
     * @param _height board height
     * @param _width board width
     */
    Board(int _height, int _width);

    /**
     *
     * @return board width
     */
    int getWidth() const;

    /**
     *
     * @return board height
     */
    int getHeight() const;

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
