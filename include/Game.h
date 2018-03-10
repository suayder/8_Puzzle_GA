// Game.h
#ifndef GAME_H
#define GAME_H
#include <cmath>
#include <vector>
#include <cstdio>

using namespace std;
namespace Game
{
    enum movimentos{
        UP, DOWN, LEFT, RIGHT
    };
    
}
using namespace Game;


class GameState
{
public:
    int tabuleiro[9];
    int vazio;
    static int* initial;
    static int* objetivo;
    vector<movimentos> moves;

    GameState();
    void resetState();
    bool moveUp();

    bool moveDown();

    bool moveLeft();

    bool moveRight();

    bool applyMove(movimentos move);
    int isGoal();
};


void print_state(int* game_state);
int isSolvable(int* block);
int isGoal(int* block, int* g_block);
int manhattan(int* block, int* g_block);
void swapInt(int *a, int *b);

extern GameState* test;
#endif

