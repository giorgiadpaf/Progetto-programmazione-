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

public:
    Giocatore(int y, int x, Mappa* mappa);
    // Funzione per cambiare le coordinate in base al tasto premuto
    void muovi(int input);
    void controllaDanni();
    void decrementaInvulnerabilita();
    void controllaDanni(Nemico* listaNemici[], int numeroNemici);
    void disegna(); // Questa mancava!
    int getVite() const;
};
#endif
