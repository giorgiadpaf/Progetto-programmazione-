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

public:
    NemicoSparante(int y, int x, Map* m);
    int movimento(int pY, int pX, int dirCorrente);
    void disegna();
    int getYp() const;
    int getXp() const;

};
