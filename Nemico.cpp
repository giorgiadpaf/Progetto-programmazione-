#include "Nemico.hpp"
#include "Bombe.hpp"
#include "Map.hpp"
#include <cstdlib>
#include <ctime>

Nemico::Nemico(int y, int x, Map* m, int t) : Entita(y, x, m, ' ') {
    this->vivo=1;
    this->tipo = t;
    this->frameCounter = 0;
    if (tipo==1){ this->frameDelay = 3; this->simbolo = '$'; }
    else if (tipo==2) { this->frameDelay = 5; this->simbolo = '#'; }
    else if (tipo==3) { this->frameDelay = 6; this->simbolo = '&'; }
}

int Nemico::movimento(int pY, int pX, int dirCorrente) {
    frameCounter++;
    if (frameCounter < frameDelay) return dirCorrente;
    frameCounter = 0;
    int nextY = y;
    int nextX = x;
    if (tipo == 1) {
        if (dirCorrente == 0) nextY--;
        else if (dirCorrente == 1) nextY++;
        else if (dirCorrente == 2) nextX--;
        else if (dirCorrente == 3) nextX++;
    }
    if (punmappa->isempty(nextY, nextX)) {
        y = nextY;
        x = nextX;
    }
    return dirCorrente;
}

void Nemico::disegna() {
    mvaddch(y, x, simbolo);
}

void Nemico::controllaMorte(Bombe* pBombe) {
    if (this->vivo == 1 && pBombe->colpitaDaEsplosione(y, x)) {
        this->vivo=0;
        this->y = -1;
        this->x = -1;
    }
}

int Nemico::getYp() const { return -1; }
int Nemico::getXp() const { return -1; }

bool Nemico::isVivo() const { return vivo == 1; }
