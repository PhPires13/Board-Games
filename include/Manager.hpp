//
// Created by pedro-pires on 7/4/24.
//

#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <string>

#include "BoardGame.hpp"
#include "Player.hpp"

/**
 * Enum to represent the possible games
 */
enum Game {
    REVERSI = 'R',
    CONNECT_FOUR = 'L',
    TTT = 'V'
};

/**
 * Class to manage the program, it is responsible for the interaction with the user
 */
class Manager {
private:
    static const uint32_t maxCommandSize; /**< max command size */

    /**
     * Print the menu of the program
     */
    static void printMenu();

    /**
     * Create a player in the database
     *
     * @param arguments Nick, name and symbol of the player
     *
     * @throws incorrect_format if was not able to parse the arguments
     * @throws duplicated_player if nick already exists
     * @throws file_error if was not able to write to the file
     */
    static void createPlayer(const std::string& arguments);

    /**
     * Delete a player from the database
     *
     * @param arguments Nick of the player
     *
     * @throws file_error if was not able to remove from the file
     */
    static void deletePlayer(const std::string& arguments);

    /**
     * List all players in the database
     *
     * @param arguments order of the list (Apelido, Nome)
     *
     * @throws file_error if was not able to read from the file
     */
    static void listPlayers(const std::string& arguments);

    /**
     * Create a match for the players of a given game
     *
     * @param game char representing the game
     * @param player1 player 1 of the match
     * @param player2 player 2 of the match
     * @param extraArguments custom dimensions for the board, when applicable
     *
     * @return a pointer to the created match
     *
     * @thwros incorrect_data if the data is invalid
     * @throws game_not_found if the game is not found
     */
    static BoardGame* createMatch(char game, const Player& player1, const Player& player2, const std::string& extraArguments);

    /**
     * Play a match between two players
     *
     * @param arguments game, nick1, nick2, custom dimensions
     *
     * @throws incorrect_format if was not able to parse the arguments
     * @throws duplicated_player if nick1 == nick2
     * @throws file_error if was not able to open the file
     * @throws player_not_found if nick1 or nick2 do not exist
     */
    static void playMatch(const std::string& arguments);

public:
    /**
     * Starts the program, keeps it running until the user decides to exit
     */
    static void menu();
};

#endif //MANAGER_HPP
