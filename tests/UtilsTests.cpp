//
// Created by Paulo Henrique Pires  on 17/08/24.
//

#include "doctest.h"

#define private public
#define protected public

#include "Utils.hpp"

#undef private
#undef protected

TEST_SUITE("Utils") {
    TEST_CASE("Clear Terminal") { // Has to be the first test since it clears the terminal
        CHECK_NOTHROW(Utils::clearTerminal());
    }

    TEST_CASE("Clean String") {
        const std::string input = "  \t Hello \t\t\n   World \t - \n \t 0  ";
        const std::string expected = "Hello World - 0";
        std::string returnValue;
        CHECK_NOTHROW(returnValue = Utils::cleanString(input));
        CHECK(returnValue == expected);
    }
}