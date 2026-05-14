#ifndef ENTITA_HPP
#define ENTITA_HPP

#include <ncurses.h>
class Mappa;

class Entita {
protected:
    int y, x;      // Coordinate attuali
    char simbolo;  // Il carattere ASCII 
    Mappa* punmappa;

public:

    Entita(int startY, int startX, Mappa* mappa,  char sym);

    virtual void disegna();

    int getY() const;
    int getX() const;
};

#endif

