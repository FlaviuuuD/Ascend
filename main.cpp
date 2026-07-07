#include <iostream>
#include <chrono>
#include "board.h"
#include "move.h"
#include "alphabeta.h"
#include "tools.h"
int main()
{
    getInitialTime();
    getRandomValues();
    board gameState;
    gameState.readFromInput();
    move myMove = getMove(gameState);
    myMove.print();
    return 0;
}