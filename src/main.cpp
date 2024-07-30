//
// Created by pires on 6/28/2024.
//

#include "BoardGame.hpp"
#include "Player.hpp"

int main(int argc, char* argv[]) {
    Player player1 = Player("Ped", "Pedro");
    Player player2 = Player("Joa", "João");

    BoardGame boardGame = BoardGame(player1, player2);

    boardGame.playGame();

    return 0;
}
