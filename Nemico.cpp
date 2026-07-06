#include "Nemico.hpp"
#include "Bombe.hpp"
#include "Map.hpp"
#include "Giocatore.hpp"
#include <cstdlib>
#include <ctime>

Nemico::Nemico(int y, int x, Map* m, int t) : Entita(y, x, m, ' ') {
    this->vivo=1;
    this->tipo = t;
    this->frameCounter = 0;
    this->dirAttuale = rand() % 4;
    if (tipo==1){ this->frameDelay = 9; this->simbolo = '$'; }
    else if (tipo==2) { this->frameDelay = 12; this->simbolo = '#'; }
    else if (tipo==3) { this->frameDelay = 15; this->simbolo = '&'; }
}

void Nemico::movimento(int pY, int pX, Bombe* pBombe) {
    frameCounter++;
    if (frameCounter < frameDelay) return;
    frameCounter = 0;

    int nextY = y;
    int nextX = x;

    if (tipo == 1) {
        if (dirAttuale == 0) nextY--;     
        else if (dirAttuale == 1) nextY++; 
        else if (dirAttuale == 2) nextX--; 
        else if (dirAttuale == 3) nextX++; 
        if (!punmappa->isempty(nextY, nextX) || (rand() %  20 == 0)) {
            dirAttuale = rand() % 4;
            return; 
        }
    } else if (tipo == 2 || tipo == 3) {
        if (pX > x && punmappa->isempty(y, x + 1)) nextX++;
        else if (pX < x && punmappa->isempty(y, x - 1)) nextX--;
        else if (pY > y && punmappa->isempty(y + 1, x)) nextY++;
        else if (pY < y && punmappa->isempty(y - 1, x)) nextY--;
    }
    if(pBombe->cEunaBomba(nextY, nextX)) {
        dirAttuale = rand() % 4;
        return;
    }
    y = nextY;
    x = nextX;
    return;
}

void Nemico::disegna() {
    mvaddch(y, x, simbolo);
}

void Nemico::controllaMorte(Bombe* pBombe, Giocatore* player) {
    if (this->vivo == 1 && pBombe->colpitaDaEsplosione(y, x)) {
        this->vivo=0;
        this->y = -1;
        this->x = -1;
        if (tipo==1){ player->aggiungiPunteggio(100); }
        else if (tipo==2) { player->aggiungiPunteggio(115); }
        else if (tipo==3) { player->aggiungiPunteggio(130); }
    }
}

int Nemico::getYp() const { return -1; }
int Nemico::getXp() const { return -1; }

bool Nemico::isVivo() const { return vivo == 1; }
