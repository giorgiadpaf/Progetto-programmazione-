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

public:
    Nemico(int y, int x, Map* m, int t);
    int movimento(int pY, int pX, int dirCorrente);
    void disegna();
    void controllaMorte(Bombe* pBombe);

    bool isVivo() const;
    virtual int getYp() const;
    virtual int getXp() const;
};
