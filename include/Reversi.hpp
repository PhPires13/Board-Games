#ifndef REVERSI_HPP
#define REVERSI_HPP

#include "BoardGame.hpp"
#include "Player.hpp"
#include "exceptions.hpp"
#include <vector>

class Reversi final : public BoardGame {
    static const uint32_t minimumBoardSize;
    static const uint32_t defaultBoardSize;

public:
    /**
     * Construtor da classe Reversi. Inicializa o jogo com dois jogadores e um tamanho de tabuleiro.
     *
     * @param _player1 Jogador 1
     * @param _player2 Jogador 2
     * @param boardSize Tamanho do tabuleiro (deve ser um número par, caso contrário, será usado o tamanho padrão)
     */
    Reversi(Player _player1, Player _player2, uint32_t boardSize = Reversi::defaultBoardSize);

private:
    /**
     * Verifica se a altura fornecida para o tabuleiro é válida.
     *
     * @param boardHeight Altura do tabuleiro
     * @return true se a altura é válida, false caso contrário
     */
    bool isAValidHeight(uint32_t boardHeight) override;

    /**
     * Verifica se a largura fornecida para o tabuleiro é válida.
     *
     * @param boardWidth Largura do tabuleiro
     * @return true se a largura é válida, false caso contrário
     */
    bool isAValidWidth(uint32_t boardWidth) override;

    /**
     * Valida o movimento dado, verificando se segue as regras do jogo Reversi.
     *
     * @param move Vetor com as coordenadas do movimento (linha e coluna)
     * @throw incorrect_format se o movimento não tiver exatamente duas coordenadas
     * @throw invalid_move se o movimento for inválido
     */
    void validateMove(const std::vector<int> &move) const override;

    /**
     * Executa o movimento no tabuleiro e vira as peças necessárias.
     *
     * @param move Coordenadas do movimento
     * @param symbol Símbolo do jogador que está realizando o movimento
     */
    void makeMove(const std::vector<int> &move, char symbol) override;

    GameState getGameState(const std::vector<int>& move) const override;

    /**
     * Vira as peças do oponente de acordo com as regras do Reversi, após um movimento válido.
     *
     * @param move Coordenadas do movimento
     * @param playerSymbol Símbolo do jogador que fez o movimento
     */
    void flipPieces(const std::vector<int>& move, char playerSymbol);

    /**
     * Verifica se uma direção específica a partir de uma posição é válida para virar peças.
     *
     * @param row Linha de origem do movimento
     * @param col Coluna de origem do movimento
     * @param directionRow Direção na linha (-1, 0, 1)
     * @param directionCol Direção na coluna (-1, 0, 1)
     * @param playerSymbol Símbolo do jogador atual
     * @return true se a direção é válida, false caso contrário
     */
    bool isValidDirection(int row, int col, int directionRow, int directionCol, char playerSymbol) const;

    /**
     * Vira as peças do oponente em uma direção específica.
     *
     * @param row Linha de origem do movimento
     * @param col Coluna de origem do movimento
     * @param directionRow Direção na linha (-1, 0, 1)
     * @param directionCol Direção na coluna (-1, 0, 1)
     * @param playerSymbol Símbolo do jogador atual
     */
    void flipInDirection(int row, int col, int directionRow, int directionCol, char playerSymbol);

    /**
     * Verifica se existe alguma direção válida para o movimento dado.
     *
     * @param row Linha de origem do movimento
     * @param col Coluna de origem do movimento
     * @param playerSymbol Símbolo do jogador atual
     * @return true se existe ao menos uma direção válida, false caso contrário
     */
    bool isAnyDirectionValid(int row, int col, char playerSymbol) const;

    /**
     * Verifica se as coordenadas estão dentro dos limites do tabuleiro.
     *
     * @param row Linha a ser verificada
     * @param col Coluna a ser verificada
     * @return true se as coordenadas estão dentro dos limites, false caso contrário
     */
    bool isWithinBounds(int row, int col) const;

    /**
     * Verifica se ainda existem movimentos possíveis para um determinado jogador.
     *
     * @param playerSymbol Símbolo do jogador
     * @return true se há movimentos válidos disponíveis, false caso contrário
     */
    bool hasValidMoves(char playerSymbol) const;
};

#endif
