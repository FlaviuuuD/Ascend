#pragma once
struct move{
    char moveType; //0 = clonare, 1 = salt.
    char tokenPosition; //pozitia tokenului ce va fi mutat / clonat (de la 1 la 49)
    char destination; //pozitia destinatiei (la care se face clonarea sau la care se sare).
    char player; //1 = eu, 0 = adversarul.
public:
    void init(char mv, char tk, char dt, char play);
    void print();
};