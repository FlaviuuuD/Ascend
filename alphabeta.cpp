#include "alphabeta.h"
#include "board.h"
#include "move.h"
#include "tools.h"
#include "evaluate.h"
#include "transpositionTable.h"
#include "moveGenerator.h"
#include <vector>
const int ROUND_CHECK = 1024;
int originalDepth;
bool outOfTime = 0;
int visitedNodes = 0;
board buff[15][4];
int alphaBeta(board& state, int depth, int alpha, int beta, char maximizingPlayer)
{
    visitedNodes++;
    if((!(visitedNodes & (ROUND_CHECK - 1))) && !((stillHaveTime())))
        {outOfTime = 1; return (-INF);}
    move firstMove;
    bool killerMove = 0;
    TTEntry auxEntry = getTTEntry(state);
    if(auxEntry.type != -100) //exista entry.
    {
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
    generateMoves(depth, state);
    if(killerMove)
        for(int ind = 0; ind < movesSize[depth]; ind++)
            if(moves[depth][ind].tokenPosition == firstMove.tokenPosition && moves[depth][ind].destination == firstMove.destination)
                {std::swap(moves[depth][0], moves[depth][ind]); break;}
                int originalAlpha = alpha, originalBeta = beta;
    if(movesSize[depth] == 0)
    {
        board original = state;
        int total = state.numberOfTokens[0] + state.numberOfTokens[1];
        state.numberOfTokens[1 - state.getMovingPlayer()] += 49 - total;
        int val = evaluate(state);
        state = original;
        return val;
    }
    int value;
    char TTEntryType = 0;
    int positionOfBestFoundMove = 0;
    int auxVariable;
    for(int ind = 0; ind < 4 && ind < movesSize[depth]; ind++)
    {
        buff[depth][ind] = state;
        buff[depth][ind].applyMove(moves[depth][ind]);
        __builtin_prefetch(&TT[buff[depth][ind].key[0] & (TTSize - 1)]);
    }
    if(maximizingPlayer)
    {
        value = -INF;
        for(int ind = 0; ind < (movesSize[depth]); ind++)
        {
            auxVariable = alphaBeta(buff[depth][ind % 4], depth - 1, alpha, beta, 0);
            if(outOfTime)
                {return -INF;}
            if(auxVariable > value)
            {
                value = auxVariable;
                positionOfBestFoundMove = ind;
            }
            if(value >= beta)
                {TTEntryType = 2; break;}
            alpha = std::max(alpha, value);
            if(ind + 4 < (movesSize[depth]))
            {
                buff[depth][ind % 4] = state;
                buff[depth][ind % 4].applyMove(moves[depth][ind + 4]);
                __builtin_prefetch(&TT[buff[depth][ind % 4].key[0] & (TTSize - 1)]);
            }
        }
        if(value <= originalAlpha)
            TTEntryType = 1;
    }
    else
    {
        value = INF;
        for(int ind = 0; ind < movesSize[depth]; ind++)
        {
            auxVariable = alphaBeta(buff[depth][ind % 4], depth - 1, alpha, beta, 1);
            if(outOfTime)
                {return -INF;}
            if(auxVariable < value)
            {
                value = auxVariable;
                positionOfBestFoundMove = ind;
            }
            if(value <= alpha)
                {TTEntryType = 1; break;}
            beta = std::min(beta, value);
            if(ind + 4 < (movesSize[depth]))
            {
                buff[depth][ind % 4] = state;
                buff[depth][ind % 4].applyMove(moves[depth][ind + 4]);
                __builtin_prefetch(&TT[buff[depth][ind % 4].key[0] & (TTSize - 1)]);
            }
        }
        if(value >= originalBeta)
            TTEntryType = 2;
    }
    if(outOfTime)
        {return -INF;}
    addTTEntry(state, moves[depth][positionOfBestFoundMove], value, depth, TTEntryType);
    return value;
}
move getMove(board& state)
{
    declareNullEntry();
    //folosim Iterative Deepening.
    int depth = 0;
    move lastMove;
    int win_loss;
    TTEntry axentry;
    int totalNodes = 0;
    while(stillHaveTime() && depth < 14)
    {
        ++depth;
        originalDepth = depth;
        visitedNodes = 0;
        alphaBeta(state, depth, -2 * INF, +2 * INF, 1);
        totalNodes += visitedNodes;
        if(stillHaveTime() && !outOfTime)
        {
            axentry = getTTEntry(state);
            lastMove = axentry.bestMove;
        }
    }
    std::cerr << "kibitz" << " " << depth << '\n';
    std::cerr << "kibitz" << " " << (int) (((1.0 * visitedNodes) / (remainingTime))) << " " << "Nodes / Second" << '\n';
    if(axentry.score >= INF)
        std::cerr << "kibitz" << " " << "Detected WIN" << '\n';
    if(axentry.score <= -INF)
        std::cerr << "kibitz" << " " << "Detected LOSS" << '\n';
    return lastMove;
}