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
private:
    static const std::string filePath; /**< Path to the database file */

    static const uint32_t firstValidSymbol; /**< First valid symbol */
    static const uint32_t lastValidSymbol; /**< Last valid symbol */

    std::string nick; /**< Player's nickname */
    std::string name; /**< Player's name */

    char symbol; /**< Player's symbol */

    uint32_t reversiWins; /**< Wins in Reversi */
    uint32_t reversiLosses; /**< Losses in Reversi */

    uint32_t connectFourWins; /**< Wins in Connect Four */
    uint32_t connectFourLosses; /**< Losses in Connect Four */

    uint32_t tttWins; /**< Wins in Tic Tac Toe */
    uint32_t tttLosses; /**< Losses in Tic Tac Toe */

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
     * Salva o player serializado no arquivo
     *
     * @param outputFile arquivo para salvar
     */
    void serialize(std::ofstream& outputFile) const;

    /**
     * Recupera o player serializado do arquivo
     *
     * @param inputFile arquivo para ler o player serializado
     */
    void deserialize(std::ifstream& inputFile);

    /**
     * Create a new player in the database
     *
     * @param nick The player's nickname
     * @param name The player's name
     * @param symbol The player's symbol
     *
     * @throws duplicated_player if the player already exists
     * @throws file_error if was not able to write to the file
     */
    static void createPlayer(std::string nick, std::string name, char symbol = 0);

    /**
     * Load a player from the database
     *
     * @param nick The player's nickname
     *
     * @return The player loaded
     *
     * @throws player_not_found if the player was not found
     * @throws file_error if was not able to read from the file
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
     * @throws player_not_found if the player was not found
     * @throws file_error if was not able to write to the file
     */
    static void updatePlayerStats(const std::string& nick, char game, bool toAddWin, bool toAddLoss);

    /**
     * Update a player info in the database
     *
     * @param nick The player's nickname
     * @param toUpdateName If the name should be changed
     * @param toUpdateSymbol If the symbol should be changed
     * @param content The new content of the field, the symbol can be empty to remove it
     *
     * @throws player_not_found if the player was not found
     * @throws file_error if was not able to write to the file
     */
    static void updatePlayerInfo(const std::string& nick, bool toUpdateName, bool toUpdateSymbol, std::string content);

    /**
     * Update a player in the database
     *
     * @param nick The player's nickname
     * @param newPlayerData The new player data
     *
     * @throws player_not_found if the player was not found
     * @throws file_error if was not able to write to the file
     */
    static void updatePlayer(const std::string& nick, const Player& newPlayerData);

    /**
     * Delete a player from the database
     *
     * @param nick The player's nickname
     *
     * @throws player_not_found if the player was not found
     * @throws file_error if was not able to remove from the file
     */
    static void deletePlayer(const std::string& nick);

    /**
     * Load all players from the database
     *
     * @return A list with all players
     *
     * @throws file_error if was not able to read from the file
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
     * Guarantee that the database file exists
     *
     * @throws file_error if was not able to open the file
     */
    static void syncDatabase();
};

#endif //PLAYER_HPP
