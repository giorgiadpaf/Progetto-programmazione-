#include "Mappa.hpp"
#include "Nemico.hpp"
#include <cstdlib>
#include <ctime>

Nemico::Nemico(int y, int x, Mappa* m, int t) : Entita(y, x, m, ' ') {
    this->vivo=1; // 1 se è in gioco, 0 se è stato colpito
    this->tipo = t;
    this->frameCounter = 0;

    if (tipo==1){
        this->frameDelay = 3;
        this->simbolo = '@';
    } else if (tipo==2) {
        this->frameDelay = 5;
        this->simbolo = '#';
    } else if (tipo==3) {
        this->frameDelay = 6;
        this->simbolo = '&';
    }

}

int Nemico::movimento(int pY, int pX, int dirCorrente) {
    frameCounter++;
    if (frameCounter < frameDelay) return dirCorrente;
    frameCounter = 0;

    int nextY = y;
    int nextX = x;

    if (tipo == 1) {
        
        if (dirCorrente == 0) nextY--;      // Su
        else if (dirCorrente == 1) nextY++; // Giu
        else if (dirCorrente == 2) nextX--; // Sx
        else if (dirCorrente == 3) nextX++; // Dx

        if (!punmappa->isVuoto(nextY, nextX) || (rand() %  20 == 0)) {
            dirCorrente = rand() % 4;
            return dirCorrente; // Salta questo turno per "girarsi"
        }
    } else if (tipo == 2 || tipo == 3) {
       
        if (pX > x && punmappa->isVuoto(y, x + 1)) nextX++;
        else if (pX < x && punmappa->isVuoto(y, x - 1)) nextX--;
        else if (pY > y && punmappa->isVuoto(y + 1, x)) nextY++;
        else if (pY < y && punmappa->isVuoto(y - 1, x)) nextY--;
    }


    y = nextY;
    x = nextX;
    return dirCorrente;
}


void Nemico::disegna() {
    // Colore rosso per i nemici (init_pair 2 nel main)
    attron(COLOR_PAIR(2));
    mvaddch(y, x, simbolo);
    attroff(COLOR_PAIR(2));
}

void Nemico::controllaMorte() {
    if (punmappa->isRed(y, x)) {
        this->vivo=0;
        this->y = -1;
        this->x = -1;
    }
}

virtual int Nemico::getYp() const { return -1; }
virtual int Nemico::getXp() const { return -1; }

bool Nemico::isVivo() const {
    return vivo;
}
