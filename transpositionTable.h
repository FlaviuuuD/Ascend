#pragma once
#include "move.h"
const int TTSize = (1 << 22);
struct TTEntry{
    unsigned long long key[2];
    move bestMove;
    int score;
    int depth;
    char type; //tipul: daca mutarea este exacta, avem 0. daca este <= scor, atunci avem 1. daca este >= scor, atunci avem 2. 
};
TTEntry TT[TTSize];
TTEntry getTTEntry();
bool doesEntryExist(int key0, int key1);
void addTTEntry();