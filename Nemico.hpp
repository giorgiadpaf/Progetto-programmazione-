#ifndef NEMICO_HPP
#define NEMICO_HPP
#include "Entita.hpp"
#include <ncurses.h>

class Nemico : public Entita {
protected:
    bool vivo; // 1 se è in gioco, 0 se è stato colpito
    int tipo; // 1 = Casuale, 2 = Inseguitore (o veloce)
    int frameDelay; // Per gestire la velocità
    int frameCounter;

public:
    Nemico(int y, int x, Mappa* m, int t);
    int movimento(int pY, int pX, int dirCorrente);
    void disegna();
    void controllaMorte(); 
    bool isVivo() const;
};
#endif
