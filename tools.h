#pragma once
#include <iostream>
#include <chrono>
extern unsigned long long randomValues[2][50][3];
extern const char toolsDX[8];
extern const char toolsDY[8];
int toolsDISTANCE(char& x, char& y);
void getRandomValues();
void getInitialTime();
double getTimeInSeconds();
bool stillHaveTime();
