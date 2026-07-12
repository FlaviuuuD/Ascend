#pragma once
#include "board.h"
#include "move.h"
#include <vector>
const int MAXMOVES = 500;
extern move moves[15][MAXMOVES + 5];
extern int movesSize[15];
void generateMoves(int& depth, board& state);