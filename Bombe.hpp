#ifndef BOMBE_HPP
#define BOMBE_HPP
#include "Bomba.hpp"
#include "Map.hpp"
const int MAX_BOMBE = 3; //limite di bombe contemporanee a schermo

class Bombe {
private:
    Bomba inventario[MAX_BOMBE]; //array statico di bombe
    int raggioAttuale;

public:
    Bombe(Map* mappa);

    //metodi riprendi da file 'Giocatore'
    void aggiungiBomba(int y, int x);
    bool cEunaBomba(int y, int x);

    void aggiornaEStampa();

    void setRaggio(int r) { raggioAttuale = r; }
    int getRaggio() const { return raggioAttuale; }

    bool colpitaDaEsplosione(int testY, int testX);
};

#endif
