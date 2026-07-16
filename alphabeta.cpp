#include "alphabeta.h"
#include "board.h"
#include "move.h"
#include "tools.h"
#include "evaluate.h"
#include "transpositionTable.h"
#include "moveGenerator.h"
#include <vector>
#include <algorithm>
const int ROUND_CHECK = 1024;
int originalDepth;
bool outOfTime = 0;
int visitedNodes = 0;
board buff[51][4];
unsigned char killerMoves[51][2][2];
int order[51][500];
int alphaBeta(board& state, int depth, int alpha, int beta, char maximizingPlayer)
{
    visitedNodes++;
    if((!(visitedNodes & (ROUND_CHECK - 1))) && !((stillHaveTime())))
        {outOfTime = 1; return (-INF);}
    unsigned char firstMove;
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
    if(depth <= 0 || state.isTerminal())
        return evaluate(state);
    if(depth >= 5 && !outOfTime && beta > alpha + 1 && (state.numberOfTokens[0] + state.numberOfTokens[1] < 40))
    {
        board nullState = state;
        nullState.changeActivePlayer();
        int nullScore = alphaBeta(nullState, depth - 1 - 2, alpha, beta, maximizingPlayer ^ 1);
        if(maximizingPlayer && nullScore >= beta)
            return nullScore;
        if(!maximizingPlayer && nullScore <= alpha)
            return nullScore;
    }
    generateMoves(depth, state);
    if(killerMove)
        moves[depth][firstMove].score = 12;
    for(int i = 0; i < movesSize[depth]; i++)
    {
        if(moves[depth][i].score == 12) continue;
        if(moves[depth][i].tokenPosition == killerMoves[depth][0][0] && moves[depth][i].destination == killerMoves[depth][0][1])
            moves[depth][i].score = 11;
        else if(moves[depth][i].tokenPosition == killerMoves[depth][1][0] && moves[depth][i].destination == killerMoves[depth][1][1])
            moves[depth][i].score = 10;
    }
    int cnt[14] = {0}, already[14] = {0};
    for(int i = 0; i < movesSize[depth]; i++)
        cnt[moves[depth][i].score]++;
    for(int i = 12; i >= 0; i--)
        cnt[i] += cnt[i + 1];
    for(int i = 0; i < movesSize[depth]; i++)
        order[depth][cnt[moves[depth][i].score + 1] + (already[moves[depth][i].score]++)] = i;
    int originalAlpha = alpha, originalBeta = beta;
    if(movesSize[depth] == 0)
    {
        board original = state;
        int total = state.numberOfTokens[0] + state.numberOfTokens[1];
        state.numberOfTokens[1 - ((state.mask[0] >> 50) & 1)] += 49 - total;
        int val = evaluate(state);
        state = original;
        return val;
    }
    int value;
    char TTEntryType = 0;
    unsigned char positionOfBestFoundMove = 0;
    int auxVariable;
    for(int ind = 0; ind < 4 && ind < movesSize[depth]; ind++)
    {
        buff[depth][ind] = state;
        buff[depth][ind].applyMove(moves[depth][order[depth][ind]]);
        __builtin_prefetch(&TT[buff[depth][ind].key[0] & (TTSize - 1)]);
    }
    if(maximizingPlayer)
    {
        value = -INF;
        for(int ind = 0; ind < (movesSize[depth]); ind++)
        {
            if(ind == 0)
                auxVariable = alphaBeta(buff[depth][ind % 4], depth - 1, alpha, beta, 0);
            else
            {
                auxVariable = alphaBeta(buff[depth][ind % 4], depth - 1, alpha, alpha + 1, 0);
                if(auxVariable > alpha && auxVariable < beta)
                    auxVariable = alphaBeta(buff[depth][ind % 4], depth - 1, alpha, beta, 0);
            }
            if(outOfTime)
                {return -INF;}
            if(auxVariable > value)
            {
                value = auxVariable;
                positionOfBestFoundMove = order[depth][ind];
            }
            if(value >= beta)
            {
                TTEntryType = 2; 
                if(moves[depth][order[depth][ind]].tokenPosition != killerMoves[depth][0][0] || 
                    moves[depth][order[depth][ind]].destination != killerMoves[depth][0][1])
                {
                    killerMoves[depth][1][0] = killerMoves[depth][0][0];
                    killerMoves[depth][1][1] = killerMoves[depth][0][1];
                    killerMoves[depth][0][0] = moves[depth][order[depth][ind]].tokenPosition;
                    killerMoves[depth][0][1] = moves[depth][order[depth][ind]].destination;
                }                
                break;
            }
            alpha = std::max(alpha, value);
            if(ind + 4 < (movesSize[depth]))
            {
                buff[depth][ind % 4] = state;
                buff[depth][ind % 4].applyMove(moves[depth][order[depth][ind + 4]]);
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
            if(ind == 0)
                auxVariable = alphaBeta(buff[depth][ind % 4], depth - 1, alpha, beta, 1);
            else
            {
                auxVariable = alphaBeta(buff[depth][ind % 4], depth - 1, beta - 1, beta, 1);
                if(auxVariable > alpha && auxVariable < beta)
                    auxVariable = alphaBeta(buff[depth][ind % 4], depth - 1, alpha, beta, 1);
            }
            if(outOfTime)
                {return -INF;}
            if(auxVariable < value)
            {
                value = auxVariable;
                positionOfBestFoundMove = order[depth][ind];
            }
            if(value <= alpha)
            {
                TTEntryType = 1;
                if(moves[depth][order[depth][ind]].tokenPosition != killerMoves[depth][0][0] || 
                    moves[depth][order[depth][ind]].destination != killerMoves[depth][0][1])
                {
                    killerMoves[depth][1][0] = killerMoves[depth][0][0];
                    killerMoves[depth][1][1] = killerMoves[depth][0][1];
                    killerMoves[depth][0][0] = moves[depth][order[depth][ind]].tokenPosition;
                    killerMoves[depth][0][1] = moves[depth][order[depth][ind]].destination;
                }  
                break;
            }
            beta = std::min(beta, value);
            if(ind + 4 < (movesSize[depth]))
            {
                buff[depth][ind % 4] = state;
                buff[depth][ind % 4].applyMove(moves[depth][order[depth][ind + 4]]);
                __builtin_prefetch(&TT[buff[depth][ind % 4].key[0] & (TTSize - 1)]);
            }
        }
        if(value >= originalBeta)
            TTEntryType = 2;
    }
    if(outOfTime)
        {return -INF;}
    addTTEntry(state, positionOfBestFoundMove, value, depth, TTEntryType);
    return value;
}
move getMove(board& state)
{
    declareNullEntry();
    //folosim Iterative Deepening.
    int depth = 0;
    move lastMove;
    TTEntry axentry;
    int totalNodes = 0;
    while(stillHaveTime() && depth < 50)
    {
        ++depth;
        originalDepth = depth;
        visitedNodes = 0;
        alphaBeta(state, depth, -2 * INF, +2 * INF, 1);
        totalNodes += visitedNodes;
        if(stillHaveTime() && !outOfTime)
        {
            axentry = getTTEntry(state);
            lastMove = moves[depth][axentry.bestMove];
        }
    }
    std::cerr << "kibitz" << " " << depth << '\n';
    std::cerr << "kibitz" << " " << (int) (((1.0 * totalNodes) / (remainingTime))) << " " << "Nodes / Second" << '\n';
    if(axentry.score >= INF)
        std::cerr << "kibitz" << " " << "Detected WIN" << '\n';
    if(axentry.score <= -INF)
        std::cerr << "kibitz" << " " << "Detected LOSS" << '\n';
    return lastMove;
}