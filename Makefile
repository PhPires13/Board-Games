ifeq ($(OS),Windows_NT)
    RM = del
else
    RM = rm -f
endif

CC=g++
CFLAGS=-std=c++11 -Wall
INCLUDE_DIR=include
SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
TESTS_DIR=tests
TESTS_OBJ_DIR=$(OBJ_DIR)/tests
TESTS_BIN_DIR=$(BIN_DIR)/tests
THIRD_PARTY_DIR=third_party

# ------------------------------------------------- Main
main: $(BIN_DIR)/Board_Games

$(OBJ_DIR)/Utils.o: $(INCLUDE_DIR)/Utils.hpp $(SRC_DIR)/Utils.cpp
	$(CC) $(CFLAGS) -c --coverage $(SRC_DIR)/Utils.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/Utils.o

$(OBJ_DIR)/exceptions.o: $(INCLUDE_DIR)/exceptions.hpp $(SRC_DIR)/exceptions.cpp
	$(CC) $(CFLAGS) -c --coverage $(SRC_DIR)/exceptions.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/exceptions.o

$(OBJ_DIR)/Board.o: $(INCLUDE_DIR)/Board.hpp $(SRC_DIR)/Board.cpp
	$(CC) $(CFLAGS) -c --coverage $(SRC_DIR)/Board.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/Board.o

$(OBJ_DIR)/Player.o: $(INCLUDE_DIR)/Player.hpp $(SRC_DIR)/Player.cpp $(INCLUDE_DIR)/exceptions.hpp $(INCLUDE_DIR)/Manager.hpp $(INCLUDE_DIR)/Utils.hpp
	$(CC) $(CFLAGS) -c --coverage $(SRC_DIR)/Player.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/Player.o

$(OBJ_DIR)/BoardGame.o: $(INCLUDE_DIR)/BoardGame.hpp $(SRC_DIR)/BoardGame.cpp $(INCLUDE_DIR)/Board.hpp $(INCLUDE_DIR)/Player.hpp $(INCLUDE_DIR)/exceptions.hpp $(INCLUDE_DIR)/Utils.hpp
	$(CC) $(CFLAGS) -c --coverage $(SRC_DIR)/BoardGame.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/BoardGame.o

$(OBJ_DIR)/TicTacToe.o: $(INCLUDE_DIR)/TicTacToe.hpp $(SRC_DIR)/TicTacToe.cpp $(INCLUDE_DIR)/BoardGame.hpp $(INCLUDE_DIR)/Board.hpp $(INCLUDE_DIR)/Player.hpp $(INCLUDE_DIR)/exceptions.hpp $(INCLUDE_DIR)/Utils.hpp
	$(CC) $(CFLAGS) -c --coverage $(SRC_DIR)/TicTacToe.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/TicTacToe.o

$(OBJ_DIR)/Reversi.o: $(INCLUDE_DIR)/Reversi.hpp $(SRC_DIR)/Reversi.cpp $(INCLUDE_DIR)/BoardGame.hpp $(INCLUDE_DIR)/Board.hpp $(INCLUDE_DIR)/Player.hpp $(INCLUDE_DIR)/exceptions.hpp $(INCLUDE_DIR)/Utils.hpp
	$(CC) $(CFLAGS) -c --coverage $(SRC_DIR)/Reversi.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/Reversi.o

$(OBJ_DIR)/ConnectFour.o: $(INCLUDE_DIR)/ConnectFour.hpp $(SRC_DIR)/ConnectFour.cpp $(INCLUDE_DIR)/BoardGame.hpp $(INCLUDE_DIR)/Board.hpp $(INCLUDE_DIR)/Player.hpp $(INCLUDE_DIR)/exceptions.hpp $(INCLUDE_DIR)/Utils.hpp
	$(CC) $(CFLAGS) -c --coverage $(SRC_DIR)/ConnectFour.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/ConnectFour.o

$(OBJ_DIR)/Manager.o: $(INCLUDE_DIR)/Manager.hpp $(SRC_DIR)/Manager.cpp $(INCLUDE_DIR)/BoardGame.hpp $(INCLUDE_DIR)/Player.hpp $(INCLUDE_DIR)/exceptions.hpp $(INCLUDE_DIR)/TicTacToe.hpp $(INCLUDE_DIR)/Reversi.hpp $(INCLUDE_DIR)/ConnectFour.hpp $(INCLUDE_DIR)/Utils.hpp
	$(CC) $(CFLAGS) -c --coverage $(SRC_DIR)/Manager.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/Manager.o

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/Manager.hpp $(INCLUDE_DIR)/Player.hpp
	$(CC) $(CFLAGS) -c --coverage $(SRC_DIR)/main.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/main.o

