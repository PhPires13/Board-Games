//
// Created by pedro-pires on 7/9/24.
//

#ifndef BOARD_HPP
#define BOARD_HPP

#include <cstdint>
#include <string>
#include <vector>

/**
 * Class to simulate a board, to place pieces
 */
class Board final {
    uint32_t height; /**< board height */
    uint32_t width; /**< board width */
    std::vector<std::vector<char>> board; /**< board matrix, to place chars as pieces */

    // ANSI escape codes for coloring
    const std::string indexColor; /**< color for the indexes */
    const std::string piecesColor; /**< color for the pieces */
    const std::string borderColor; /**< color for the border */

    // ANSI escape codes for background colors
    const std::string evenBg; /**< background color for the even cells (i+j) */
    const std::string oddBg; /**< background color for the odd cells (i+j) */

public:
    static const char emptyCell; /**< char for an empty cell */
    static const uint32_t maxBoardSize; /**< max board size */

    /**
     * @param _height board height
     * @param _width board width
     * @param indexColor color for the indexes
     * @param piecesColor color for the pieces
     * @param borderColor color for the board
     * @param evenBg background color for the even cells
     * @param oddBg background color for the odd cells
     */
    Board(uint32_t _height, uint32_t _width, std::string indexColor = "", std::string piecesColor = "",
     std::string borderColor = "", std::string evenBg = "", std::string oddBg = "");

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
    char getSymbol(uint32_t line, uint32_t column) const;

    /**
     * Place symbol in the board, falling on the column or in the given coordinates
     * @param move vector with coordinates to place the symbol dim: 1-2
     * @param symbol symbol to be placed
     */
    void placeSymbol(const std::vector<uint32_t>& move, char symbol);
};

#endif //BOARD_HPP
