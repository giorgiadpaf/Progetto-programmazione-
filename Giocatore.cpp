#include "Giocatore.hpp"
#include "Map.hpp"
#include "Bombe.hpp"
#include "Nemico.hpp"
Giocatore::Giocatore(int y, int x, Map* mappa, Bombe* pBombe) : Entita(y, x, mappa, 'A') {
    this->pBombe = pBombe;
    this->vite = 3;
    this->startY = y;
    this->startX = x;
    this->invulnerabile = 0;
    this->punteggio = 0;
}

void Giocatore::cambiaLivello(Map* nuovaMappa, int nuovoY, int nuovoX) {
    punmappa = nuovaMappa; // Aggiorna la mappa del giocatore
    y = nuovoY;            // Imposta la nuova posizione Y
    x = nuovoX;            // Imposta la nuova posizione X
    startY = nuovoY;       // Aggiorna lo spawn di sicurezza in caso di danno
    startX = nuovoX;
}

void Giocatore::muovi(int input){
    int newx = x;
    int newy = y;
    if (input == 'a' || input == KEY_LEFT) newx--;
    else if (input == 'w' || input == KEY_UP) newy--;
    else if (input == 'd' || input == KEY_RIGHT) newx++;
    else if (input == 's' || input == KEY_DOWN) newy++;

    if(punmappa->isempty(newy, newx) && !pBombe->cEunaBomba(newy, newx)){
        y=newy;
        x=newx;
    }

    if (input == ' ') {
        pBombe->aggiungiBomba(y, x);
    }
}

//adattato la funzione alla nuova implementazione con liste dei nemici
void Giocatore::controllaDanni(enemylist* listaNemici) {
    if (invulnerabile > 0) return;

    if(pBombe->colpitaDaEsplosione(y, x)){
        vite--;
        y = startY;
        x = startX;
        invulnerabile = 20;
        return;
    }

    enemylist* tmp = listaNemici;
    while (tmp != NULL) {
        if (tmp->enemy->isVivo()) {
            if (tmp->enemy->getY() == y && tmp->enemy->getX() == x) {
                vite--;
                y = startY;
                x = startX;
                invulnerabile = 20;
                return;
            }
        }
        tmp = tmp->next;
    }
}

void Giocatore::decrementaInvulnerabilita() {
    if (invulnerabile > 0) invulnerabile--;
}

void Giocatore::disegna() {
    mvaddch(y, x, '@');
}

int Giocatore::getVite() const { return vite; }
int Giocatore::aggiungiPunteggio(int p) { return punteggio += p; }
int Giocatore::getPunteggio() const { return punteggio; }
