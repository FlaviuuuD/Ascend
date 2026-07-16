#pragma once
#include "board.h"
#include "move.h"
#include <vector>
const int MAXMOVES = 500;
extern move moves[51][MAXMOVES + 5];
extern int movesSize[51];
void generateMoves(int& depth, board& state);