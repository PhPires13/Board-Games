//
// Created by Paulo Henrique Pires  on 31/07/24.
//

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

class invalid_command final: public std::exception {
public:
    const char* what() const noexcept override ;
};

class game_not_found final: public std::exception {
public:
    const char* what() const noexcept override;
};

class incorrect_data final: public std::exception {
public:
    const char* what() const noexcept override;
};

class player_not_found final: public std::exception {
public:
    const char* what() const noexcept override;
};

class file_error final: public std::exception {
public:
    const char* what() const noexcept override;
};

class duplicated_player final: public std::exception {
public:
    const char* what() const noexcept override;
};

class incorrect_format final: public std::exception {
public:
    const char* what() const noexcept override;
};

class invalid_move final: public std::exception {
public:
    const char* what() const noexcept override;
};

class size_exceeded final: public std::exception {
public:
    const char* what() const noexcept override;
};

#endif //EXCEPTIONS_HPP
