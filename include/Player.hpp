//
// Created by pedro-pires on 7/3/24.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <list>
#include <string>
#include <unordered_map>

enum CreationStatus {
    CREATED,
    INCORRECT_DATA,
    DUPLICATED_PLAYER
};

enum DeletionStatus {
    DELETED,
    PLAYER_NOT_FOUND,
    DELETION_ERROR
};

/**
 * Class that represents the player, it is also responsible for allowing the interaction with the database
 */
class Player {
    std::string nick;
    std::string name;

    uint reversiWins;
    uint reversiLosses;

    uint lig4Wins;
    uint lig4Losses;

    char symbol;

public:
    /**
     * Create a new player instance
     *
     * @param _nick Player's nickname
     * @param _name Player's name
     * @param _reversiWins Player's wins in reversi
     * @param _reversiLosses Player's losses in reversi
     * @param _lig4Wins Player's wins in lig4
     * @param _lig4Losses Player's losses in lig4
     */
    Player(std::string  _nick, std::string  _name, uint _reversiWins = 0, uint _reversiLosses = 0,
     uint _lig4Wins = 0, uint _lig4Losses = 0);

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
     * Get the player's wins of a game
     *
     * @param game letter that represents the game
     *
     * @return The player's wins stats
     */
    uint getWins(char game) const;

    /**
     * Get the player's losses of a game
     *
     * @param game letter that represents the game
     *
     * @return The player's losses stats
     */
    uint getLosses(char game) const;

    /**
     * Add a win to the player
     *
     * @param game The game to add the win
     */
    void addWin(char game);

    /**
     * Add a loss to the player
     *
     * @param game The game to add the loss
     */
    void addLoss(char game);

    /**
     * Set the player's symbol
     *
     * @param symbol The symbol to be set
     */
    void setSymbol(char symbol);

    /**
     * Get the player's symbol
     *
     * @return The player's symbol
     */
    char getSymbol() const;


    /**
     * Create a new player in the database
     *
     * @param nick The player's nickname
     * @param name The player's name
     *
     * @return CreationStatus enum
     */
    static CreationStatus createPlayer(const std::string& nick, const std::string& name);

    /**
     * Load a player from the database
     *
     * @param nick The player's nickname
     *
     * @return The player loaded
     */
    static Player* loadPlayer(const std::string& nick);

    /**
     * Update a player in the database
     *
     * @param nick The player's nickname
     * @param game The game stat to be updated
     * @param toAddWin If a win should be added
     * @param toAddLoss If a loss should be added
     * @param name (optional) The player's name to be changed
     */
    static int updatePlayer(const std::string& nick, char game, bool toAddWin, bool toAddLoss, const std::string& name = "");

    /**
     * Delete a player from the database
     *
     * @param nick The player's nickname
     *
     * @return DeletionStatus enum
     */
    static DeletionStatus deletePlayer(const std::string& nick);

    /**
     * Load all players from the database
     *
     * @return A list with all players
     */
    static std::list<Player> getAllPlayers();
};

#endif //PLAYER_HPP
