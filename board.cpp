#include "board.h"
#include "move.h"
#include "tools.h"
#include <iostream>
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
void board::initializeNumberOfTokens()
{
    for(int i = 1; i <= 49; i++)
        if(mask[0] & (1ll << i))
            numberOfTokens[(mask[1] & (1ll << i)) != 0]++;
}
void board::readFromInput()
{
    char token;
    char player; std::cin >> player;
    player -= '0';
    for(int i = 1; i <= 7; i++)
    {
        for(int j = 1; j <= 7; j++)
        {
            std::cin >> token;
            if(token == '.') {} //neocupat, nu facem nimic.
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
    remainingTime = (milisec[player] / 100.0);
    originalRemainingTime = 0.5 * remainingTime;
    remainingTime = std::min(0.5 * remainingTime, TIME_LIMIT);
    initializeNumberOfTokens();
    initializeKeys();
}
char board::getMovingPlayer()
{
    //returnam 1 daca mutam noi, 0 daca inamicul.
    return ((mask[0] >> 50) & 1);
}
void board::applyMove(move& mv)
{
    if(mv.moveType == 0)
    {
        //clonare.
        key[0] ^= randomValues[0][mv.destination][0];
        key[1] ^= randomValues[1][mv.destination][0];
        if(mv.player == 1)
        {
            mask[0] |= (1ll << mv.destination);
            mask[1] |= (1ll << mv.destination);
            key[0] ^= randomValues[0][mv.destination][1];
            key[1] ^= randomValues[1][mv.destination][1];
        }
        else
        {
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
            mask[1] |= (1ll << mv.destination);
            key[0] ^= randomValues[0][mv.destination][1];
            key[1] ^= randomValues[1][mv.destination][1];
        }
        else
        {
            key[0] ^= randomValues[0][mv.destination][2];
            key[1] ^= randomValues[1][mv.destination][2];
            if(mask[1] & (1ll << mv.destination))
                mask[1] ^= (1ll << mv.destination);
        }
    }
    char lin = (mv.destination / 7 - (mv.destination % 7 == 0) + 1);
    char col = (mv.destination % 7 == 0 ? 7 : mv.destination % 7);
    for(int k = 0; k < 8; k++)
    {
        if(adjiacentMatrix[mv.destination][k] >= 1 && adjiacentMatrix[mv.destination][k] <= 49 && 
            (mask[0] & (1ll << adjiacentMatrix[mv.destination][k])) && (((mask[1] & (1ll << adjiacentMatrix[mv.destination][k])) != 0) != mv.player))
                {
                    mask[1] ^= (1ll << adjiacentMatrix[mv.destination][k]); 
                    numberOfTokens[mv.player]++; 
                    numberOfTokens[mv.player ^ 1]--;
                    key[0] ^= randomValues[0][adjiacentMatrix[mv.destination][k]][mv.player + 1];
                    key[1] ^= randomValues[1][adjiacentMatrix[mv.destination][k]][mv.player + 1];
                    key[0] ^= randomValues[0][adjiacentMatrix[mv.destination][k]][(1 - mv.player) + 1];
                    key[1] ^= randomValues[1][adjiacentMatrix[mv.destination][k]][(1 - mv.player) + 1];
                }
    }
    //schimbam si jucatorul la mutare.
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