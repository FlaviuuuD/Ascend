#include "transpositionTable.h"
#include "board.h"
#include "move.h"
#include <iostream>
TTEntry TT[TTSize];
void addTTEntry(board& brd, move& bestFoundMove, int& maxScore, int& stateDepth, char& tp)
{
    if(doesEntryExist(brd.key[0], brd.key[1]) || TT[brd.key[0] & (TTSize - 1)].depth >= stateDepth)
        return;
    TT[brd.key[0] & (TTSize - 1)].key[0] = brd.key[0];
    TT[brd.key[0] & (TTSize - 1)].key[1] = brd.key[1];
    TT[brd.key[0] & (TTSize - 1)].bestMove = bestFoundMove;
    TT[brd.key[0] & (TTSize - 1)].score = maxScore;
    TT[brd.key[0] & (TTSize - 1)].depth = stateDepth;
    TT[brd.key[0] & (TTSize - 1)].type = tp;
}
bool doesEntryExist(unsigned long long& key0, unsigned long long& key1)
{
    return (TT[key0 & (TTSize - 1)].key[0] == key0 && TT[key0 & (TTSize - 1)].key[1] == key1);    
}
TTEntry getTTEntry(unsigned long long& key0)
{
    return TT[key0 & (TTSize - 1)];
}