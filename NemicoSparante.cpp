#include "NemicoSparante.hpp"
#include "Map.hpp"

NemicoSparante::NemicoSparante(int y, int x, Map* m) : Nemico(y, x, m, 3) {
    this->dirProiettile = -1;
    this->frameProi = 0;
    this->xp = -1;
    this->yp = -1;

    this->reloadTimer = 0;
    this->reloadTime = 30;
}

void NemicoSparante::movimento(int pY, int pX, Bombe* pBombe) {
    if (dirProiettile != -1) {
        frameProi++;
        if (frameProi >= 2) {
            frameProi = 0;
            if (dirProiettile == 0)      yp--;
            else if (dirProiettile == 1) yp++;
            else if (dirProiettile == 2) xp--;
            else if (dirProiettile == 3) xp++;

            char t = punmappa->whatsthere(yp, xp);
            if (t == '#' || t == '*' || (yp == pY && xp == pX)) {
                dirProiettile = -1;
            }
        }
    }
    else {
        if (reloadTimer < reloadTime) {
            reloadTimer++;
        }
        else {
            bool haSparato = false;
            if (pY == y && pX > x && punmappa->isempty(y, x + 1)) {
                dirProiettile = 3; yp = y; xp = x + 1; haSparato = true;
            } else if (pY == y && pX < x && punmappa->isempty(y, x - 1)) {
                dirProiettile = 2; yp = y; xp = x - 1; haSparato = true;
            } else if (pX == x && pY > y && punmappa->isempty(y + 1, x)) {
                dirProiettile = 1; yp = y + 1; xp = x; haSparato = true;
            } else if (pX == x && pY < y && punmappa->isempty(y - 1, x)) {
                dirProiettile = 0; yp = y - 1; xp = x; haSparato = true;
            }
            if (haSparato) {
                reloadTimer = 0;
            }
        }
    }
    Nemico::movimento(pY, pX, pBombe);
}

void NemicoSparante::disegna() {
    Nemico::disegna(); /
    if (dirProiettile != -1) {
        attron(COLOR_PAIR(1));
        mvaddch(yp, xp, '*');
        attroff(COLOR_PAIR(1));
    }
}


int NemicoSparante::getYp() const {
    return yp;
}

int NemicoSparante::getXp() const {
    return xp;
}
