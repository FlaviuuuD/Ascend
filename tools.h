#pragma once
#include <iostream>
#include <chrono>
unsigned long long randomValues[2][50][3];
const char toolsDX[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const char toolsDY[] = {-1, 0, 1, -1, 1, -1, 0, 1};
inline int toolsDISTANCE(char& x, char& y);
void getRandomValues();
void getInitialTime();
double getTimeInSeconds();
bool stillHaveTime();
