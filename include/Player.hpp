//
// Created by pedro-pires on 7/3/24.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <list>
#include <string>

class Player {
    std::string nick;
    std::string name;

    int wins;
    int losses;

    char symbol;

public:
    Player(std::string _nick, std::string _name, int _wins = 0, int _losses = 0);

    std::string getNick() const;

    std::string getName() const;

    int getWins() const;

    int getLosses() const;

    void addWin();

    void addLoss();

    void setSymbol(char symbol);

    char getSymbol() const;


    static bool savePlayer(const Player& player);

    static Player loadPlayer(std::string nick);

    static bool deletePlayer(std::string nick);

    static std::list<Player> loadAllPlayers();
};

#endif //PLAYER_HPP
