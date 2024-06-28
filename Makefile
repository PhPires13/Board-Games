CC=g++
CFLAGS=-std=c++11 -Wall
INCLUDE_DIR=include
SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin

all: $(BIN_DIR)/board_games

$(OBJ_DIR)/BoardGame.o: $(INCLUDE_DIR)/BoardGame.hpp $(SRC_DIR)/BoardGame.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/BoardGame.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/BoardGame.o

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/BoardGame.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/main.o

$(BIN_DIR)/board_games: $(OBJ_DIR)/BoardGame.o $(SRC_DIR)/main.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/BoardGame.o $(OBJ_DIR)/main.o -o $(BIN_DIR)/board_games

clean:
	rm -f board_games $(OBJ_DIR)/*.o