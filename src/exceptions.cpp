//
// Created by Paulo Henrique Pires  on 05/08/24.
//

#include "exceptions.hpp"

const char* invalid_command::what() const noexcept {
    return "ERRO: comando invalido";
}

const char* game_not_found::what() const noexcept {
    return "ERRO: jogo inexistente";
}

const char* incorrect_data::what() const noexcept {
    return "ERRO: dados incorretos";
}

const char* player_not_found::what() const noexcept {
    return "ERRO: jogador inexistente";
}

const char* file_error::what() const noexcept {
    return "ERRO: erro ao lidar com arquivo";
}

const char* duplicated_player::what() const noexcept {
    return "ERRO: jogador repetido";
}

const char* incorrect_format::what() const noexcept {
    return "ERRO: formato incorreto";
}

const char* invalid_move::what() const noexcept {
    return "ERRO: jogada invalida";
}

const char* size_exceeded::what() const noexcept {
    return "ERRO: comando excedeu o limite de tamanho";
}
