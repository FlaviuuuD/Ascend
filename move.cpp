#include "move.h"
#include "tools.h"
#include <iostream>
void move::init(char mv, char tk, char dt, char play, char scor) {moveType = mv; tokenPosition = tk; destination = dt; player = play; score = scor;}
void move::print()
{
    if(moveType == 0)
        std::cout << (char) ('a' + (destination % 7 == 0 ? 7 : destination % 7) - 1) << (destination / 7 - (destination % 7 == 0) + 1);
    else
    {
        std::cout << (char) ('a' + (tokenPosition % 7 == 0 ? 7 : tokenPosition % 7) - 1) << (tokenPosition / 7 - (tokenPosition % 7 == 0) + 1);
        std::cout<<"-";
        std::cout << (char) ('a' + (destination % 7 == 0 ? 7 : destination % 7) - 1) << (destination / 7 - (destination % 7 == 0) + 1);
    }
}