$(BIN_DIR)/Board_Games: $(OBJ_DIR)/Utils.o $(OBJ_DIR)/exceptions.o $(OBJ_DIR)/Board.o $(OBJ_DIR)/Player.o $(OBJ_DIR)/BoardGame.o $(OBJ_DIR)/TicTacToe.o $(OBJ_DIR)/Reversi.o $(OBJ_DIR)/ConnectFour.o $(OBJ_DIR)/Manager.o $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS) --coverage $(OBJ_DIR)/*.o -o $(BIN_DIR)/Board_Games


# ------------------------------------------------- Tests
tests: $(BIN_DIR)/Board_Games $(TESTS_BIN_DIR)/Board_Games_Tests

$(TESTS_OBJ_DIR)/UtilsTests.o: $(TESTS_DIR)/UtilsTests.cpp $(INCLUDE_DIR)/Utils.hpp $(THIRD_PARTY_DIR)/doctest.h
	$(CC) $(CFLAGS) -c --coverage $(TESTS_DIR)/UtilsTests.cpp -I $(INCLUDE_DIR) -I $(THIRD_PARTY_DIR) -o $(TESTS_OBJ_DIR)/UtilsTests.o

$(TESTS_OBJ_DIR)/exceptionsTests.o: $(TESTS_DIR)/exceptionsTests.cpp $(INCLUDE_DIR)/exceptions.hpp $(THIRD_PARTY_DIR)/doctest.h
	$(CC) $(CFLAGS) -c --coverage $(TESTS_DIR)/exceptionsTests.cpp -I $(INCLUDE_DIR) -I $(THIRD_PARTY_DIR) -o $(TESTS_OBJ_DIR)/exceptionsTests.o

$(TESTS_OBJ_DIR)/BoardTests.o: $(TESTS_DIR)/BoardTests.cpp $(INCLUDE_DIR)/Board.hpp $(INCLUDE_DIR)/exceptions.hpp $(THIRD_PARTY_DIR)/doctest.h
	$(CC) $(CFLAGS) -c --coverage $(TESTS_DIR)/BoardTests.cpp -I $(INCLUDE_DIR) -I $(THIRD_PARTY_DIR) -o $(TESTS_OBJ_DIR)/BoardTests.o

$(TESTS_OBJ_DIR)/BoardGameTests.o: $(TESTS_DIR)/BoardGameTests.cpp $(INCLUDE_DIR)/BoardGame.hpp $(INCLUDE_DIR)/Player.hpp $(INCLUDE_DIR)/exceptions.hpp $(THIRD_PARTY_DIR)/doctest.h
	$(CC) $(CFLAGS) -c --coverage $(TESTS_DIR)/BoardGameTests.cpp -I $(INCLUDE_DIR) -I $(THIRD_PARTY_DIR) -o $(TESTS_OBJ_DIR)/BoardGameTests.o

$(TESTS_OBJ_DIR)/PlayerTests.o: $(TESTS_DIR)/PlayerTests.cpp $(INCLUDE_DIR)/Player.hpp $(INCLUDE_DIR)/Manager.hpp $(INCLUDE_DIR)/exceptions.hpp $(THIRD_PARTY_DIR)/doctest.h
	$(CC) $(CFLAGS) -c --coverage $(TESTS_DIR)/PlayerTests.cpp -I $(INCLUDE_DIR) -I $(THIRD_PARTY_DIR) -o $(TESTS_OBJ_DIR)/PlayerTests.o

$(TESTS_OBJ_DIR)/TicTacToeTests.o: $(TESTS_DIR)/TicTacToeTests.cpp $(INCLUDE_DIR)/TicTacToe.hpp $(INCLUDE_DIR)/Player.hpp $(INCLUDE_DIR)/exceptions.hpp $(THIRD_PARTY_DIR)/doctest.h
	$(CC) $(CFLAGS) -c --coverage $(TESTS_DIR)/TicTacToeTests.cpp -I $(INCLUDE_DIR) -I $(THIRD_PARTY_DIR) -o $(TESTS_OBJ_DIR)/TicTacToeTests.o

$(TESTS_OBJ_DIR)/ReversiTests.o: $(TESTS_DIR)/ReversiTests.cpp $(INCLUDE_DIR)/Reversi.hpp $(INCLUDE_DIR)/Player.hpp $(INCLUDE_DIR)/exceptions.hpp $(THIRD_PARTY_DIR)/doctest.h
	$(CC) $(CFLAGS) -c --coverage $(TESTS_DIR)/ReversiTests.cpp -I $(INCLUDE_DIR) -I $(THIRD_PARTY_DIR) -o $(TESTS_OBJ_DIR)/ReversiTests.o

$(TESTS_OBJ_DIR)/ConnectFourTests.o: $(TESTS_DIR)/ConnectFourTests.cpp $(INCLUDE_DIR)/ConnectFour.hpp $(INCLUDE_DIR)/Player.hpp $(INCLUDE_DIR)/exceptions.hpp $(THIRD_PARTY_DIR)/doctest.h
	$(CC) $(CFLAGS) -c --coverage $(TESTS_DIR)/ConnectFourTests.cpp -I $(INCLUDE_DIR) -I $(THIRD_PARTY_DIR) -o $(TESTS_OBJ_DIR)/ConnectFourTests.o

$(TESTS_OBJ_DIR)/ManagerTests.o: $(TESTS_DIR)/ManagerTests.cpp $(INCLUDE_DIR)/Manager.hpp $(INCLUDE_DIR)/Player.hpp $(INCLUDE_DIR)/exceptions.hpp $(THIRD_PARTY_DIR)/doctest.h
	$(CC) $(CFLAGS) -c --coverage $(TESTS_DIR)/ManagerTests.cpp -I $(INCLUDE_DIR) -I $(THIRD_PARTY_DIR) -o $(TESTS_OBJ_DIR)/ManagerTests.o

$(TESTS_OBJ_DIR)/tests.o: $(TESTS_DIR)/tests.cpp $(THIRD_PARTY_DIR)/doctest.h $(TESTS_DIR)/UtilsTests.cpp $(TESTS_DIR)/exceptionsTests.cpp $(TESTS_DIR)/BoardTests.cpp $(TESTS_DIR)/BoardGameTests.cpp $(TESTS_DIR)/PlayerTests.cpp $(TESTS_DIR)/TicTacToeTests.cpp $(TESTS_DIR)/ReversiTests.cpp $(TESTS_DIR)/ConnectFourTests.cpp $(TESTS_DIR)/ManagerTests.cpp
	$(CC) $(CFLAGS) -c --coverage $(TESTS_DIR)/tests.cpp -I $(INCLUDE_DIR) -I $(THIRD_PARTY_DIR) -o $(TESTS_OBJ_DIR)/tests.o

$(TESTS_BIN_DIR)/Board_Games_Tests: $(TESTS_OBJ_DIR)/UtilsTests.o $(TESTS_OBJ_DIR)/exceptionsTests.o $(TESTS_OBJ_DIR)/BoardTests.o $(TESTS_OBJ_DIR)/BoardGameTests.o $(TESTS_OBJ_DIR)/PlayerTests.o $(TESTS_OBJ_DIR)/TicTacToeTests.o $(TESTS_OBJ_DIR)/ReversiTests.o $(TESTS_OBJ_DIR)/ConnectFourTests.o $(TESTS_OBJ_DIR)/ManagerTests.o $(TESTS_OBJ_DIR)/tests.o \
									$(OBJ_DIR)/Utils.o $(OBJ_DIR)/exceptions.o $(OBJ_DIR)/Board.o $(OBJ_DIR)/Player.o $(OBJ_DIR)/BoardGame.o $(OBJ_DIR)/TicTacToe.o $(OBJ_DIR)/Reversi.o $(OBJ_DIR)/ConnectFour.o $(OBJ_DIR)/Manager.o
	$(CC) $(CFLAGS) --coverage $(TESTS_OBJ_DIR)/*.o $(filter-out $(OBJ_DIR)/main.o, $(wildcard $(OBJ_DIR)/*.o)) -o $(TESTS_BIN_DIR)/Board_Games_Tests


# ------------------------------------------------- Clean
clean: clean_coverage
	$(RM) \
	$(BIN_DIR)/Board_Games $(TESTS_BIN_DIR)/Board_Games_Tests \
	$(OBJ_DIR)/*.o $(OBJ_DIR)/*/*.o \
	$(OBJ_DIR)/*.gcno $(OBJ_DIR)/*/*.gcno

clean_coverage:
	$(RM) $(OBJ_DIR)/*.gcda $(OBJ_DIR)/*/*.gcda
