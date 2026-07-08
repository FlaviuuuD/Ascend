#include "alphabeta.h"
#include "board.h"
#include "move.h"
#include "tools.h"
#include "evaluate.h"
#include "transpositionTable.h"
#include "moveGenerator.h"
#include <vector>
bool outOfTime = 0;
const int depthLimit = 7;
int alphaBeta(board& state, int depth, int alpha, int beta, bool maximizingPlayer)
{
    if(!((stillHaveTime() && !outOfTime) || (outOfTime && stillHaveHardTime() && depth < depthLimit)))
        {outOfTime = 1; return -INF;}
    move firstMove;
    bool killerMove = 0;
    if(doesEntryExist(state.key[0], state.key[1]))
    {
        TTEntry auxEntry = getTTEntry(state.key[0]);
        if(auxEntry.depth >= depth)
        {
            if(auxEntry.type == 0)
                return auxEntry.score;
            if(auxEntry.type == 1 && auxEntry.score <= alpha)
                return auxEntry.score;
            if(auxEntry.type == 2 && auxEntry.score >= beta)
                return auxEntry.score;
        }
        killerMove = 1;
        firstMove = auxEntry.bestMove;
    }
    if(depth == 0 || state.isTerminal())
        return evaluate(state);
    std::vector<move> generatedMoves = generateMoves(state);
    if(killerMove)
    {
        generatedMoves.push_back(firstMove);
        std::swap(generatedMoves.back(), generatedMoves[0]);
    }
    if(!((stillHaveTime() && !outOfTime) || (outOfTime && stillHaveHardTime() && depth < depthLimit)))
        {outOfTime = 1; return -INF;}
    if(generatedMoves.empty())
        return evaluate(state);
    int value;
    board original = state;
    char TTEntryType = 0;
    int positionOfBestFoundMove = 0;
    int auxVariable;
    if(maximizingPlayer)
    {
        value = -INF;
        for(int ind = 0; ind < (int) (generatedMoves.size()); ind++)
        {
            state.applyMove(generatedMoves[ind]);
            auxVariable = alphaBeta(state, depth - 1, alpha, beta, 0);
            state = original;
            if(!((stillHaveTime() && !outOfTime) || (outOfTime && stillHaveHardTime() && depth < depthLimit)))
                {outOfTime = 1; return -INF;}
            if(auxVariable > value)
            {
                value = auxVariable;
                positionOfBestFoundMove = ind;
            }
            if(value >= beta)
                {TTEntryType = 2; break;}
            alpha = std::max(alpha, value);
        }
    }
    else
    {
        value = INF;
        for(int ind = 0; ind < (int) (generatedMoves.size()); ind++)
        {
            state.applyMove(generatedMoves[ind]);
            auxVariable = alphaBeta(state, depth - 1, alpha, beta, 1);
            state = original;
            if(!((stillHaveTime() && !outOfTime) || (outOfTime && stillHaveHardTime() && depth < depthLimit)))
                {outOfTime = 1; return -INF;}
            if(auxVariable < value)
            {
                value = auxVariable;
                positionOfBestFoundMove = ind;
            }
            if(value <= alpha)
                {TTEntryType = 1; break;}
            beta = std::min(beta, value);
        }
    }
    if(!((stillHaveTime() && !outOfTime) || (outOfTime && stillHaveHardTime() && depth < depthLimit)))
        {outOfTime = 1; return -INF;}
    addTTEntry(state, generatedMoves[positionOfBestFoundMove], value, depth, TTEntryType);
    return value;
}
move getMove(board& state)
{
    //folosim Iterative Deepening.
    int depth = 0;
    move lastMove;
    while((stillHaveTime() && !outOfTime) || (outOfTime && stillHaveHardTime() && depth < depthLimit))
    {
        ++depth;
        alphaBeta(state, depth, -INF, +INF, 1);
        if(stillHaveTime() && !outOfTime)
            lastMove = getTTEntry(state.key[0]).bestMove;
    }
    std::cerr << "kibitz" << " " << depth << '\n';
    return lastMove;
}