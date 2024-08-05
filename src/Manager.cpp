//
// Created by pedro-pires on 7/4/24.
//

#include "Manager.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <iterator>

#include "BoardGame.hpp"
#include "exceptions.hpp"
#include "Player.hpp"
#include "Reversi.hpp"
#include "TicTacToe.hpp"
#include "Utils.hpp"

const uint32_t Manager::maxCommandSize = 100;

void Manager::printMenu() {
    // Define color codes
    const std::string titleColor = "\033[1;34m"; // Bold blue
    const std::string optionColor = "\033[1;32m"; // Bold green
    const std::string descriptionColor = "\033[0;36m"; // Cyan
    const std::string paramColor = "\033[0;33m"; // Yellow
    const std::string optionalParamColor = "\033[0;35m"; // Magenta
    const std::string optionsColor = "\033[0;31m"; // Red
    const std::string exampleColor = "\033[1;31m"; // Bold red
    const std::string noteColor = "\033[1;33m"; // Bold yellow
    const std::string reset = "\033[0m"; // Reset color

    std::cout << titleColor << "Obs.:" << reset << std::endl;
    std::cout << noteColor << "?: parametros opcionais" << reset << std::endl;
    std::cout << exampleColor << "R: reversi, tabuleiro: quadrado, par, min 4x4\t" << reset;
    std::cout << exampleColor << "L: liga4, tabuleiro: min 4x4\t" << reset;
    std::cout << exampleColor << "V: velha, tabuleiro: 3x3" << reset;
    std::cout << std::endl << std::endl;

    std::cout << titleColor << "------------------------------------ MENU ------------------------------------" << reset << std::endl;
    std::cout << optionColor << "CJ: " << reset << descriptionColor << "Cadastrar Jogador (" << paramColor << "<Apelido> <Nome>" << optionalParamColor << " <? Simbolo>" << descriptionColor << ")" << reset << std::endl;
    std::cout << optionColor << "RJ: " << reset << descriptionColor << "Remover Jogador (" << paramColor << "<Apelido>" << descriptionColor << ")" << reset << std::endl;
    std::cout << optionColor << "LJ: " << reset << descriptionColor << "Listar Jogadores (" << optionalParamColor << "<? Ordem: " << optionsColor << "[A|N]" << optionalParamColor << ">" << descriptionColor << ")" << reset << std::endl;
    std::cout << optionColor << "EP: " << reset << descriptionColor << "Executar Partida (" << paramColor << "<Jogo: " << optionsColor << "(R|L|V)" << paramColor << "> <Apelido Jogador 1> <Apelido Jogador 2>" << optionalParamColor << " <? Altura Tabuleiro> <? Largura Tabuleiro>" << descriptionColor << ")" << reset << std::endl;
    std::cout << optionColor << "FS: " << reset << descriptionColor << "Finalizar Sistema" << reset << std::endl;
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
    // Define color codes
    const std::string nickColor = "\033[1;35m"; // Bold Magenta
    const std::string nameColor = "\033[0;33m"; //  Yellow
    const std::string symbolColor = "\033[1;34m"; // Bold blue
    const std::string gameColor = "\033[0;36m"; // Cyan
    const std::string winColor = "\033[0;32m"; // Green
    const std::string lossColor = "\033[0;31m"; // Red
    const std::string reset = "\033[0m"; // Reset color

    std::stringstream ss(arguments);
    char order;
    ss >> order;

    const std::list<Player> players = Player::getAllPlayers();
    std::vector<Player> playersVector(players.begin(), players.end());

    if (order == 'A') {
        std::sort(playersVector.begin(), playersVector.end(), Player::compareByNick);
    } else if (order == 'N') {
        std::sort(playersVector.begin(), playersVector.end(), Player::compareByName);
    }
    // Caso o parametro de ordenacao seja invalido, nao ordena intencionalmente

    for (const Player& player: playersVector) {
        std::cout << nickColor << player.getNick() << reset << " "
                  << nameColor << player.getName() << reset << " "
                  << symbolColor << player.getSymbol() << reset << std::endl;

        std::cout << gameColor << "REVERSI - " << reset
                  << winColor << "V: " << player.getWins(Game::REVERSI) << reset << " "
                  << lossColor << "D: " << player.getLosses(Game::REVERSI) << reset << std::endl;

        std::cout << gameColor << "LIG4 - " << reset
                  << winColor << "V: " << player.getWins(Game::LIG4) << reset << " "
                  << lossColor << "D: " << player.getLosses(Game::LIG4) << reset << std::endl;

        std::cout << gameColor << "VELHA - " << reset
                  << winColor << "V: " << player.getWins(Game::TTT) << reset << " "
                  << lossColor << "D: " << player.getLosses(Game::TTT) << reset << std::endl;

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
