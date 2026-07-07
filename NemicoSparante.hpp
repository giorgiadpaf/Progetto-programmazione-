#pragma once
#include "Nemico.hpp"
#include <ncurses.h>

// Forward declaration per velocizzare la compilazione
class Map;

class NemicoSparante : public Nemico {
protected:
    int dirProiettile;
    int frameProi;
    int xp;
    int yp;
    int reloadTimer;
    int reloadTime;

public:
    NemicoSparante(int y, int x, Map* m);
    void movimento(int pY, int pX, Bombe* pBombe);
    void disegna();
    int getYp() const;
    int getXp() const;

};
