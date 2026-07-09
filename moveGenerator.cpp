#include "board.h"
#include "move.h"
#include "tools.h"
#include <vector>
std::vector<move> generateMoves(board& state)
{
    std::vector<move> rez;
    unsigned long long cloneMask = 0;
    move ax;
    unsigned long long m;
    unsigned long long playerMask = ((state.getMovingPlayer() == 1 ? state.mask[1] : (~state.mask[1])) & (state.mask[0]));
    for(m = playerMask; m >= 1; m -= (m&(-m)))
        cloneMask |= (adjiacentMask[(63 - __builtin_clzll((m&(-m))))] & (~state.mask[0]));
    for(unsigned long long m = cloneMask; m >= 1; m -= (m&(-m)))
        {ax.init(0, 0, (63 - __builtin_clzll((m&(-m)))), state.getMovingPlayer()); rez.push_back(ax);}
    for(m = playerMask; m >= 1; m -= (m&(-m)))
    {
        cloneMask = (adjiacentJumpMask[(63 - __builtin_clzll(m&(-m)))] & (~state.mask[0]));
        for(playerMask = cloneMask; playerMask >= 1; playerMask -= (playerMask&(-playerMask)))
            {ax.init(1, (63 - __builtin_clzll(m&(-m))), (63 - __builtin_clzll(playerMask&(-playerMask))), state.getMovingPlayer()); rez.push_back(ax);}
    }
    return rez;
}