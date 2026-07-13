#include "transpositionTable.h"
#include "board.h"
#include "move.h"
#include "tools.h"
#include <iostream>
TTEntry TT[TTSize];
TTEntry nullEntry;
void declareNullEntry()
{
    nullEntry.type = -100;
}
void addTTEntry(board& brd, move& bestFoundMove, int& maxScore, int& stateDepth, char& tp)
{
    TTEntry auxx = getTTEntry(brd);
    if((!TT[brd.key[0] & (TTSize - 1)].key[0]) || TT[brd.key[0] & (TTSize - 1)].depth < stateDepth)
    {
        TT[brd.key[0] & (TTSize - 1)].key[0] = brd.key[0];
        TT[brd.key[0] & (TTSize - 1)].key[1] = brd.key[1];
        TT[brd.key[0] & (TTSize - 1)].bestMove = bestFoundMove;
        TT[brd.key[0] & (TTSize - 1)].score = maxScore;
        TT[brd.key[0] & (TTSize - 1)].depth = stateDepth;
        TT[brd.key[0] & (TTSize - 1)].type = tp;
    }
}
TTEntry getTTEntry(board& state)
{
    if(!(TT[state.key[0] & (TTSize - 1)].key[0] == state.key[0] && TT[state.key[0] & (TTSize - 1)].key[1] == state.key[1]))
        return nullEntry;
    return TT[state.key[0] & (TTSize - 1)];
}
