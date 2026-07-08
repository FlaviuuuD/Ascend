#pragma once
#include "move.h"
struct board{
    unsigned long long mask[2] = {0, 0};
    //Prima masca contine 49 de biti (adica mask[0] si ne spune daca sunt sau nu ocupate pozitiile).
    //A doua masca contine inca 49 de biti (adica mask[1]) si ne spune cine ocupa pozitiile 
    //(informatie corecta doar daca in mask[0] pozitia este marcata ca fiind ocupata). 1 = suntem noi, 0 = este adversarul.
    //De asemenea, in prima masca, pe pozitia 50, ne vom tine ce jucator este la mutare (1 = suntem noi, 0 = este adversarul).
    unsigned long long key[2] = {0, 0};
    char numberOfTokens[2] = {0, 0};
    void readFromInput();
    void initializeKeys();
    void initializeNumberOfTokens();
    char getMovingPlayer();
    char checkValidMove(move& mv);
    void applyMove(move& mv);
    bool isTerminal();
};