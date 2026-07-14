#include "board.h"
#include "move.h"
#include "tools.h"
#include <iostream>
const int positionMatrix[50] = {0,
    30, 15, 12, 10, 12, 15, 30,
    15, 8, 5, 5, 5, 8, 15,
    12, 2, 5, 5, 5, 2, 12,
    10, 2, 5, 4, 5, 2, 10,
    12, 2, 5, 5, 5, 2, 12,
    15, 8, 2, 2, 2, 2, 15,
    30, 15, 12, 10, 12, 15, 30
};
void board::initializeKeys()
{
    for(int i = 1; i <= 49; i++)
    {
        if(!(mask[0] & (1ll << i)))
        {
            key[0] ^= randomValues[0][i][0];
            key[1] ^= randomValues[1][i][0];
        }
        else
        {
            if((mask[1] & (1ll << i)))
            {
                key[0] ^= randomValues[0][i][1];
                key[1] ^= randomValues[1][i][1];
            }
            else
            {
                key[0] ^= randomValues[0][i][2];
                key[1] ^= randomValues[1][i][2];
            }
        }
    }
    key[0] ^= randomValues[0][50][1];
    key[1] ^= randomValues[1][50][1];
}
void board::initializeTableScores()
{
    for(int i = 1; i <= 49; i++)
        if(mask[0] & (1ll << i))
            numberOfTokens[(mask[1] & (1ll << i)) != 0]++;
    for(int i = 1; i <= 49; i++)
        if(mask[0] & (1ll << i))
            positionScore += positionMatrix[i] * ((mask[1] & (1ll << i)) ? 1 : -1);
}
void board::readFromInput()
{
    char token;
    char player; std::cin >> player;
    player -= '0';
    int emptyCells = 0;
    for(int i = 1; i <= 7; i++)
    {
        for(int j = 1; j <= 7; j++)
        {
            std::cin >> token;
            if(token == '.') {emptyCells++;} //neocupat, nu facem nimic.
            else
            {
                //pozitia este ocupata.
                mask[0] |= (1ll << ((i - 1) * 7 + j));
                if((token == 'x' && player == 0) || (token == 'o' && player == 1))
                    mask[1] |= (1ll << ((i - 1) * 7 + j));
            }
        }
    }
    //noi suntem automat la mutare din moment ce am citit tabla de la intrare.
    mask[0] |= (1ll << 50);
    int milisec[2];
    std::cin >> milisec[0]>> milisec[1];
    remainingTime = (milisec[player] / 1000.0);
    double estimatedRoundCount = 1.4 * (emptyCells);
    remainingTime = remainingTime / estimatedRoundCount; 
    initializeTableScores();
    initializeKeys();
}
char board::getMovingPlayer()
{
    //returnam 1 daca mutam noi, 0 daca inamicul.
    return ((mask[0] >> 50) & 1);
}
unsigned long long capturedMask, axlog;
void board::applyMove(move& mv)
{
    if(mv.moveType == 0)
    {
        //clonare.
        key[0] ^= randomValues[0][mv.destination][0];
        key[1] ^= randomValues[1][mv.destination][0];
        if(mv.player == 1)
        {
            positionScore += (positionMatrix[mv.destination]);
            mask[0] |= (1ll << mv.destination);
            mask[1] |= (1ll << mv.destination);
            key[0] ^= randomValues[0][mv.destination][1];
            key[1] ^= randomValues[1][mv.destination][1];
        }
        else
        {
            positionScore -= (positionMatrix[mv.destination]);
            mask[0] |= (1ll << mv.destination);
            key[0] ^= randomValues[0][mv.destination][2];
            key[1] ^= randomValues[1][mv.destination][2];
            //la destinatie oricum nu era niciun jeton deci by default la destinatie in mask[1] vom avea 0, dar ne vom asigura totusi.
            if(mask[1] & (1ll << mv.destination))
                mask[1] ^= (1ll << mv.destination);
        }
        numberOfTokens[mv.player]++;
    }
    else
    {
        //salt.
        mask[0] ^= (1ll << mv.tokenPosition);
        key[0] ^= randomValues[0][mv.tokenPosition][(1 - mv.player) + 1];
        key[1] ^= randomValues[1][mv.tokenPosition][(1 - mv.player) + 1];
        key[0] ^= randomValues[0][mv.tokenPosition][0];
        key[1] ^= randomValues[1][mv.tokenPosition][0];
        key[0] ^= randomValues[0][mv.destination][0];
        key[1] ^= randomValues[1][mv.destination][0];
        mask[0] |= (1ll << mv.destination);
        if(mv.player == 1)
        {
            positionScore -= (positionMatrix[mv.tokenPosition]);
            positionScore += (positionMatrix[mv.destination]);
            mask[1] ^= (1ll << mv.tokenPosition);
            mask[1] |= (1ll << mv.destination);
            key[0] ^= randomValues[0][mv.destination][1];
            key[1] ^= randomValues[1][mv.destination][1];
        }
        else
        {
            positionScore += (positionMatrix[mv.tokenPosition]);
            positionScore -= (positionMatrix[mv.destination]);
            key[0] ^= randomValues[0][mv.destination][2];
            key[1] ^= randomValues[1][mv.destination][2];
            if(mask[1] & (1ll << mv.destination))
                mask[1] ^= (1ll << mv.destination);
        }
    }
    capturedMask = (adjiacentMask[mv.destination] & mask[0] & (mv.player == 1 ? (~mask[1]) : (mask[1]))); 
    for(; capturedMask >= 1; capturedMask -= (capturedMask & (-capturedMask)))
    {
        axlog =  (63 - __builtin_clzll(capturedMask&(-capturedMask)));
        mask[1] ^= (1ll << axlog);
        positionScore += (mv.player == 1 ? 2 : -2) * positionMatrix[axlog];
        numberOfTokens[mv.player]++; 
        numberOfTokens[mv.player ^ 1]--;
        key[0] ^= randomValues[0][axlog][mv.player + 1];
        key[1] ^= randomValues[1][axlog][mv.player + 1];
        key[0] ^= randomValues[0][axlog][(1 - mv.player) + 1];
        key[1] ^= randomValues[1][axlog][(1 - mv.player) + 1];
    }
    //schimbam si jucatorul la mutare.
    key[0] ^= randomValues[0][50][0];
    key[0] ^= randomValues[0][50][1];
    key[1] ^= randomValues[1][50][0];
    key[1] ^= randomValues[1][50][1];
    mask[0] ^= (1ll << 50);
}
void board::changeActivePlayer()
{
    key[0] ^= randomValues[0][50][0];
    key[0] ^= randomValues[0][50][1];
    key[1] ^= randomValues[1][50][0];
    key[1] ^= randomValues[1][50][1];
    mask[0] ^= (1ll << 50);
}
bool board::isTerminal()
{
    return ((numberOfTokens[0] + numberOfTokens[1] == 49) || (numberOfTokens[0] == 0) || (numberOfTokens[1] == 0));
}