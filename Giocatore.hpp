#ifndef GIOCATORE_HPP
#define GIOCATORE_HPP
#include "Entita.hpp"
#include <ncurses.h>

class Nemico;
class Bombe; //MODIFICA: aggiunta la classe Bombe

class Giocatore : public Entita {
private:
    int vite;
    Bombe* pBombe; //MODIFICA: puntatore al gestore delle bombe
    int startY;
    int startX;
    int invulnerabile;
    int punteggio;

public:
    //MODIFICA: aggiunto pBombe ai parametri del costruttore
    Giocatore(int y, int x, Mappa* mappa, Bombe* pBombe);
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
