#include <iostream>
#include <random>
#include "tools.h"
unsigned long long randomValues[2][51][3];
double remainingTime;
const double TIME_LIMIT = 1.78;
const char toolsDX[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const char toolsDY[] = {-1, 0, 1, -1, 1, -1, 0, 1};
const char toolsJumpDX[] = {-2, -2, -2, -2, -2, -1, -1, 0, 0, 1, 1, 2, 2, 2, 2, 2};
const char toolsJumpDY[] = {-2, -1, 0, 1, 2, -2, 2, -2, 2, -2, 2, -2, -1, 0, 1, 2};
char adjiacentMatrix[50][8];
char jumpAdjiacentMatrix[50][16];
const unsigned long long maxULL = (((__int128_t)(1) << (64)) - 1);
double originalRemainingTime;
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
    return (getTimeInSeconds() < remainingTime);
}
void precalculateTools()
{
    std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<unsigned long long> distrib(1, maxULL);
    for(int t = 0; t <= 1; t++)
        for(int i = 1; i <= 50; i++)
            for(int j = 0; j <= 2; j++)
                randomValues[t][i][j] = distrib(rnd);
    int xi, yi;
    int newx, newy;
    for(int i = 1; i <= 49; i++)
    {
        xi = (i / 7 - (i % 7 == 0) + 1); yi = (i % 7 == 0 ? 7 : i % 7);
        for(int j = 0; j < 8; j++)
        {
            newx = xi + toolsDX[j]; newy = yi + toolsDY[j];
            if(newx >= 1 && newx <= 7 && newy >= 1 && newy <= 7)
                adjiacentMatrix[i][j] = ((newx - 1) * 7 + newy);
        }
    }
    for(int i = 1; i <= 49; i++)
    {
        xi = (i / 7 - (i % 7 == 0) + 1); yi = (i % 7 == 0 ? 7 : i % 7);
        for(int j = 0; j < 16; j++)
        {
            newx = xi + toolsJumpDX[j]; newy = yi + toolsJumpDY[j];
            if(newx >= 1 && newx <= 7 && newy >= 1 && newy <= 7)
                jumpAdjiacentMatrix[i][j] = ((newx - 1) * 7 + newy);
        }
    }
}
bool stillHaveHardTime()
{
    return (getTimeInSeconds() < originalRemainingTime);
}