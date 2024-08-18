//
// Created by Paulo Henrique Pires  on 17/08/24.
//

#include "doctest.h"

#define private public
#define protected public

#include "exceptions.hpp"

#undef private
#undef protected

TEST_SUITE("Exceptions") {
    TEST_CASE("Throw") {
        CHECK_THROWS_AS(throw invalid_command(), invalid_command);
        CHECK_THROWS_AS(throw game_not_found(), game_not_found);
        CHECK_THROWS_AS(throw incorrect_data(), incorrect_data);
        CHECK_THROWS_AS(throw player_not_found(), player_not_found);
        CHECK_THROWS_AS(throw file_error(), file_error);
        CHECK_THROWS_AS(throw duplicated_player(), duplicated_player);
        CHECK_THROWS_AS(throw incorrect_format(), incorrect_format);
        CHECK_THROWS_AS(throw invalid_move(), invalid_move);
        CHECK_THROWS_AS(throw size_exceeded(), size_exceeded);

        CHECK_THROWS_AS(throw invalid_command(), std::exception);
        CHECK_THROWS_AS(throw game_not_found(), std::exception);
        CHECK_THROWS_AS(throw incorrect_data(), std::exception);
        CHECK_THROWS_AS(throw player_not_found(), std::exception);
        CHECK_THROWS_AS(throw file_error(), std::exception);
        CHECK_THROWS_AS(throw duplicated_player(), std::exception);
        CHECK_THROWS_AS(throw incorrect_format(), std::exception);
        CHECK_THROWS_AS(throw invalid_move(), std::exception);
        CHECK_THROWS_AS(throw size_exceeded(), std::exception);
    }

    TEST_CASE("What") {
        CHECK_NOTHROW(invalid_command().what());
        CHECK_NOTHROW(game_not_found().what());
        CHECK_NOTHROW(incorrect_data().what());
        CHECK_NOTHROW(player_not_found().what());
        CHECK_NOTHROW(file_error().what());
        CHECK_NOTHROW(duplicated_player().what());
        CHECK_NOTHROW(incorrect_format().what());
        CHECK_NOTHROW(invalid_move().what());
        CHECK_NOTHROW(size_exceeded().what());
    }
}