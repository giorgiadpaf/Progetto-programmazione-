#include "Entita.hpp"

Entita::Entita(int startY, int startX, Map* mappa, char sym){
    y = startY;
    x = startX;
    simbolo = sym;
    punmappa = mappa;
}


void Entita::disegna(){
    mvaddch(y, x, simbolo);
}

int Entita::getY() const{
    return y;
}

int Entita::getX() const{
    return x;
}
