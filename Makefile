CC=g++
CFLAGS=-std=c++11 -Wall
INCLUDE_DIR=include
SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin

all: $(BIN_DIR)/Board_Games

$(OBJ_DIR)/Utils.o: $(INCLUDE_DIR)/Utils.hpp $(SRC_DIR)/Utils.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Utils.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/Utils.o

$(OBJ_DIR)/exceptions.o: $(INCLUDE_DIR)/exceptions.hpp $(SRC_DIR)/exceptions.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/exceptions.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/exceptions.o

$(OBJ_DIR)/Board.o: $(INCLUDE_DIR)/Board.hpp $(SRC_DIR)/Board.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Board.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/Board.o

$(OBJ_DIR)/Player.o: $(INCLUDE_DIR)/Player.hpp $(SRC_DIR)/Player.cpp $(INCLUDE_DIR)/exceptions.hpp $(INCLUDE_DIR)/Manager.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Player.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/Player.o

$(OBJ_DIR)/BoardGame.o: $(INCLUDE_DIR)/BoardGame.hpp $(SRC_DIR)/BoardGame.cpp $(INCLUDE_DIR)/Board.hpp $(INCLUDE_DIR)/Player.hpp $(INCLUDE_DIR)/exceptions.hpp $(INCLUDE_DIR)/Utils.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/BoardGame.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/BoardGame.o

$(OBJ_DIR)/TicTacToe.o: $(INCLUDE_DIR)/TicTacToe.hpp $(SRC_DIR)/TicTacToe.cpp $(INCLUDE_DIR)/BoardGame.hpp $(INCLUDE_DIR)/Board.hpp $(INCLUDE_DIR)/Player.hpp $(INCLUDE_DIR)/exceptions.hpp $(INCLUDE_DIR)/Utils.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/TicTacToe.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/TicTacToe.o

$(OBJ_DIR)/Reversi.o: $(INCLUDE_DIR)/Reversi.hpp $(SRC_DIR)/Reversi.cpp $(INCLUDE_DIR)/BoardGame.hpp $(INCLUDE_DIR)/Board.hpp $(INCLUDE_DIR)/Player.hpp $(INCLUDE_DIR)/exceptions.hpp $(INCLUDE_DIR)/Utils.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Reversi.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/Reversi.o

$(OBJ_DIR)/Manager.o: $(INCLUDE_DIR)/Manager.hpp $(SRC_DIR)/Manager.cpp $(INCLUDE_DIR)/BoardGame.hpp $(INCLUDE_DIR)/Player.hpp $(INCLUDE_DIR)/exceptions.hpp $(INCLUDE_DIR)/Reversi.hpp $(INCLUDE_DIR)/TicTacToe.hpp $(INCLUDE_DIR)/Utils.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Manager.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/Manager.o

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/Manager.hpp $(INCLUDE_DIR)/Player.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/main.o

$(BIN_DIR)/Board_Games: $(OBJ_DIR)/Utils.o $(OBJ_DIR)/exceptions.o $(OBJ_DIR)/Board.o $(OBJ_DIR)/Player.o $(OBJ_DIR)/BoardGame.o $(OBJ_DIR)/TicTacToe.o $(OBJ_DIR)/Reversi.o $(OBJ_DIR)/Manager.o $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/*.o -o $(BIN_DIR)/Board_Games

clean:
	rm -f $(BIN_DIR)/Board_Games $(OBJ_DIR)/*.o