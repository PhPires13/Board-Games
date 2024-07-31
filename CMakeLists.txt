cmake_minimum_required(VERSION 3.28)
project(Board_Games)

set(CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(Board_Games src/main.cpp
        include/Board.hpp
        src/Board.cpp
        include/Player.hpp
        src/Player.cpp
        include/BoardGame.hpp
        src/BoardGame.cpp
        include/Manager.hpp
        src/Manager.cpp
        include/TicTacToe.hpp
        src/TicTacToe.cpp)
