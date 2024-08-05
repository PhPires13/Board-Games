//
// Created by pedro-pires on 7/4/24.
//

#include "Manager.hpp"

#include <iostream>
#include <sstream>
#include <cstdint>

#include "BoardGame.hpp"
#include "exceptions.hpp"
#include "Player.hpp"
#include "Reversi.hpp"
#include "TicTacToe.hpp"
#include "Utils.hpp"

const uint32_t Manager::maxCommandSize = 100;

void Manager::printMenu() {
    std::cout << "Obs.:" << std::endl;
    std::cout << "?: parametros opcionais" << std::endl;
    std::cout << "R: reversi, tabuleiro: quadrado, par, min 4x4 \t";
    std::cout << "L: liga4, tabuleiro: min 4x4\t";
    std::cout << "V: velha, tabuleiro: 3x3";
    std::cout << std::endl << std::endl;

    std::cout << "------------------------------------ MENU ------------------------------------"  << std::endl;
    std::cout << "CJ: Cadastrar Jogador (<Apelido> <Nome> <? Simbolo>)" << std::endl;
    std::cout << "RJ: Remover Jogador (<Apelido>)" << std::endl;
    std::cout << "LJ: Listar Jogadores (<Ordem: [A|N]>)" << std::endl;
    std::cout << "EP: Executar Partida (<Jogo: (R|L|V)> <Apelido Jogador 1> <Apelido Jogador 2> <? Altura Tabuleiro> <? Largura Tabuleiro>)" << std::endl;
    std::cout << "FS: Finalizar Sistema" << std::endl;
    std::cout << std::endl;
    std::cout << "> ";
}

void Manager::createPlayer(const std::string& arguments) {
    std::string nick, name;
    char symbol = 0;

    // Split the arguments into substrings by space
    std::istringstream iss(arguments);
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};

    try {
        // Get the symbol if it exists
        if (tokens.back().size() == 1) {
            symbol = tokens.back()[0];
            tokens.pop_back();
        }

        for (uint32_t i =0; i < tokens.size(); i++) {
            if (i == 0) nick = tokens[i];
            else {
                if (i != 1) name += " ";
                name += tokens[i];
            }
        }
    } catch (std::exception& e) {
        throw incorrect_format();
    }

    if (nick.empty() || name.empty()) throw incorrect_format();

    // Create the player
    Player::createPlayer(nick, name, symbol);

    std::cout << "Jogador " << nick << " cadastrado com sucesso" << std::endl;
}

void Manager::deletePlayer(const std::string& arguments) {
    std::stringstream ss(arguments);
    std::string nick;
    ss >> nick;

    // Delete the player
    Player::deletePlayer(nick);

    std::cout << "Jogador " << nick << " removido com sucesso" << std::endl;
}

void Manager::listPlayers(const std::string &arguments) {
    std::stringstream ss(arguments);
    char order;
    ss >> order;

    // TODO: implement order

    const std::list<Player> players = Player::getAllPlayers();

    for (const Player& player: players) {
        std::cout << player.getNick() << " " << player.getName() << " " << player.getSymbol() << std::endl;
        std::cout << "REVERSI - " << "V: " << player.getWins(Game::REVERSI) << " D: " << player.getLosses(Game::REVERSI) << std::endl;
        std::cout << "LIG4 - " << "V: " << player.getWins(Game::LIG4) << " D: " << player.getLosses(Game::LIG4) << std::endl;
        std::cout << "VELHA - " << "V: " << player.getWins(Game::TTT) << " D: " << player.getLosses(Game::TTT) << std::endl;
        std::cout << std::endl;
    }
}

BoardGame* Manager::createMatch(char game, const Player& player1, const Player& player2, const std::string& extraArguments) {
    BoardGame* boardGame = nullptr;

    // Get the custom board size if sent
    uint32_t boardHeight=0, boardWidth=0;
    if (!extraArguments.empty()) {
        std::stringstream ss(extraArguments);
        try {
            ss >> boardHeight >> boardWidth;
        } catch (std::exception& e) {
            throw incorrect_data();
        }
    }

    // Create the game instance
    if (game == Game::REVERSI) {
        boardGame = new Reversi(const_cast<Player&>(player1), const_cast<Player&>(player2), boardHeight);
    } else if (game == Game::LIG4) {
        // TODO: Adicionar criacao do lig4
    } else if (game == Game::TTT) {
        boardGame = new TicTacToe(const_cast<Player&>(player1), const_cast<Player&>(player2));
    } else {
        throw game_not_found();
    }

    return boardGame;
}

void Manager::playMatch(const std::string &arguments) {
    std::stringstream ss(arguments);
    char game;
    std::string nick1, nick2;
    try {
        ss >> game >> nick1 >> nick2;
    } catch (std::exception& e) {
        throw incorrect_data();
    }

    if (game == '\0' || nick1.empty() || nick2.empty()) throw incorrect_format();

    if (nick1 == nick2) throw duplicated_player();

    // Recover players
    Player player1 = Player::loadPlayer(nick1);
    Player player2 = Player::loadPlayer(nick2);

    // Create a game instance of the specified type
    std::string extraArguments;
    std::getline(ss, extraArguments);
    BoardGame* boardGame = createMatch(game, player1, player2, extraArguments);

    // Play the match
    const GameState gameState = boardGame->playGame();

    // Update players stats
    const bool player1Won = gameState == GameState::PLAYER1_WINS;
    const bool player2Won = gameState == GameState::PLAYER2_WINS;

    Player::updatePlayerStats(player1.getNick(), game, player1Won, player2Won);
    Player::updatePlayerStats(player2.getNick(), game, player2Won, player1Won);
}

void Manager::menu() {
    while (true) {
        try {
            Manager::printMenu();

            // Read command line
            std::string commandLine;
            std::getline(std::cin, commandLine);
            commandLine = Utils::cleanString(commandLine);
            if (commandLine.size() > Manager::maxCommandSize) throw size_exceeded();
            std::stringstream ss(commandLine);

            std::string command;
            std::string arguments;
            ss >> command;
            std::getline(ss, arguments);

            std::cout << std::endl;

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
                throw invalid_command();
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }

        std::cout << std::endl<< "Pressione: <ENTER>";
        const char pause = getchar();
        Utils::clearTerminal();
    }
}
