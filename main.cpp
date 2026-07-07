#include <iostream>
#include "board.h"
int main()
{
    board gameState;
    gameState.readFromInput();
    move myMove = alphaBeta.getMove();
    myMove.print();
    return 0;
}