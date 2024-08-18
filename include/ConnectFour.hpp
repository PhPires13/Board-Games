//
// Created by Carlos Eduardo on 05/08/2024.
//

#ifndef CONNECTFOUR_HPP
#define CONNECTFOUR_HPP


#include "BoardGame.hpp"
#include "Player.hpp"
#include <vector>

/**
 * Class that represents the Connect Four game
 */
class ConnectFour final: public BoardGame {
private:
    static const uint32_t minimumBoardSize; /**< Minimum size of the board (height == width) */
    static const uint32_t defaultBoardHeight; /**< Default height of the board */
    static const uint32_t defaultBoardWidth; /**< Default width of the board */

public:
    /**
     * Construtor da classe ConnectFour. Inicializa o jogo com dois jogadores e as dimensões do tabuleiro.
     *
     * @param _player1 Jogador 1
     * @param _player2 Jogador 2
     * @param boardHeight Altura do tabuleiro
     * @param boardWidth Largura do tabuleiro
     */
    ConnectFour(Player _player1, Player _player2, uint32_t boardHeight = ConnectFour::defaultBoardHeight, uint32_t boardWidth = ConnectFour::defaultBoardWidth);

private:

    /**
     * Verifica se a altura do tabuleiro é válida.
     *
     * @param boardHeight
     * @return true se é uma altura válida.
     */
    bool isAValidHeight(uint32_t boardHeight) const override;

    /**
     * Verifica se a largura do tabuleiro é válida.
     *
     * @param boardWidth
     * @return true se é uma largura válida.
     */
    bool isAValidWidth(uint32_t boardWidth) const override;

    /**
     *  Verifica se a coluna selecionada está cheia e executa o movimento da peça no tabuleiro.
     *
     * @param move Coordenadas da coluna.
     *
     * @throws incorrect_format if the move is empty or has more than 2 values
     * @throws invalid_move if the move is outside the board
     */
    void validateMove(const std::vector<uint32_t> &move)const override;

    /**
     * Analisa o status atual do jogo após cada jogada e verifica se há algum vencedor, de acordo com as regras do Lig4.
     *
     * @param move Coordenadas do movimento
     */
    GameState getGameState(const std::vector<uint32_t>& move) const override;

   /**
     * Verifica se há quatro peças seguidas de mesmo símbolo em uma determinda direção no tabuleiro após uma jogada
     *
     * @param move Coordenadas do movimento
     * @param symbol Símbolo do jogador que fez o movimento
     * @param dRow Sinalizador para analisar casas na direção vertical
     * @param dCol Sinalizadorpara analisar casas na direção horizontal
     */
    bool checkDirection(const std::vector<uint32_t> &move, char symbol, int dRow, int dCol) const;
};

#endif //CONNECTFOUR_HPP
