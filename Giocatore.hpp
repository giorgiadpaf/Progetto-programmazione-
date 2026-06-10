#ifndef GIOCATORE_HPP
#define GIOCATORE_HPP
#include "Entita.hpp"
#include <ncurses.h>

class Nemico;

class Giocatore : public Entita {
private:
    int vite;
    //Bombe* pbombe;
    int startY;
    int startX;
    int invulnerabile;
    int punteggio;

public:
    Giocatore(int y, int x, Mappa* mappa);
    // Funzione per cambiare le coordinate in base al tasto premuto
    void muovi(int input);
    void decrementaInvulnerabilita();
    void controllaDanni(Nemico* listaNemici[], int numeroNemici);
    void disegna();
    int getVite() const;
    int getPunteggio() const;
    int aggiungiPunteggio(int p);
};
#endif
