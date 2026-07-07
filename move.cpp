#include "move.h"
#include <iostream>
void move::init(char mv, char tk, char dt) {moveType = mv; tokenPosition = tk; destination = dt;}
void move::print()
{
    std::cout << moveType << " " << tokenPosition << " " << destination;
}
