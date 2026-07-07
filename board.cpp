#include "board.h"
#include <iostream>
using namespace std;
void board::readFromInput()
{
    int token;
    for(int i = 1; i <= 7; i++)
    {
        for(int j = 1; j <= 7; j++)
        {
            cin >> token;
            mask |= ((1 << ((i - 1) * 7 + j)) & token);
        }
    }
}
int board::getBoard()
{
    return mask;
}
