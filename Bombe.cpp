#include "Bombe.hpp"
#include "Map.hpp"
#include "Giocatore.hpp"


Bombe::Bombe(Map* mappa) {
    raggioAttuale = 1; //raggio iniziale standard

    //array statico inizializzato associando la mappa a ciascuna bomba
    for (int i = 0; i < MAX_BOMBE; i++) {
        inventario[i] = Bomba(mappa);
    }
}

void Bombe::aggiungiBomba(int y, int x, Giocatore* player) {
    //cerca e pizza bomba
    for (int i = 0; i < MAX_BOMBE; i++) {
        if (!inventario[i].isAttiva()) {
            inventario[i].piazza(y, x, raggioAttuale, player);
            break; //esce quando ne trova una disponibile
        }
    }
}

bool Bombe::cEunaBomba(int y, int x) {
    //controlla se una delle bombe attive si trova esattamente alle coordinate (y, x)
    // per impedire al giocatore di camminarci sopra
    for (int i = 0; i < MAX_BOMBE; i++) {
        if (inventario[i].isAttiva() && inventario[i].getY() == y && inventario[i].getX() == x) {
            return true;
        }
    }
    return false;
}

void Bombe::aggiornaEStampa() {
    //conto alla rovescia ed esplosione bomba
    for (int i = 0; i < MAX_BOMBE; i++) {
        if (inventario[i].isAttiva()) {
            inventario[i].aggiorna(); //controlla il tempo
            if (inventario[i].isAttiva()) {
                inventario[i].disegna(); //stampa a schermo
            }
        }
    }
}

bool Bombe::colpitaDaEsplosione(int testY, int testX){
	for (int i =0; i< MAX_BOMBE; i++) {
		if(inventario[i].colpisce(testY, testX)) {
			return true;
		}
	}
	return false;
}
