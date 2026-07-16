#pragma once
#include "move.h"
#include "board.h"
const int TTSize = (1 << 24);
struct TTEntry{
    unsigned long long key[2];
    unsigned char bestMove;
    int score;
    unsigned char depth;
    unsigned char type;
    //tipul: daca mutarea este exacta, avem 0. daca este <= scor, atunci avem 1. daca este >= scor, atunci avem 2. 
};
extern TTEntry TT[TTSize];
void declareNullEntry();
void addTTEntry(board& brd, unsigned char& bestFoundMove, int& maxScore, int& stateDepth, char& tp);
TTEntry getTTEntry(board& state);
