#include "Nemico.hpp"
#include "Bombe.hpp"
#include "Map.hpp"
#include "Giocatore.hpp"
#include <cstdlib>
#include <ctime>

Nemico::Nemico(int y, int x, Map* m, int t) : Entita(y, x, m, ' ') {
    this->vivo = 1;
    this->tipo = t;
    this->frameCounter = 0;
    this->dirAttuale = rand() % 4;
    if (tipo == 1)      { this->frameDelay = 7; this->simbolo = '$'; }
    else if (tipo == 2) { this->frameDelay = 10; this->simbolo = '#'; }
    else if (tipo == 3) { this->frameDelay = 13; this->simbolo = '&'; }
}

void Nemico::movimento(int pY, int pX, Bombe* pBombe) {
    frameCounter++;
    if (frameCounter < frameDelay) return;
    frameCounter = 0;
    int nextY = y;
    int nextX = x;
    if (tipo == 1) {
        // --- TIPO 1: MOVIMENTO CASUALE ---
        if (dirAttuale == 0)      nextY--;
        else if (dirAttuale == 1) nextY++;
        else if (dirAttuale == 2) nextX--;
        else if (dirAttuale == 3) nextX++;
        if (!punmappa->isempty(nextY, nextX) || (rand() % 20 == 0)) {
            dirAttuale = rand() % 4;
            return;
        }
    }
    else if (tipo == 2 || tipo == 3) {
        // --- TIPO 2/3: INSEGUIMENTO ---
        bool mosso = false;
        int distY;
        if (pY > y) distY = pY - y;
        else distY = y - pY;
        int distX;
        if (pX > x) distX = pX - x;
        else distX = x - pX;
        if (distX > distY) { 
            if (pX > x && punmappa->isempty(y, x + 1))      { nextX++; mosso = true; }
            else if (pX < x && punmappa->isempty(y, x - 1)) { nextX--; mosso = true; }
            if (!mosso) {
                if (pY > y && punmappa->isempty(y + 1, x))      { nextY++; mosso = true; }
                else if (pY < y && punmappa->isempty(y - 1, x)) { nextY--; mosso = true; }
            }
        } else { 
            if (pY > y && punmappa->isempty(y + 1, x))      { nextY++; mosso = true; }
            else if (pY < y && punmappa->isempty(y - 1, x)) { nextY--; mosso = true; }
            if (!mosso) {
                if (pX > x && punmappa->isempty(y, x + 1))      { nextX++; mosso = true; }
                else if (pX < x && punmappa->isempty(y, x - 1)) { nextX--; mosso = true; }
            }
        }
        if (!mosso) {
            int r = rand() % 4;
            if (r == 0 && punmappa->isempty(y - 1, x))      nextY--;
            else if (r == 1 && punmappa->isempty(y + 1, x)) nextY++;
            else if (r == 2 && punmappa->isempty(y, x - 1)) nextX--;
            else if (r == 3 && punmappa->isempty(y, x + 1)) nextX++;
        }
    }
    if (pBombe->cEunaBomba(nextY, nextX)) {
        dirAttuale = rand() % 4;
        return;
    }
    this->y = nextY;
    this->x = nextX;
}

void Nemico::disegna() {
    int coppiaColore = 1; 
    if (tipo == 2) {
        coppiaColore = 2; 
    } else if (tipo == 3) {
        coppiaColore = 3; 
    }
    attron(COLOR_PAIR(coppiaColore));
    mvaddch(y, x, simbolo);
    attroff(COLOR_PAIR(coppiaColore));
}


void Nemico::controllaMorte(Bombe* pBombe, Giocatore* player) {
    if (this->vivo == 1 && pBombe->colpitaDaEsplosione(y, x)) {
	if (rand() % 100 < 20) { //percentuale di spawn item quando muore il nemico
		if(rand() % 2 == 0) {
			punmappa->setTile(y, x, '^');//item raggio
		} else {
			punmappa->setTile(y, x, '&');//item tempo
		}
        }
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
