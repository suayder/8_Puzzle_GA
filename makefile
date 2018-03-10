INC_DIR = include
SRC_DIR = src
OBJ_DIR = obj
CXX = g++
CFLAGS  = -std=c++11 -c -Wall -Ofast -lm -Iinclude/
SRCS = $(SRC_DIR)/Game.cpp $(SRC_DIR)/GA.cpp $(SRC_DIR)/main.cpp
OBJS = $(OBJ_DIR)/Game.o $(OBJ_DIR)/GA.o $(OBJ_DIR)/main.o
# Note: The above will soon get unwieldy.
# The wildcard and patsubt commands will come to your rescue.

DEPS = $(INC_DIR)/Game.h $(INC_DIR)/GA.h $(INC_DIR)/main.h
# Note: The above will soon get unwieldy.
# You will soon want to use an automatic dependency generator.


all: $(OBJS) $(OBJ_DIR)/main

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main: $(OBJS)
	$(CXX) $(OBJS) -g -Wall -o 8_Puzzle

clean:
	rm -f $(OBJ_DIR)/*
	rm -f 8_Puzzle