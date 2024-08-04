//
// Created by Paulo Henrique Pires  on 31/07/24.
//

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

//TODO: Criar cpp

class invalid_command final: public std::exception {
public:
    const char* what() const noexcept override {
        return "ERRO: comando invalido";
    }
};

class game_not_found final: public std::exception {
public:
    const char* what() const noexcept override {
        return "ERRO: jogo inexistente";
    }
};

class incorrect_data final: public std::exception {
public:
    const char* what() const noexcept override {
        return "ERRO: dados incorretos";
    }
};

class player_not_found final: public std::exception {
public:
    const char* what() const noexcept override {
        return "ERRO: jogador inexistente";
    }
};

class file_error final: public std::exception {
public:
    const char* what() const noexcept override {
        return "ERRO: erro lidar com arquivo";
    }
};

class duplicated_player final: public std::exception {
public:
    const char* what() const noexcept override {
        return "ERRO: jogador repetido";
    }
};

class incorrect_format final: public std::exception {
public:
    const char* what() const noexcept override {
        return "ERRO: formato incorreto";
    }
};

class invalid_move final: public std::exception {
public:
    const char* what() const noexcept override {
        return "ERRO: jogada invalida";
    }
};

class size_exceeded final: public std::exception {
public:
    const char* what() const noexcept override {
        return "ERRO: comando excedeu o limite de tamanho";
    }
};

#endif //EXCEPTIONS_HPP
