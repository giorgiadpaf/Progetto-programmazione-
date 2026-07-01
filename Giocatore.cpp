#include "Mappa.hpp"
#include "Giocatore.hpp"
#include "Nemico.hpp"
#include "Bombe.hpp" //MODIFICA: inclusione header

//MODIFICA: aggiornato il costruttore
Giocatore::Giocatore(int y, int x, Mappa* mappa, Bombe* pBombe) : Entita(y, x, mappa, 'A') {
    this->pBombe = pBombe;
    this->vite = 3;
    this->startY = y; // posizione iniziale
    this->startX = x;
    this->invulnerabile = 0;
    this->punteggio = 0;
}


void Giocatore::muovi(int input){
    int newx = x;
    int newy = y;
    if (input == 'a' || input == KEY_LEFT) {
        newx--;
    }
    else if (input == 'w' || input == KEY_UP) {
        newy--;
    }
    else if (input == 'd' || input == KEY_RIGHT) {
        newx++;
    }
    else if (input == 's' || input == KEY_DOWN) {
        newy++;
    }
    if(punmappa->isVuoto(newy, newx)  && !pBombe->cEunaBomba(newy, newx)){
            y=newy;
            x=newx;
        }

     if (input == ' ') {
        pBombe->aggiungiBomba(y, x);
    }

}
void Giocatore::controllaDanni(Nemico* listaNemici[], int numeroNemici) {
    if (invulnerabile > 0) return;

    //MODIFICA: verifica se il giocatore viene preso dall'esplosione della bobma
    if(pBombe->colpitaDaEsplosione(y, x)){
	    vite--;
	    y = startY;
	    x = startX;
	    invulnerabile = 20;
	    return;
    }

    // Controllo Fuoco
    if (punmappa->isRed(y, x)) {
        vite--;
        invulnerabile = 20; 
        return;
    }

    for (int i = 0; i < numeroNemici; i++) {
        if (!listaNemici[i]->isVivo()) continue;

        // CONTROLLO CORPO DEL NEMICO
        if (listaNemici[i]->getY() == y && listaNemici[i]->getX() == x) {
            vite--;
            y = startY; // Respawn per contatto fisico
            x = startX;
            invulnerabile = 20;
            return;
        }

        // CONTROLLO PROIETTILE
        if (listaNemici[i]->getYp() == y && listaNemici[i]->getXp() == x) {
            vite--;
            invulnerabile = 20;
            return;
        }
    }
}

void Giocatore::decrementaInvulnerabilita() {
    if (invulnerabile > 0) invulnerabile--;
}

void Giocatore::disegna() {
    if (invulnerabile > 0) {
        if (invulnerabile % 2 != 0) { //acceso-spento
            return;
        }
    }

    attron(COLOR_PAIR(1));
    mvaddch(y, x, simbolo);
    attroff(COLOR_PAIR(1));
}

int Giocatore::getVite() const{
    return vite;
}


int Giocatore::aggiungiPunteggio(int punti){
    this->punteggio += punti;
    return this->punteggio;
}


int Giocatore::getPunteggio() const{
    return punteggio;
}
