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
    static std::string filePath;

    static constexpr int firstValidSymbol = 33;
    static constexpr char lastValidSymbol = 126;


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
     * @param _reversiWins Player's wins in reversi
     * @param _reversiLosses Player's losses in reversi
     * @param _lig4Wins Player's wins in lig4
     * @param _lig4Losses Player's losses in lig4
     * @param _tttWins Player's wins in ttt
     * @param _tttLosses Player's losses in ttt
     */
    Player(const std::string& _nick, std::string _name, char symbol = 0, uint32_t _reversiWins = 0, uint32_t _reversiLosses = 0,
     uint32_t _lig4Wins = 0, uint32_t _lig4Losses = 0, uint32_t _tttWins = 0, uint32_t _tttLosses = 0);

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
     * Set a default file path to persist players
     *
     * @param filePath to be set
     */
    static void setFilePath(const std::string& filePath);

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
};

#endif //PLAYER_HPP
