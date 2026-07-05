#pragma once
#include "Entita.hpp"
#include <ncurses.h>

class Map;
class Bombe;

class Nemico : public Entita {
protected:
    bool vivo;
    int tipo;
    int frameDelay;
    int frameCounter;
    int dirAttuale;

public:
    Nemico(int y, int x, Map* m, int t);
    void movimento(int pY, int pX, Bombe* pBombe);
    void disegna();
    void controllaMorte(Bombe* pBombe);

    bool isVivo() const;
    virtual int getYp() const;
    virtual int getXp() const;
};
