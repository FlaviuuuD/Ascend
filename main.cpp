#include <iostream>
#include "board.h"
#include "move.h"
#include "alphabeta.h"
int main()
{
    board gameState;
    gameState.readFromInput();
    move myMove = getMove(gameState);
    myMove.print();
    return 0;
}