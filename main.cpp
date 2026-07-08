#include <iostream>
#include <chrono>
#include "board.h"
#include "move.h"
#include "alphabeta.h"
#include "tools.h"
board gameState;
move myMove;
int main()
{
    getInitialTime();
    precalculateTools();
    gameState.readFromInput();
    myMove = getMove(gameState);
    myMove.print();
    return 0;
}