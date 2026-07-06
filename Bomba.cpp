#include "Bomba.hpp"
#include "Map.hpp"
#include "Giocatore.hpp"
#include <ctime>
#include <ncurses.h>

// posiziona la bomba nelle coordinate (0, 0)
Bomba::Bomba(Map* mappa) : Entita(0, 0, mappa, 'O') {
    attiva = false;
    inEsplosione = false;
    raggio = 3;
    for(int i = 0; i < 4; i++) raggioEffettivo[i] = 0;
}

void Bomba::piazza(int startY, int startX, int raggioBomba, Giocatore* Pgiocatore) {
    y = startY;
    x = startX;
    raggio = raggioBomba;
    tempoPiazzamento = time(NULL); // salva il momento esatto in cui il giocatore l'ha piazzata
    attiva = true;
    inEsplosione = false;
    simbolo = 'O';
	player = Pgiocatore;
    for(int i = 0; i < 4; i++) {
        raggioEffettivo[i] = 0;
    }
}

void Bomba::aggiorna() {
    if (!attiva) return;

    if (!inEsplosione) {
        // tempoo di attesa per esplosione bomba: 3 sec
        if (difftime(time(NULL), tempoPiazzamento) >= 3) {
            inEsplosione = true;
            tempoEsplosione = time(NULL);

            // logica dei danni
	    // sotto, sopra, sinstra, destra
            int direzioni[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	    for (int d = 0; d < 4; d++) {
		raggioEffettivo[d] = 0;

                for (int i = 1; i <= raggio; i++) {
                    int ny = y + (direzioni[d][0] * i);
                    int nx = x + (direzioni[d][1] * i);

		    char tile = punmappa->whatsthere(ny, nx);

		    if(tile == '#'){
			    break; //muro indistruttibvile
		    }

		    raggioEffettivo[d] = i;

		    if(tile == '*'){
			    punmappa->setTile(ny, nx, '.');
				if (player != NULL) {
            		player->aggiungiPunti(10); 
        		}
			    break;
		    }
		}
	     }
	    }
    } else {
        //esplosione visibile a schermo per 1 secondo
        if (difftime(time(NULL), tempoEsplosione) >= 1) {
            disattiva(); //libera lo slot
        }
    }
}

void Bomba::disegna() {
	if(!attiva) return;

	if(!inEsplosione) {
		mvaddch(y, x, simbolo);
	} else {
		attron(COLOR_PAIR(1));
		mvprintw(y, x, "%s", "█");

		int direzioni[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

		for(int d=0; d < 4; d++) {
			for(int i=1; i<=raggio; i++) {
				int ny= y + (direzioni[d][0] * i);
				int nx= x + (direzioni[d][1] * i);

				if (punmappa->whatsthere(ny, nx) != '#') {
                    			mvprintw(ny, nx, "%s", "█");
                		}
			}
		}
		attroff(COLOR_PAIR(1));
	}
}

bool Bomba::colpisce(int testY, int testX) const {
	if(!attiva || !inEsplosione) return false;

	if(testY == y && testX == x) return true;

	int direzioni[4][2] ={{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int d = 0; d < 4; d++) {
        for (int i = 1; i <= raggio; i++) {
            int ny = y + (direzioni[d][0] * i);
            int nx = x + (direzioni[d][1] * i);

            if (testY == ny && testX == nx) return true;
        }
    }
    return false;
}

void Bomba::disattiva() {
    attiva = false;
    inEsplosione = false;
}

bool Bomba::isAttiva() const { return attiva; }
bool Bomba::isInEsplosione() const { return inEsplosione; }
int Bomba::getRaggio() const { return raggio; }
