#include "NemicoSparante.hpp"
#include "Mappa.hpp"

NemicoSparante::NemicoSparante(int y, int x, Mappa* m) : Nemico(y, x, m, 3){
    this->dirProiettile = -1;
    this->frameProi=0;
    this->xp=-1;
    this->yp=-1;
}
int NemicoSparante::movimento(int pY, int pX, int dirCorrente){

    int nuovaDir = Nemico::movimento(pY, pX, dirCorrente); //AVEVO SBAGLIATO IL RICHIAMO

    if (dirProiettile == -1) {
        if (pY < y && pX == x && punmappa->isVuoto(y - 1, x)) {
            dirProiettile=0;
            yp=y-1;
            xp=x;
        }
        else if (pY > y && pX == x && punmappa->isVuoto(y+1, x)) {
            dirProiettile=1;
            yp=y+1;
            xp=x;
        }
        else if (pX < x && pY == y && punmappa->isVuoto(y, x - 1)){
            dirProiettile=2;
            yp=y;
            xp=x-1;
        }
        else if (pX > x && pY == y && punmappa->isVuoto(y, x+1)) {
            dirProiettile=3;
            yp=y;
            xp=x+1;
        }

    } else {
        frameProi++;
        if (frameProi >= 2){
            frameProi=0;
            if (dirProiettile == 0)  yp--;      // Su
            else if (dirProiettile == 1) yp++; // Giu
            else if (dirProiettile == 2) xp--; // Sx
            else if (dirProiettile == 3) xp++;
            if(!punmappa->isVuoto(yp, xp)) {
                dirProiettile=-1;
            }
        }
    }
    return nuovaDir;
}

int NemicoSparante::getYp(){
    return yp;
}

int NemicoSparante::getXp(){
    return xp;
}

void NemicoSparante::disegna(){
    Nemico::disegna();
    if (dirProiettile != -1) {
        attron(COLOR_PAIR(2));
        mvaddch(yp, xp, '*');
        attroff(COLOR_PAIR(2));
    }
}
