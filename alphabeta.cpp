#include "alphabeta.h"
#include "board.h"
#include "move.h"
#include "tools.h"
#include "evaluate.h"
#include "transpositionTable.h"
#include "moveGenerator.h"
#include <vector>
const int depthLimit = 6;
int originalDepth;
int alphaBeta(board& state, int depth, int alpha, int beta, char maximizingPlayer)
{
    if(!((stillHaveTime())))
        {return -INF;}
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
        return evaluate(state, originalDepth - depth);
    generateMoves(depth, state);
    if(killerMove)
        for(int ind = 0; ind < (int) movesSize[depth]; ind++)
            if(moves[depth][ind].tokenPosition == firstMove.tokenPosition && moves[depth][ind].destination == firstMove.destination)
                {std::swap(moves[depth][0], moves[depth][ind]); break;}
    board original = state;
    int originalAlpha = alpha, originalBeta = beta;
    if(movesSize[depth] == 0)
    {
        int total = state.numberOfTokens[0] + state.numberOfTokens[1];
        state.numberOfTokens[1 - state.getMovingPlayer()] += 49 - total;
        int val = evaluate(state, originalDepth - depth);
        state = original;
        return val;
    }
    int value;
    char TTEntryType = 0;
    int positionOfBestFoundMove = 0;
    int auxVariable;
    if(maximizingPlayer)
    {
        value = -INF;
        for(int ind = 0; ind < (int) (movesSize[depth]); ind++)
        {
            state.applyMove(moves[depth][ind]);
            auxVariable = alphaBeta(state, depth - 1, alpha, beta, 0);
            state = original;
            if(!((stillHaveTime())))
                {return -INF;}
            if(auxVariable > value)
            {
                value = auxVariable;
                positionOfBestFoundMove = ind;
            }
            if(value >= beta)
                {TTEntryType = 2; break;}
            alpha = std::max(alpha, value);
        }
        if(value <= originalAlpha)
            TTEntryType = 1;
    }
    else
    {
        value = INF;
        for(int ind = 0; ind < (int) movesSize[depth]; ind++)
        {
            state.applyMove(moves[depth][ind]);
            auxVariable = alphaBeta(state, depth - 1, alpha, beta, 1);
            state = original;
            if(!(stillHaveTime()))
                {return -INF;}
            if(auxVariable < value)
            {
                value = auxVariable;
                positionOfBestFoundMove = ind;
            }
            if(value <= alpha)
                {TTEntryType = 1; break;}
            beta = std::min(beta, value);
        }
        if(value >= originalBeta)
            TTEntryType = 2;
    }
    if(!(stillHaveTime()))
        {return -INF;}
    addTTEntry(state, moves[depth][positionOfBestFoundMove], value, depth, TTEntryType);
    return value;
}
move getMove(board& state)
{
    //folosim Iterative Deepening.
    int depth = 0;
    move lastMove;
    int win_loss;
    TTEntry axentry;
    while(stillHaveTime() && depth < 14)
    {
        ++depth;
        originalDepth = depth;
        alphaBeta(state, depth, -INF, +INF, 1);
        if(stillHaveTime())
        {
            axentry = getTTEntry(state.key[0]);
            lastMove = axentry.bestMove;
        }
    }
    std::cerr << "kibitz" << " " << depth << '\n';
    if(axentry.score >= INF)
        std::cerr << "kibitz" << " " << "Detected WIN" << '\n';
    if(axentry.score <= -INF)
        std::cerr << "kibitz" << " " << "Detected LOSS" << '\n';
    return lastMove;
}