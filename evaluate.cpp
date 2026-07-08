#include "evaluate.h"
#include "board.h"
#include "tools.h"
#include <algorithm>
int sp[2][8][8];
inline int matrixSum(int a, int b, int c, int d)
{
    return (sp[0][c][d] - sp[0][c][b - 1] - sp[0][a - 1][d] + sp[0][a - 1][b - 1]);
}
inline int inDanger(int& i)
{
    return ((matrixSum(std::max((i / 7 - (i % 7 == 0) + 1) - 3, 1), std::max((i % 7 == 0 ? 7 : i % 7) - 3, 1), 
        std::min((i / 7 - (i % 7 == 0) + 1) + 3, 7), std::min((i % 7 == 0 ? 7 : i % 7) + 3, 7))) > 0);
}
int evaluate(board& state)
{
    if(state.numberOfTokens[1] == 0)
        return (-INF);
    if(state.numberOfTokens[0] == 0)
        return (INF);
    if(state.numberOfTokens[0] + state.numberOfTokens[1] == 49)
        return ((state.numberOfTokens[1] > state.numberOfTokens[0] ? INF : -INF));
    int tokenDifference = (state.numberOfTokens[1] - state.numberOfTokens[0]) * 100; 
    int tokensInDanger = 0;
    //numarul maxim de tokenuri pe care le poate lua adversarul de la noi in urmatoarea runda maxim.
    for(int i = 1; i <= 49; i++)
    {
        sp[0][(i / 7 - (i % 7 == 0) + 1)][(i % 7 == 0 ? 7 : i % 7)] = 0;
        sp[1][(i / 7 - (i % 7 == 0) + 1)][(i % 7 == 0 ? 7 : i % 7)] = 0;
        if(state.mask[0] & (1ll << i))
            sp[(state.mask[1] & (1ll << i)) != 0][(i / 7 - (i % 7 == 0) + 1)][(i % 7 == 0 ? 7 : i % 7)]++;
    }
    for(int p = 0; p <= 1; p++)
        for(int i = 1; i <= 7; i++) 
            for(int j = 1; j <= 7; j++)
                sp[p][i][j] += (sp[p][i - 1][j] + sp[p][i][j - 1] - sp[p][i - 1][j - 1]);
    for(int i = 1; i <= 49; i++)
        if((state.mask[0] & (1ll << i)) && (state.mask[1] & (1ll << i)))
            tokensInDanger -= (75 * inDanger(i));
    int positioning = 0;
    for(int i = 1; i <= 49; i++)
        if(state.mask[0] & (1ll << i))
            positioning += (std::min({(i / 7 - (i % 7 == 0) + 1) - 1, 7 - (i / 7 - (i % 7 == 0) + 1), (i % 7 == 0 ? 7 : i % 7) - 1, 7 - (i % 7 == 0 ? 7 : i % 7)})) * 15;
    return (tokenDifference + tokensInDanger);
}