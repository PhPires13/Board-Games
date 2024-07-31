//
// Created by Paulo Henrique Pires  on 31/07/24.
//

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

//TODO: validar necessidade de .cpp

class incorrect_data final: public std::exception {
public:
    const char* what () const _NOEXCEPT override {
        return "ERRO: dados incorretos";
    }
};

class player_not_found final: public std::exception {
public:
    const char* what () const _NOEXCEPT override {
        return "ERRO: jogador inexistente";
    }
};

class deletion_error final: public std::exception {
public:
    const char* what () const _NOEXCEPT override {
        return "ERRO: erro ao remover jogador";
    }
};

class duplicated_player final: public std::exception {
public:
    const char* what () const _NOEXCEPT override {
        return "ERRO: jogador repetido";
    }
};

class update_error final: public std::exception {
public:
    const char* what () const _NOEXCEPT override {
        return "ERRO: erro ao atualizar dados do jogador";
    }
};

class incorrect_format final: public std::exception {
public:
    const char* what () const _NOEXCEPT override {
        return "ERRO: formato incorreto";
    }
};

class invalid_move final: public std::exception {
public:
    const char* what () const _NOEXCEPT override {
        return "ERRO: jogada invalida";
    }
};

#endif //EXCEPTIONS_HPP
