#pragma once
#include "Map.hpp"
#include "Entita.hpp"
#include <ctime>

class Bomba : public Entita {
protected:
    time_t tempoPiazzamento; // quando piazzata a terra
    int raggio;              // raggio esplosione
    bool attiva;             // true se sta nella mappa
    bool inEsplosione;       // true se esplosa
    time_t tempoEsplosione;  // quando inizia animazione esplosione

public:
    Bomba(Map* mappa = nullptr);

    //,etodi di azione
    void piazza(int startY, int startX, int raggioBomba);
    void aggiorna();
    void disattiva();

    //animazione a croce
    void disegna();

    //calcola se una coordinata e' nel fuoco
    bool colpisce(int testY, int testX) const;

    bool isAttiva() const;
    bool isInEsplosione() const;
    int getRaggio() const;
};
