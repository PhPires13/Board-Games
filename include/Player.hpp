//
// Created by pedro-pires on 7/3/24.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <list>
#include <string>
#include <cstdint>

/**
 * Class that represents the player, it is also responsible for allowing the interaction with the database
 */
class Player {
    static const std::string filePath;

    static const uint32_t firstValidSymbol;
    static const char lastValidSymbol;


    std::string nick;
    std::string name;

    char symbol;

    uint32_t reversiWins;
    uint32_t reversiLosses;

    uint32_t lig4Wins;
    uint32_t lig4Losses;

    uint32_t tttWins;
    uint32_t tttLosses;

public:
    /**
     * Create a new player instance
     *
     * @param _nick Player's nickname
     * @param _name Player's name
     * @param symbol Player's symbol
     */
    Player(std::string _nick, std::string _name, char symbol = 0);

    /**
     * Get the player's nickname
     *
     * @return The player's nickname
     */
    std::string getNick() const;

    /**
     * Get the player's name
     *
     * @return The player's name
     */
    std::string getName() const;

    /**
     * Get the player's symbol
     *
     * @return The player's symbol
     */
    char getSymbol() const;

    /**
     * Set the player's symbol, it is just during execution time, it does not change the database
     *
     * @param symbol The symbol to be set
     */
    void setSymbol(char symbol);

    /**
     * Get the player's wins of a game
     *
     * @param game letter that represents the game
     *
     * @return The player's wins stats
     */
    uint32_t getWins(char game) const;

    /**
     * Get the player's losses of a game
     *
     * @param game letter that represents the game
     *
     * @return The player's losses stats
     */
    uint32_t getLosses(char game) const;

    /**
     * Add a win to the player
     *
     * @param game The game to add the win
     * @param toAddWin If a win should be added
     * @param toAddLoss If a loss should be added
     */
    void addStats(char game, bool toAddWin, bool toAddLoss);

    /**
     * Create a new player in the database
     *
     * @param nick The player's nickname
     * @param name The player's name
     * @param symbol The player's symbol
     *
     * @throws duplicated_player
     * @throws file_error
     */
    static void createPlayer(const std::string& nick, const std::string& name, char symbol = 0);

    /**
     * Load a player from the database
     *
     * @param nick The player's nickname
     *
     * @return The player loaded
     *
     * @throws player_not_found
     * @throws file_error
     */
    static Player loadPlayer(const std::string& nick);

    /**
     * Update a player stats in the database
     *
     * @param nick The player's nickname
     * @param game The game stat to be updated
     * @param toAddWin If a win should be added
     * @param toAddLoss If a loss should be added
     *
     * @throws player_not_found
     * @throws file_error
     */
    static void updatePlayerStats(const std::string& nick, char game, bool toAddWin, bool toAddLoss);

    /**
     * Update a player info in the database
     *
     * @param name (optional) The player's name to be changed
     * @param symbol (optional) The player's symbol to be changed
     *
     * @throws file_error
     */
    static void updatePlayerInfo(const std::string& nick, const std::string& name = "", char symbol = 0);

    /**
     * Delete a player from the database
     *
     * @param nick The player's nickname
     *
     * @throws player_not_found
     * @throws file_error
     */
    static void deletePlayer(const std::string& nick);

    /**
     * Load all players from the database
     *
     * @return A list with all players
     *
     * @throws file_error
     */
    static std::list<Player> getAllPlayers();

    /**
     * Compare two players by nick
     *
     * @return true if the first player is less than the second one
     */
    static bool compareByNick(const Player& player1, const Player& player2);

    /**
     * Compare two players by name
     *
     * @return true if the first player is less than the second one
     */
    static bool compareByName(const Player& player1, const Player& player2);

    /**
     * Guarantee that the databse file exists
     *
     * @throws file_error
     */
    static void syncDatabase();
};

#endif //PLAYER_HPP
