//
// Created by Paulo Henrique Pires  on 16/08/24.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#define private public
#define protected public

#include "UtilsTests.cpp" // utils has to be the first test since it clears the terminal
#include "BoardTests.cpp"
#include "BoardGameTests.cpp"
#include "TicTacToeTests.cpp"
#include "PlayerTests.cpp"
#include "ManagerTests.cpp"
#include "exceptionsTests.cpp"

#undef private
#undef protected
