CC=g++
CFLAGS=-std=c++11 -Wall
SRC_DIR=src
INCLUDE_DIR=include
OBJ_DIR=obj

all: board_games

$(OBJ_DIR)/BoardGame.o: $(INCLUDE_DIR)/BoardGame.hpp $(SRC_DIR)/BoardGame.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/BoardGame.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/BoardGame.o

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/BoardGame.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -I $(INCLUDE_DIR) -o $(OBJ_DIR)/main.o

board_games: $(OBJ_DIR)/BoardGame.o $(SRC_DIR)/main.o
	$(CC) $(CFLAGS) $(OBJ_DIR)/BoardGame.o $(OBJ_DIR)/main.o -o board_games

clean:
	rm -f board_games $(OBJ_DIR)/*.o