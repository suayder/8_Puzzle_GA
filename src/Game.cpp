#include "Game.h"


using namespace std;
using namespace Game;

int* GameState::initial = new int[9];
int* GameState::objetivo = new int[9];


GameState::GameState()
{
    vazio = -1;
    for (int i = 0; i < 9; i++)
    {
        tabuleiro[i] = initial[i];
        if(vazio==-1 && tabuleiro[i] == 0) vazio = i;
    }
}
    
void GameState::resetState()
{
    for (int i = 0; i < 9; i++)
    {
        tabuleiro[i] = initial[i];
        if(vazio==-1 && tabuleiro[i] == 0) vazio = i;
    }
}

bool GameState::moveUp()
{
    if(vazio <= 2) return false;
    swapInt(&tabuleiro[vazio], &tabuleiro[vazio-3]);
    vazio -= 3;
    this->moves.push_back(UP);
    #ifdef DBG
        if (vazio < 0 || vazio > 8)
        {
            printf("!!!moveUp: vazio FORA DO RANGE!!!\n");
            exit(-1);
        }
    #endif // DBG
    return true;
}

bool GameState::moveDown()
{
    if(vazio > 5) return false;
    swapInt(&tabuleiro[vazio], &tabuleiro[vazio+3]);
    vazio +=3;
    this->moves.push_back(DOWN);
    #ifdef DBG
        if (vazio < 0 || vazio > 8)
        {
            printf("!!!moveDown: vazio FORA DO RANGE!!!\n");
            exit(-1);
        }
    #endif // DBG
    return true;
}

bool GameState::moveLeft()
{
    if(vazio % 3 == 0) return false;
    swapInt(&tabuleiro[vazio], &tabuleiro[vazio-1]);
    vazio -= 1;
    this->moves.push_back(LEFT);
    #ifdef DBG
        if (vazio < 0 || vazio > 8)
        {
            printf("!!!moveLeft: vazio FORA DO RANGE!!!\n");
            exit(-1);
        }
    #endif // DBG
    return true;
}

bool GameState::moveRight()
{
    if(vazio % 3 == 2) return false;
    swapInt(&tabuleiro[vazio], &tabuleiro[vazio+1]);
    vazio += 1;
    this->moves.push_back(RIGHT);
    #ifdef DBG
        if (vazio < 0 || vazio > 8)
        {
            printf("!!!moveRight: vazio FORA DO RANGE!!!\n");
            exit(-1);
        }
    #endif // DBG
    return true;
}

bool GameState::applyMove(movimentos move)
{
    switch (move)
    {
        case UP:
            return moveUp();
            break;
        case DOWN:
            return moveDown();
            break;
        case LEFT:
            return moveLeft();
            break;
        case RIGHT:
            return moveRight();
            break;
        default:
            #ifdef DBG
                printf("%d\n", move);
                printf("applyMove: SOMETHING IS WRONG!\n");
            #endif // DBG
        break;
    }
    return false;
}



void print_state(int* game_state)
{
	int i;
	for (i = 0; i < 9; i++)
	{
		if(game_state[i]==8)
			printf("_ ");
		else
			printf("%d ", game_state[i]+1);
		if ((i + 1) % 3 == 0)
			printf("\n");
	}
}

int isSolvable(int* block)
{
	int i, j, count;
	count = 0;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (block[i] > block[j])
			{
				count++;
			}
		}
	}
	return count%2;
}

int isGoal(int* block, int* g_block)
{	
	int i;
	for (i = 0; i < 9; i++)
	{
		if (block[i] != g_block[i])
			return 0;
	}

	return 1;
}

int GameState::isGoal()
{	
	int i;
	for (i = 0; i < 9; i++)
	{
		if (tabuleiro[i] != objetivo[i])
			return 0;
	}

	return 1;
}

int manhattan(int* block, int* g_block)
{
    int to_return = 0;

	for (int i = 0; i<9; i++)
	{
		to_return += abs((g_block[i] / 3) - (block[i] / 3));
		to_return += abs((g_block[i] % 3) - (block[i] % 3));
	}
	return to_return;
}

void swapInt(int *a, int *b)
{
    *a += *b;
    *b = *a - *b;
    *a -= *b;
}

GameState* test;