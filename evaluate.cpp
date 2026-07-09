#include "evaluate.h"
#include "board.h"
#include "tools.h"
#include <algorithm>
int evaluate(board& state, int depth)
{
    if(state.numberOfTokens[1] == 0)
        return (-INF - depth);
    if(state.numberOfTokens[0] == 0)
        return (INF + depth);
    if(state.numberOfTokens[0] + state.numberOfTokens[1] == 49)
        return ((state.numberOfTokens[1] > state.numberOfTokens[0] ? (INF + depth) : (-INF - depth)));
    int tokenDifference = (state.numberOfTokens[1] - state.numberOfTokens[0]) * (8 + ((state.numberOfTokens[0] + state.numberOfTokens[1]))); 
    int tokensInDanger = 0;
    int positioning = 0;
    for(int i = 1; i <= 49; i++)
        if((state.mask[0] & (1ll << i)) && (state.mask[1] & (1ll << i)))
            positioning += (3 - (std::min({(i / 7 - (i % 7 == 0) + 1) - 1, 7 - (i / 7 - (i % 7 == 0) + 1), (i % 7 == 0 ? 7 : i % 7) - 1, 7 - (i % 7 == 0 ? 7 : i % 7)}))) * 
            ((state.numberOfTokens[0] + state.numberOfTokens[1]) < 20 ? -15 : 10);
        else if(state.mask[0] & (1ll << i))
            positioning -= (3 - (std::min({(i / 7 - (i % 7 == 0) + 1) - 1, 7 - (i / 7 - (i % 7 == 0) + 1), (i % 7 == 0 ? 7 : i % 7) - 1, 7 - (i % 7 == 0 ? 7 : i % 7)}))) * 
            ((state.numberOfTokens[0] + state.numberOfTokens[1]) < 20 ? -15 : 10);
    int expansion = 0;
    unsigned long long cloneMask = 0;
    for(int i = 1; i <= 49; i++)
        if((state.mask[0] & (1ll << i)) && (state.mask[1] & (1ll << i)))
            cloneMask |= (adjiacentMask[i] & (~(state.mask[0])));
    expansion = 25 * (__builtin_popcountll(cloneMask));
    cloneMask = 0;
    for(int i = 1; i <= 49; i++)
        if((state.mask[0] & (1ll << i)) && !(state.mask[1] & (1ll << i)))
            cloneMask |= (adjiacentMask[i] & (~(state.mask[0])));
    expansion -= 25 * (__builtin_popcountll(cloneMask));
    int mobility = 0;
    cloneMask = 0;
    for(int i = 1; i <= 49; i++)
        if((state.mask[0] & (1ll << i)) && (state.mask[1] & (1ll << i)))
            cloneMask |= (adjiacentJumpMask[i] & (~(state.mask[0])));
    mobility = 15 * (__builtin_popcountll(cloneMask));
    cloneMask = 0;
    for(int i = 1; i <= 49; i++)
        if((state.mask[0] & (1ll << i)) && !(state.mask[1] & (1ll << i)))
            cloneMask |= (adjiacentJumpMask[i] & (~(state.mask[0])));
    mobility -= 15 * (__builtin_popcountll(cloneMask));
    int danger = 0;
    for(int i = 1; i <= 49; i++)
        if((state.mask[0] & (1ll << i)) && !(state.mask[1] & (1ll << i)))
            danger = std::max(danger, __builtin_popcountll((state.mask[0]) & (state.mask[1]) & (captureMask[i])));
    danger = danger * (-30);
    int danger2 = 0;
    for(int i = 1; i <= 49; i++)
        if((state.mask[0] & (1ll << i)) && (state.mask[1] & (1ll << i)))
            danger2 = std::max(danger2, __builtin_popcountll((state.mask[0]) & (~state.mask[1]) & (captureMask[i])));
    danger += danger2 * (30);
    //std::cerr << tokenDifference << " " << tokensInDanger << " " << positioning << " " << expansion << " " << mobility << " " << danger << '\n';
    return (tokenDifference + tokensInDanger + positioning + expansion + mobility + danger);
}