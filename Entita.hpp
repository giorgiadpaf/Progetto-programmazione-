#ifndef ENTITA_HPP
#define ENTITA_HPP

#include <ncurses.h>
class Mappa;

class Entita {
protected:
    int y, x;      // Coordinate attuali
    char simbolo;  // Il carattere ASCII (es. '@')
    Mappa* punmappa;

public:
    // Costruttore: decide dove parte il giocatore
    Entita(int startY, int startX, Mappa* mappa,  char sym);

    // Funzione per stampare il giocatore sullo schermo
    virtual void disegna();

    // Getter per le coordinate (serviranno agli altri componenti)
    int getY() const;
    int getX() const;
};

#endif

