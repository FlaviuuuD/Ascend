#include "evaluate.h"
#include "board.h"
#include "tools.h"
#include <algorithm>
const int POSITIONING_MINUS = -8;
const int POSITIONING_PLUS = 15;
const int EXPANSION = 25;
const int MOBILITY = 15;
const int DANGER = 60;
const int CONSTTOKENS = 20;
int evaluate(board& state)
{
    if(state.numberOfTokens[1] == 0)
        return (-INF - (1000));
    if(state.numberOfTokens[0] == 0)
        return (INF + (1000));
    if(state.numberOfTokens[0] + state.numberOfTokens[1] == 49)
        return ((state.numberOfTokens[1] > state.numberOfTokens[0] ? (INF + (state.numberOfTokens[1] - state.numberOfTokens[0])) : (-INF - (state.numberOfTokens[0] - state.numberOfTokens[1]))));
    return (((state.numberOfTokens[1] - state.numberOfTokens[0]) *  CONSTTOKENS) + state.positionScore); 
    /*int tokenDifference = (state.numberOfTokens[1] - state.numberOfTokens[0]) * ((state.numberOfTokens[1] + state.numberOfTokens[0]) * CONSTTOKENS); 
    int positioning = 0;
    unsigned long long ourMask = (state.mask[1]);
    unsigned long long enemyMask = (state.mask[0] & (~(state.mask[1]))) & (~(1ll << 50));
    unsigned long long m;
    int expansion = 0;
    unsigned long long cloneMask = 0, jumpMask = 0;
    int mobility = 0;
    int danger = 0;
    int danger2 = 0;
    int axlog;
    for(m = ourMask; m >= 1; m -= (m&(-m)))
    {
        axlog = (63 - __builtin_clzll(m&(-m)));
        cloneMask |= (adjiacentMask[axlog] & (~(state.mask[0])));
        jumpMask |= (adjiacentJumpMask[axlog] & (~(state.mask[0])));
        positioning += (3 - (std::min({(axlog / 7 - (axlog % 7 == 0) + 1) - 1, 7 - (axlog / 7 - (axlog % 7 == 0) + 1), (axlog % 7 == 0 ? 7 : axlog % 7) - 1, 7 - (axlog % 7 == 0 ? 7 : axlog % 7)}))) * 
        ((state.numberOfTokens[0] + state.numberOfTokens[1]) < 10 ? POSITIONING_MINUS : POSITIONING_PLUS);
        danger2 = std::max(danger2, __builtin_popcountll((state.mask[0]) & (~state.mask[1]) & (captureMask[axlog])));
    }
    expansion = EXPANSION * (__builtin_popcountll(cloneMask));
    mobility = MOBILITY * (__builtin_popcountll(jumpMask));
    cloneMask = 0;
    jumpMask = 0;
    for(m = enemyMask; m >= 1; m -= (m&(-m)))
    {
        axlog = (63 - __builtin_clzll(m&(-m)));
        cloneMask |= (adjiacentMask[axlog] & (~(state.mask[0])));
        jumpMask |= (adjiacentJumpMask[axlog] & (~(state.mask[0])));
        danger = std::max(danger, __builtin_popcountll((state.mask[0]) & (state.mask[1]) & (captureMask[axlog])));
        positioning -= (3 - (std::min({(axlog / 7 - (axlog % 7 == 0) + 1) - 1, 7 - (axlog / 7 - (axlog % 7 == 0) + 1), (axlog % 7 == 0 ? 7 : axlog % 7) - 1, 7 - (axlog % 7 == 0 ? 7 : axlog % 7)}))) * 
        ((state.numberOfTokens[0] + state.numberOfTokens[1]) < 10 ? POSITIONING_MINUS : POSITIONING_PLUS);
    }
    expansion -= EXPANSION * (__builtin_popcountll(cloneMask));
    mobility -= MOBILITY * (__builtin_popcountll(jumpMask));
    danger = danger * (-DANGER);
    danger += danger2 * (DANGER);
    //std::cerr << tokenDifference << " " << tokensInDanger << " " << positioning << " " << expansion << " " << mobility << " " << danger << '\n';
    return (tokenDifference + positioning + expansion + mobility + danger);*/
}