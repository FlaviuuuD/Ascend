#include "evaluate.h"
#include "board.h"
int evaluate(board& state)
{
    return (state.numberOfTokens[1] - state.numberOfTokens[0]);
}