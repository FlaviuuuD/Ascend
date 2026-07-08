#pragma once
#include "move.h"
#include "board.h"
const int TTSize = (1 << 22);
struct TTEntry{
    unsigned long long key[2];
    move bestMove;
    int score;
    int depth;
    char type; //tipul: daca mutarea este exacta, avem 0. daca este <= scor, atunci avem 1. daca este >= scor, atunci avem 2. 
};
void addTTEntry(board& brd, move& bestFoundMove, int& maxScore, int& stateDepth, char& tp);
bool doesEntryExist(unsigned long long& key0, unsigned long long& key1);
TTEntry getTTEntry(unsigned long long& key0);
