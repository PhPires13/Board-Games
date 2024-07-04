//
// Created by pedro-pires on 7/3/24.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <list>
#include <string>

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

/*
 * Class that represents the player, it is also responsible for allowing the interaction with the database
 */
class Player {
    std::string nick;
    std::string name;

    // TODO: count statistics for each game
    uint wins;
    uint losses;

    char symbol;

public:
    /*
     * Create a new player instance
     *
     * @param _nick: Player's nickname
     * @param _name: Player's name
     * @param _wins: Player's wins
     * @param _losses: Player's losses
     */
    Player(const std::string& _nick, const std::string& _name, uint _wins = 0, uint _losses = 0);

    /*
     * Get the player's nickname
     *
     * @return: The player's nickname
     */
    std::string getNick() const;

    /*
     * Get the player's name
     *
     * @return: The player's name
     */
    std::string getName() const;

    /*
     * Get the player's wins
     *
     * @return: The player's wins
     */
    uint getWins() const;

    /*
     * Get the player's losses
     *
     * @return: The player's losses
     */
    uint getLosses() const;

    /*
     * Add a win to the player
     */
    void addWin();

    /*
     * Add a loss to the player
     */
    void addLoss();

    /*
     * Set the player's symbol
     *
     * @param symbol: The symbol to be set
     */
    void setSymbol(char symbol);

    /*
     * Get the player's symbol
     *
     * @return: The player's symbol
     */
    char getSymbol() const;


    /*
     * Create a new player in the database
     *
     * @param _nick: The player's nickname
     * @param _name: The player's name
     *
     * @return: CreationStatus enum
     */
    static CreationStatus createPlayer(const std::string& nick, const std::string& name);

    /*
     * Load a player from the database
     *
     * @param nick: The player's nickname
     *
     * @return: The player loaded
     */
    static Player loadPlayer(const std::string& nick);

    /*
     * Update a player in the database
     *
     * @param nick: The player's nickname
     * @param toAddWin: If a win should be added
     * @param toAddLoss: If a loss should be added
     * @param (optional) name: The player's name to be changed
     */
    static int updatePlayer(const std::string& nick, bool toAddWin, bool toAddLoss, const std::string& name = "");

    /*
     * Delete a player from the database
     *
     * @param nick: The player's nickname
     *
     * @return: DeletionStatus enum
     */
    static DeletionStatus deletePlayer(const std::string& nick);

    /*
     * Load all players from the database
     *
     * @return: A list with all players
     */
    static std::list<Player> getAllPlayers();
};

#endif //PLAYER_HPP
