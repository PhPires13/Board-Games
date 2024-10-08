#include "doctest.h"
#include "exceptions.hpp"

#include <sstream>
#include <iostream>

#define private public
#define protected public

#include "Reversi.hpp"
#include "Player.hpp"

#undef private
#undef protected

TEST_SUITE("Reversi") {

    TEST_CASE("Constructor") {
        const Player player1("PED", "PEDRO");
        const Player player2("CARL", "CARLOS");

        // Constructor with default board size
        CHECK_NOTHROW(Reversi(player1, player2));

        // Constructor with valid board size (even number)
        CHECK_NOTHROW(Reversi(player1, player2, Reversi::minimumBoardSize));

        // Constructor with invalid board size (odd number), will sue the default size
        CHECK_NOTHROW(Reversi(player1, player2, Reversi::minimumBoardSize-1));

        // Constructor with minimum valid board size
        CHECK_NOTHROW(Reversi(player1, player2, Reversi::minimumBoardSize));
    }

    TEST_CASE("Is a valid size") {
        const Player player1("PED", "PEDRO");
        const Player player2("CARL", "CARLOS");
        const Reversi game(player1, player2);

        CHECK(game.isAValidHeight(Reversi::minimumBoardSize - 1) == false);
        CHECK(game.isAValidHeight(Reversi::minimumBoardSize) == true);
        CHECK(game.isAValidHeight(Reversi::minimumBoardSize + 2) == true);
        CHECK(game.isAValidWidth(Reversi::minimumBoardSize - 1) == false);
        CHECK(game.isAValidWidth(Reversi::minimumBoardSize) == true);
        CHECK(game.isAValidWidth(Reversi::minimumBoardSize + 2) == true);
    }

    TEST_CASE("Validate Move") {
        const Player player1("PED", "PEDRO");
        const Player player2("CARL", "CARLOS");

        Reversi reversiGame(player1, player2, Reversi::minimumBoardSize); // Tabuleiro 4x4

        // Movimento inválido, lugar não cumpre as regras
        CHECK_THROWS_AS(reversiGame.validateMove({0, 0}), invalid_move);

        // Movimentos válidos
        CHECK_NOTHROW(reversiGame.validateMove({3, 2}));

        // Tamanho inválido
        CHECK_THROWS_AS(reversiGame.validateMove({}), incorrect_format);
        CHECK_THROWS_AS(reversiGame.validateMove({1}), incorrect_format);
        CHECK_THROWS_AS(reversiGame.validateMove({1, 2, 3}), incorrect_format);

        // Fora dos limites
        CHECK_THROWS_AS(reversiGame.validateMove({Reversi::minimumBoardSize, 0}), invalid_move);  // 4x4 board
        CHECK_THROWS_AS(reversiGame.validateMove({0, Reversi::minimumBoardSize}), invalid_move);  // 4x4 board
        CHECK_THROWS_AS(reversiGame.validateMove({8, Reversi::minimumBoardSize}), invalid_move);  // 4x4 board

        // Lugar não está vazio
        reversiGame.makeMove({2, 3}, player1.getSymbol());
        CHECK_THROWS_AS(reversiGame.validateMove({2, 3}), invalid_move);
    }

    TEST_CASE("Make Move and Flip Pieces") {
        const Player player1("PED", "PEDRO", 'X');
        const Player player2("CARL", "CARLOS", 'O');

        Reversi reversiGame(player1, player2, Reversi::minimumBoardSize); // Tabuleiro 4x4

        // Executa o movimento e verifica se as peças são viradas corretamente
        reversiGame.makeMove({2, 3}, player1.getSymbol());
        CHECK(reversiGame.board.getSymbol(2, 3) == 'X');
        CHECK(reversiGame.board.getSymbol(2, 2) == 'X');
    }

    TEST_CASE("Get Game State") {
        const Player player1("PED", "PEDRO", 'X');
        const Player player2("CARL", "CARLOS", 'O');

        Reversi reversiGame(player1, player2, Reversi::minimumBoardSize); // Tabuleiro 4x4

        // Jogo ainda não terminou
        CHECK(reversiGame.getGameState({3, 2}) == GameState::NOT_OVER);

        // Exemplo de cenário onde o jogador 1 vence
        reversiGame.makeMove({3, 1}, player1.getSymbol());
        reversiGame.makeMove({1, 0}, player2.getSymbol());
        reversiGame.makeMove({0, 1}, player1.getSymbol());
        reversiGame.makeMove({3, 2}, player2.getSymbol());
        reversiGame.makeMove({3, 3}, player1.getSymbol());
        reversiGame.makeMove({2, 3}, player2.getSymbol());
        reversiGame.makeMove({1, 3}, player1.getSymbol());
        reversiGame.makeMove({0, 3}, player2.getSymbol());

        CHECK(reversiGame.getGameState({0, 2}) == GameState::PLAYER1_WINS);

    }

    TEST_CASE("Play Game") {
        std::streambuf* cinbuf = std::cin.rdbuf();  // Store the original buffer

        const Player player1("PED", "PEDRO", 'X');
        const Player player2("CARL", "CARLOS", 'O');

        const std::istringstream input1("2 0\n3 2\n1 3\n0 2\n2 3\n1 0\n0 1\n3 0\n0 3\n3 3\n3 1\n0 0\n"); // Entrada simulada
        std::cin.rdbuf(input1.rdbuf());
        Reversi reversiGame(player1, player2, Reversi::minimumBoardSize); // Tabuleiro 4x4
        GameState gameState;
        CHECK_NOTHROW(gameState = reversiGame.playGame());
        CHECK(gameState == GameState::TIE);

        // Restore std::cin to its original state
        std::cin.rdbuf(cinbuf);
    }

    TEST_CASE("Game Tie") {
        const Player player1("PED", "PEDRO", 'X');
        const Player player2("CARL", "CARLOS", 'O');

        Reversi reversiGame(player1, player2, Reversi::minimumBoardSize); // Tabuleiro 4x4

        reversiGame.makeMove({2, 0}, player1.getSymbol());
        reversiGame.makeMove({3, 2}, player2.getSymbol());
        reversiGame.makeMove({1, 3}, player1.getSymbol());
        reversiGame.makeMove({0, 2}, player2.getSymbol());
        reversiGame.makeMove({2, 3}, player1.getSymbol());
        reversiGame.makeMove({1, 0}, player2.getSymbol());
        reversiGame.makeMove({0, 1}, player1.getSymbol());
        reversiGame.makeMove({3, 0}, player2.getSymbol());
        reversiGame.makeMove({0, 3}, player1.getSymbol());
        reversiGame.makeMove({3, 3}, player2.getSymbol());
        reversiGame.makeMove({3, 1}, player1.getSymbol());
        reversiGame.makeMove({0, 0}, player2.getSymbol());
        CHECK(reversiGame.getGameState({0, 0}) == GameState::TIE);
    }

    TEST_CASE("Player 2 Wins") {
        const Player player1("PED", "PEDRO", 'X');
        const Player player2("CARL", "CARLOS", 'O');

        Reversi reversiGame(player1, player2, Reversi::minimumBoardSize); // Tabuleiro 4x4

        reversiGame.makeMove({1, 3}, player1.getSymbol());
        reversiGame.makeMove({0, 3}, player2.getSymbol());
        reversiGame.makeMove({2, 0}, player1.getSymbol());
        reversiGame.makeMove({3, 0}, player2.getSymbol());
        reversiGame.makeMove({0, 2}, player1.getSymbol());
        reversiGame.makeMove({0, 1}, player2.getSymbol());
        reversiGame.makeMove({1, 0}, player1.getSymbol());
        reversiGame.makeMove({0, 0}, player2.getSymbol());
        reversiGame.makeMove({3, 1}, player1.getSymbol());
        reversiGame.makeMove({3, 3}, player2.getSymbol());
        reversiGame.makeMove({2, 3}, player1.getSymbol());
        reversiGame.makeMove({3, 2}, player2.getSymbol());
        CHECK(reversiGame.getGameState({3, 2}) == GameState::PLAYER2_WINS);
    }

    TEST_CASE("Player 1 Wins With Empty Spaces Left") {
        const Player player1("PED", "PEDRO", 'X');
        const Player player2("CARL", "CARLOS", 'O');

        Reversi reversiGame(player1, player2, Reversi::minimumBoardSize); // Tabuleiro 4x4

        reversiGame.makeMove({1, 3}, player1.getSymbol());
        reversiGame.makeMove({2, 3}, player2.getSymbol());
        reversiGame.makeMove({3, 3}, player1.getSymbol());
        reversiGame.makeMove({0, 1}, player2.getSymbol());
        reversiGame.makeMove({3, 0}, player1.getSymbol());
        reversiGame.makeMove({2, 0}, player2.getSymbol());
        reversiGame.makeMove({0, 0}, player1.getSymbol());
        reversiGame.makeMove({0, 2}, player2.getSymbol());
        reversiGame.makeMove({0, 3}, player1.getSymbol());
        reversiGame.makeMove({3, 1}, player2.getSymbol());
        reversiGame.makeMove({1, 0}, player1.getSymbol());
        CHECK(reversiGame.getGameState({0, 3}) == GameState::PLAYER1_WINS);
    }
}
