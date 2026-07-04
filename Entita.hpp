#pragma once
#include <ncurses.h>
class Map;

class Entita {
protected:
    int y, x;      // Coordinate attuali
    char simbolo;  // Il carattere ASCII
    Map* punmappa;

public:

    Entita(int startY, int startX, Map* mappa,  char sym);

    virtual void disegna();

    int getY() const;
    int getX() const;
};
