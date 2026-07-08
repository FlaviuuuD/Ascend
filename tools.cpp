#include <iostream>
#include <random>
#include "tools.h"
unsigned long long randomValues[2][51][3];
int remainingTime;
const char toolsDX[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const char toolsDY[] = {-1, 0, 1, -1, 1, -1, 0, 1};
const double TIME_LIMIT = 0.98;
const unsigned long long maxULL = (((__int128_t)(1) << (64)) - 1);
int toolsDISTANCE(char& x, char& y)
{
    //distanta este egala cu maximul dintre distanta pe linie si distanta pe coloana.
    return std::max(abs((x / 7 - (x % 7 == 0) + 1) - (y / 7 - (y % 7 == 0) + 1)), abs((x % 7 == 0 ? 7 : (x % 7)) - (y % 7 == 0 ? 7 : (y % 7))));
}
std::chrono::time_point<std::chrono::steady_clock> start;
void getInitialTime()
{
    start = std::chrono::steady_clock::now();
}
double getTimeInSeconds()
{
    return std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
}
bool stillHaveTime()
{
    return (getTimeInSeconds() < TIME_LIMIT);
}
void getRandomValues()
{
    std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<unsigned long long> distrib(1, maxULL);
    for(int t = 0; t <= 1; t++)
        for(int i = 1; i <= 50; i++)
            for(int j = 0; j <= 2; j++)
                randomValues[t][i][j] = distrib(rnd);
}