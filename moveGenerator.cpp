#include "board.h"
#include "move.h"
#include "moveGenerator.h"
#include "tools.h"
#include <vector>
move moves[51][MAXMOVES + 5];
int movesSize[51];
void generateMoves(int& depth, board& state)
{
    unsigned long long cloneMask = 0;
    movesSize[depth] = 0;
    move ax;
    unsigned long long m;
    unsigned long long playerMask = ((((state.mask[0] >> 50) & 1) == 1 ? state.mask[1] : (~state.mask[1])) & (state.mask[0])) & (~(1ll << 50));
    for(m = playerMask; m >= 1; m -= (m&(-m)))
        cloneMask |= (adjiacentMask[(63 - __builtin_clzll((m&(-m))))] & (~state.mask[0]));
    for(unsigned long long m = cloneMask; m >= 1; m -= (m&(-m)))
        {ax.init(0, 0, (63 - __builtin_clzll((m&(-m)))), ((state.mask[0] >> 50) & 1), 1 + __builtin_popcountll(adjiacentMask[(63 - __builtin_clzll((m&(-m))))] & state.mask[0] & (((state.mask[0] >> 50) & 1) == 1 ? (~state.mask[1]) : (state.mask[1])))); moves[depth][movesSize[depth]++] = ax;}
    for(m = playerMask; m >= 1; m -= (m&(-m)))
    {
        cloneMask = (adjiacentJumpMask[(63 - __builtin_clzll(m&(-m)))] & (~state.mask[0]));
        for(playerMask = cloneMask; playerMask >= 1; playerMask -= (playerMask&(-playerMask)))
            {ax.init(1, (63 - __builtin_clzll(m&(-m))), (63 - __builtin_clzll(playerMask&(-playerMask))), ((state.mask[0] >> 50) & 1), __builtin_popcountll(adjiacentMask[(63 - __builtin_clzll((playerMask&(-playerMask))))] & state.mask[0] & (((state.mask[0] >> 50) & 1) == 1 ? (~state.mask[1]) : (state.mask[1])))); moves[depth][movesSize[depth]++] = ax;}
    }
}