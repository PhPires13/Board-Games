//
// Created by Pedro Henrique Pires  on 30/07/24.
//

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

/**
 * Class with utility functions
 */
class Utils {
public:
    /**
     * Remove all the duplicated "invisible" characters from a string\n
     * Also from the beginning and the end\n
     * Leaving only one space between words
     *
     * @param input string to clean
     *
     * @return cleaned string
     */
    static std::string cleanString(const std::string& input);

    /**
     * Clear the terminal screen, for windows and unix
     */
    static void clearTerminal();
};

#endif //UTILS_HPP
