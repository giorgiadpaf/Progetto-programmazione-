#pragma once
#include "Entita.hpp"
#include <ncurses.h>

class Map;
class Nemico;
class Bombe;
struct enemylist;

class Giocatore : public Entita {
private:
    int vite;
    Bombe* pBombe;
    int startY;
    int startX;
    int invulnerabile;
    int punteggio;

public:
    Giocatore(int y, int x, Map* mappa, Bombe* pBombe);
    void muovi(int input);
    void decrementaInvulnerabilita();
    void controllaDanni(enemylist* listanemici);
    void disegna();
    int getVite() const;
    int getPunteggio() const;
    int aggiungiPunteggio(int p);
    void cambiaLivello(Map* nuovaMappa, int nuovoY, int nuovoX); //aggiunto per non dover instanziare di nuovo
                                                                 //il giovatore quando si passa al nuovo livello
};
