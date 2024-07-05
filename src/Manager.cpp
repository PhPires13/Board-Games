//
// Created by pedro-pires on 7/4/24.
//

#include "Manager.hpp"

#include <iostream>
#include <sstream>

#include "Player.hpp"

Manager::Manager(const std::string& _databasePath): databasePath(_databasePath) {

}

void Manager::printMenu() {
     std::cout << "CJ: Cadastrar Jogador (<Apelido> <Nome>)" << std::endl;
     std::cout << "RJ: Remover Jogador (<Apelido>)" << std::endl;
     std::cout << "LJ: Listar Jogadores (<Ordem: [A|N]>)" << std::endl;
     std::cout << "EP: Executar Partida (<Jogo: (R|L)> <Apelido Jogador 1> <Apelido Jogador 2>)" << std::endl;
     std::cout << "FS: Finalizar Sistema" << std::endl;
     std::cout << std::endl;
     std::cout << "> " << std::endl;
}

void Manager::createPlayer(const std::string& arguments) const {
    std::stringstream ss(arguments);
    std::string nick, name;
    ss >> nick;
    std::getline(ss, name);

    CreationStatus creationStatus = Player::createPlayer(nick, name);

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

void Manager::executeMatch(const std::string &arguments) const {
    std::stringstream ss(arguments);
    char game;
    std::string nick1, nick2;
    ss >> game >> nick1 >> nick2;

    // TODO: implement calling each game
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

        // TODO: pass databasePath argument
        if (command == "CJ")
            createPlayer(arguments);
        else if (command == "RJ")
            deletePlayer(arguments);
        else if (command == "LJ")
            listPlayers(arguments);
        else if (command == "EP")
            executeMatch(arguments);
        else if (command == "FS")
            break;
        else
            std::cout << "ERRO: comando inválido" << std::endl;
    }
}