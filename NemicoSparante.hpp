#ifndef NEMICOSPARANTE_HPP
#define NEMICOSPARANTE_HPP
#include "Nemico.hpp"
#include <ncurses.h>

// Forward declaration per velocizzare la compilazione
class Mappa;

class NemicoSparante : public Nemico {
protected:
    int dirProiettile;
    int frameProi;
    int xp;
    int yp;

public:
    NemicoSparante(int y, int x, Mappa* m);
    int movimento(int pY, int pX, int dirCorrente);
    void disegna();
    int getYp() const;
    int getXp() const;

};
#endif
