#ifndef BOMBE_HPP
#define BOMBE_HPP
#include "Bomba.hpp"
#include "Map.hpp"
#include "Item.hpp"
class Giocatore;

const int MAX_BOMBE = 3; //limite di bombe contemporanee a schermo

class Bombe {
private:
    Bomba inventario[MAX_BOMBE]; //array statico di bombe
    int raggioAttuale;
    Item potenziamento;

public:
    Bombe(Map* mappa);

    //metodi riprendi da file 'Giocatore'
    void aggiungiBomba(int y, int x, Giocatore* player);
    bool cEunaBomba(int y, int x);

    void aggiornaEStampa();

    void raccogliItem(int durata);

    void setRaggio(int r) { raggioAttuale = r; }
    int getRaggio() const { return raggioAttuale; }

    bool colpitaDaEsplosione(int testY, int testX);
};

#endif
