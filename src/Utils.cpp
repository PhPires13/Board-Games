//
// Created by Paulo Henrique Pires  on 05/08/24.
//

#include "Utils.hpp"

std::string Utils::cleanString(const std::string& input) {
    std::string output;
    bool inWhitespace = false;

    for (const char ch : input) {
        if (std::isspace(ch)) {
            if (!inWhitespace) {
                output += ' '; // Replace any whitespace character with a single space
                inWhitespace = true;
            }
        } else {
            output += ch;
            inWhitespace = false;
        }
    }

    // Remove trailing space if there is any
    if (!output.empty() && output.back() == ' ') {
        output.pop_back();
    }

    // Remove leading space if there is any
    if (!output.empty() && output.front() == ' ') {
        output.erase(output.begin());
    }

    return output;
}

void Utils::clearTerminal() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}
