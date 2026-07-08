#pragma once
#include <iostream>
#include <chrono>
extern unsigned long long randomValues[2][51][3];
extern double remainingTime;
const int INF = 1e8;
extern const double TIME_LIMIT;
extern char adjiacentMatrix[50][8];
extern char jumpAdjiacentMatrix[50][16];
int toolsDISTANCE(char& x, char& y);
void precalculateTools();
void getInitialTime();
double getTimeInSeconds();
bool stillHaveTime();
