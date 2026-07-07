#include "transpositionTable.h"
#include "board.h"
TTEntry addTTEntry(board& brd, move& bestFoundMove, int& maxScore, int& stateDepth, char& tp)
{
    TT[brd.key[0] & (TTSize - 1)].key[0] = brd.key[0];
    TT[brd.key[0] & (TTSize - 1)].key[1] = brd.key[1];
    TT[brd.key[0] & (TTSize - 1)].bestMove = bestFoundMove;
    TT[brd.key[0] & (TTSize - 1)].score = maxScore;
    TT[brd.key[0] & (TTSize - 1)].depth = stateDepth;
    TT[brd.key[0] & (TTSize - 1)].type = tp;
}
bool doesEntryExist(int key0, int key1)
{
    return (TT[key0].key[1] == key1);    
}
TTEntry getTTEntry(int key0)
{
    return TT[key0];
}