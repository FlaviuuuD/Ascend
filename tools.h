char toolsDX[] = {-1, -1, -1, 0, 0, 1, 1, 1};
char toolsDY[] = {-1, 0, 1, -1, 1, -1, 0, 1};
inline int toolsDISTANCE(char& x, char& y)
{
    //distanta este egala cu maximul dintre distanta pe linie si distanta pe coloana.
    return std::max(abs((x / 7 - (x % 7 == 0) + 1) - (y / 7 - (y % 7 == 0) + 1)), abs((x % 7 == 0 ? 7 : (x % 7)) - (y % 7 == 0 ? 7 : (y % 7))));
}