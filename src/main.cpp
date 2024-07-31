//
// Created by pires on 6/28/2024.
//

#include "BoardGame.hpp"
#include "Player.hpp"
#include "TicTacToe.hpp"

int main(int argc, char* argv[]) {
    Player player1 = Player("Ped", "Pedro");
    Player player2 = Player("Joa", "João");

    TicTacToe boardGame = TicTacToe(player1, player2);

    boardGame.playGame();

    return 0;
}
