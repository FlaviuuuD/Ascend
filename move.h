#pragma once
struct move{
    unsigned char moveType; //0 = clonare, 1 = salt.
    unsigned char tokenPosition; //pozitia tokenului ce va fi mutat / clonat (de la 1 la 49)
    unsigned char destination; //pozitia destinatiei (la care se face clonarea sau la care se sare).
    unsigned char player; //1 = eu, 0 = adversarul.
    unsigned char score;
public:
    void init(unsigned char mv, unsigned char tk, unsigned char dt, unsigned char play, unsigned char scor);
    void print();
};