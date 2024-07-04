//
// Created by pedro-pires on 7/4/24.
//

#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <string>

class Manager {
    std::string databasePath;
    // TODO: dict of games type BoardGame

public:
    Manager(const std::string& _databasePath);

    static void printMenu();

    void createPlayer(const std::string& arguments) const;

    void deletePlayer(const std::string& arguments) const;

    void listPlayers(const std::string& arguments) const;

    void executeMatch(const std::string& arguments) const;

    void menu() const;
};

#endif //MANAGER_HPP
