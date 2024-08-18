//
// Created by Paulo Henrique Pires  on 31/07/24.
//

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

/**
 * Exception thrown when a command is invalid
 */
class invalid_command final: public std::exception {
public:
    const char* what() const noexcept override ;
};

/**
 * Exception thrown when there is no matching game
 */
class game_not_found final: public std::exception {
public:
    const char* what() const noexcept override;
};

/**
 * Exception thrown when the data is incorrect or invalid
 */
class incorrect_data final: public std::exception {
public:
    const char* what() const noexcept override;
};

/**
 * Exception thrown when a player is not found for some action
 */
class player_not_found final: public std::exception {
public:
    const char* what() const noexcept override;
};

/**
 * Exception thrown when there is some error with the file
 */
class file_error final: public std::exception {
public:
    const char* what() const noexcept override;
};

/**
 * Exception thrown when a player is duplicated, both creating and playing
 */
class duplicated_player final: public std::exception {
public:
    const char* what() const noexcept override;
};

/**
 * Exception thrown when the format of the data is incorrect
 */
class incorrect_format final: public std::exception {
public:
    const char* what() const noexcept override;
};

/**
 * Exception thrown when the move is invalid
 */
class invalid_move final: public std::exception {
public:
    const char* what() const noexcept override;
};

/**
 * Exception thrown when the size of the command is exceeded
 */
class size_exceeded final: public std::exception {
public:
    const char* what() const noexcept override;
};

#endif //EXCEPTIONS_HPP
