#pragma once
#include <iostream>
#include <chrono>
extern unsigned long long randomValues[2][51][3];
extern double remainingTime;
const int INF = 1e8;
extern const double TIME_LIMIT;
extern const char toolsDX[8];
extern const char toolsDY[8];
int toolsDISTANCE(char& x, char& y);
void getRandomValues();
void getInitialTime();
double getTimeInSeconds();
bool stillHaveTime();
