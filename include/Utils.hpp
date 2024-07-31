//
// Created by Pedro Henrique Pires  on 30/07/24.
//

#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <string>

// TODO: validar criacao cpp

class Utils {
public:
    static std::string removeNonAlphaNum(std::string line) {
        // Remove non-alphanumeric characters from the begining of the line
        line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](char c) {
            return std::isalnum(c);
        }));

        // Remove non-alphanumeric characters from the end of the line
        line.erase(std::find_if(line.rbegin(), line.rend(), [](char c) {
            return std::isalnum(c);
        }).base(), line.end());

        return line;
    }
};

#endif //UTILS_HPP
