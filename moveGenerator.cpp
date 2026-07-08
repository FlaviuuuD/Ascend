#include "board.h"
#include "move.h"
#include "tools.h"
#include <vector>
std::vector<move> generateMoves(board& state)
{
    std::vector<move> rez;
    unsigned long long cloneMask = 0;
    move ax;
    for(int i = 1; i <= 49; i++)
    {
        if((state.mask[0] & (1ll << i)) && (((state.mask[1] & (1ll << i)) != 0) == state.getMovingPlayer()))
        for(int k = 0; k < 8; k++)
            if((adjiacentMatrix[i][k] >= 1 && adjiacentMatrix[i][k] <= 49) && !(state.mask[0] & (1ll << adjiacentMatrix[i][k])))
                cloneMask |= (1ll << adjiacentMatrix[i][k]);
    }
    for(int i = 1; i <= 49; i++)
        if(cloneMask & (1ll << i))
            {ax.init(0, 0, i); rez.push_back(ax);}
    for(int i = 1; i <= 49; i++)
    {
        if((state.mask[0] & (1ll << i)) && (((state.mask[1] & (1ll << i)) != 0) == state.getMovingPlayer()))
            for(int k = 0; k < 8; k++)
                if((jumpAdjiacentMatrix[i][k] >= 1 && jumpAdjiacentMatrix[i][k] <= 49) && !(state.mask[0] & (1ll << jumpAdjiacentMatrix[i][k])))
                    {ax.init(1, i, jumpAdjiacentMatrix[i][k]); rez.push_back(ax);}
    }
    return rez;
}