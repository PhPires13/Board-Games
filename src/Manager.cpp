//
// Created by pedro-pires on 7/4/24.
//

#include "Manager.hpp"

#include <iostream>
#include <sstream>
#include <cstdint>

#include "BoardGame.hpp"
#include "Player.hpp"

Manager::Manager(const std::string& _databasePath): databasePath(_databasePath) {

}

void Manager::printMenu() {
    std::cout << "Obs.:" << std::endl;
    std::cout << "?: parametros opcionais" << std::endl;
    std::cout << "R: reversi, tabuleiro: quadrado, min 6x6 \t";
    std::cout << "L: lig4, tabuleiro: min 4x4";
    std::cout << std::endl << std::endl;

    std::cout << "------------------------------------ MENU ------------------------------------"  << std::endl;
    std::cout << "CJ: Cadastrar Jogador (<Apelido> <Nome> <? Simbolo>)" << std::endl;
    std::cout << "RJ: Remover Jogador (<Apelido>)" << std::endl;
    std::cout << "LJ: Listar Jogadores (<Ordem: [A|N]>)" << std::endl;
    std::cout << "EP: Executar Partida (<Jogo: (R|L)> <Apelido Jogador 1> <Apelido Jogador 2> <? Altura Tabuleiro> <? Largura Tabuleiro>)" << std::endl;
    std::cout << "FS: Finalizar Sistema" << std::endl;
    std::cout << std::endl;
    std::cout << "> " << std::endl;
}

void Manager::createPlayer(std::string& arguments) const {
    std::string nick, name;
    char symbol = 0;

    // Check if the arguments contains a symbol at the end
    const uint32_t lastSpace = arguments.find_last_of(' ');
    if ((lastSpace != std::string::npos) && (lastSpace + 1 == arguments.size() - 1)) {
        symbol = arguments[lastSpace + 1];
        arguments = arguments.substr(0, lastSpace); // Remove the symbol from the arguments
    }

    // Read the rest of the arguments
    std::stringstream ss(arguments);
    ss >> nick;
    std::getline(ss, name);

    // Create the player
    const CreationStatus creationStatus = Player::createPlayer(nick, name, symbol);

    // Check the creation status
    if (creationStatus == CreationStatus::CREATED)
        std::cout << "Jogador " << nick << " cadastrado com sucesso" << std::endl;
    else if (creationStatus == CreationStatus::INCORRECT_DATA)
        std::cout << "ERRO: dados incorretos" << std::endl;
    else if (creationStatus == CreationStatus::DUPLICATED_PLAYER)
        std::cout << "ERRO: jogador repetido" << std::endl;
}

void Manager::deletePlayer(const std::string& arguments) const {
    std::stringstream ss(arguments);
    std::string nick;
    ss >> nick;

    DeletionStatus deletionStatus = Player::deletePlayer(nick);

    if (deletionStatus == DeletionStatus::DELETED)
        std::cout << "Jogador " << nick << " removido com sucesso" << std::endl;
    else if (deletionStatus == DeletionStatus::PLAYER_NOT_FOUND)
        std::cout << "ERRO: jogador inexistente" << std::endl;
    else if (deletionStatus == DeletionStatus::DELETION_ERROR)
        std::cout << "ERRO: erro ao remover jogador" << std::endl;
}

void Manager::listPlayers(const std::string &arguments) const {
    std::stringstream ss(arguments);
    char order;
    ss >> order;

    // TODO: implement order

    std::list<Player> players = Player::getAllPlayers();

    // TOOD: Print players with stats
}

BoardGame* Manager::createMatch(char game, const Player& player1, const Player& player2, const std::string& extraArguments) const {
    if (game == 'R') {
        // TODO: adicionar criacao do reversi
    } else if (game == 'L') {
        // TODO: Adicionar criacao do lig4
    }
}


void Manager::playMatch(const std::string &arguments) const {
    std::stringstream ss(arguments);
    char game;
    std::string nick1, nick2;
    try {
        ss >> game >> nick1 >> nick2;
    } catch (std::exception& e) {
        std::cout << "ERRO: dados incorretos" << std::endl;
        return;
    }

    // Recover players
    Player* player1 = Player::loadPlayer(nick1);
    Player* player2 = Player::loadPlayer(nick2);
    if (player1 == nullptr || player2 == nullptr) {
        std::cout << "ERRO: jogador inexistente" << std::endl;
        return;
    }

    // Create a game instance of the specified type
    std::string extraArguments;
    std::getline(ss, extraArguments);
    BoardGame* boardGame = createMatch(game, *player1, *player2, extraArguments);

    // Play the match
    GameState gameState = boardGame->playGame();

    // Update players stats
    bool player1Won = gameState == GameState::PLAYER1_WINS;
    bool player2Won = gameState == GameState::PLAYER2_WINS;

    Player::updatePlayer(player1->getNick(), game, player1Won, player2Won);
    Player::updatePlayer(player2->getNick(), game, player2Won, player1Won);
}

void Manager::menu() const {
    while (true) {
        Manager::printMenu();

        // Read command line
        std::string commandLine;
        std::getline(std::cin, commandLine);
        std::stringstream ss(commandLine);

        std::string command;
        std::string arguments;
        ss >> command;
        std::getline(ss, arguments);

        // Remove non-alphanumeric characters from the end of the arguments
        arguments.erase(std::remove_if(arguments.begin(), arguments.end(), [](char c) {
            return !std::isalnum(c);
        }), arguments.end());

        // TODO: pass databasePath argument
        if (command == "CJ")
            createPlayer(arguments);
        else if (command == "RJ")
            deletePlayer(arguments);
        else if (command == "LJ")
            listPlayers(arguments);
        else if (command == "EP")
            playMatch(arguments);
        else if (command == "FS")
            break;
        else
            std::cout << "ERRO: comando inválido" << std::endl;
    }
}
