//
// Created by Paulo Henrique Pires  on 16/08/24.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#define private public
#define protected public

#include "UtilsTests.cpp" // utils has to be the first test since it clears the terminal
#include "exceptionsTests.cpp"
#include "BoardTests.cpp"
#include "BoardGameTests.cpp"
#include "PlayerTests.cpp"
#include "TicTacToeTests.cpp"
#include "ReversiTests.cpp"
#include "ConnectFourTests.cpp"
#include "ManagerTests.cpp"

#undef private
#undef protected
