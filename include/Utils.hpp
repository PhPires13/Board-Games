//
// Created by Pedro Henrique Pires  on 30/07/24.
//

#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <string>

// TODO: criar .cpp

class Utils {
public:
    static std::string cleanString(const std::string& input) {
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

    static void clearTerminal() {
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
    }
};

#endif //UTILS_HPP
