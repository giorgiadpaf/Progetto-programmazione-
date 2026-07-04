#include <clocale>
#include <cstddef>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "Map.hpp"
#include "Nemico.hpp"
#include "NemicoSparante.hpp"
#include "Giocatore.hpp"
#include "Bombe.hpp"
#include <fstream>
#include <cstring>
#include "Menu.hpp"

//funzione che fa il parsing di un file e costruisce direttamente la lista di livelli
// inserisce sia la lista di nemici sia il punto di spawn del giocatore e concatena tutte le mappe

Map* loadMapsFromFile(const char* fileName, WINDOW* win) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        return NULL;
    }

    Map* head = NULL;
    Map* currentMap = NULL;
    char word[256];

    while (file >> word) {
        if (strcmp(word, "MAPPA") == 0) {
            char newLogic[20][41];

            for (int i = 0; i < 20; i++) {
                file >> word;
                for (int k = 0; k < 40; k++) {
                    newLogic[i][k] = word[k];
                }
                newLogic[i][40] = '\0';
            }

            int spawnX = 0, spawnY = 0;
            int enemiesX[50], enemiesY[50], enemiesType[50];
            int numEnemies = 0;

            while (file >> word && strcmp(word, "FINE_MAPPA") != 0) {
                if (strcmp(word, "SPAWN") == 0) {
                    file >> spawnX >> spawnY;
                }
                else if (strcmp(word, "NEMICO") == 0) {
                    file >> enemiesY[numEnemies] >> enemiesX[numEnemies] >> enemiesType[numEnemies];
                    numEnemies++;
                }
            }

            Map* newMap = new Map(currentMap, NULL, newLogic, spawnX, spawnY, win, NULL);

            for (int i = 0; i < numEnemies; i++) {
                newMap->addenemy(enemiesY[i], enemiesX[i], enemiesType[i]);
            }

            if (head == NULL) {
                head = newMap;
                currentMap = newMap;
            } else {
                currentMap->addmapinq(newMap);
                currentMap = newMap;
            }
        }
    }

    file.close();
    return head;
}
//main aggiornato per permettere al giocatore di muoversi tra una mappa e l'altra
//i nemici non si muovono, non so come funzionano
int main() {
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE); //MODIFICA: funzione per far funzionare le frecce
    timeout(50);
    srand(time(NULL));

    Menu menu;
    bool avviaGioco = false;

    while(!avviaGioco){
    	int scelta = menu.opzione();

	if(scelta == 2){
		endwin();
		return 0;
	}
	else if(scelta == 1){
		clear();
		mvprintw(5, 15, "classifica");

		refresh();

		timeout(-1);
		getch();
		timeout(50);
	}
	else if (scelta == 0){
		avviaGioco = true;
	}
    }

    Map* mappa = loadMapsFromFile("Maps.txt", stdscr);
    if (mappa == NULL) {
        endwin();
        printf("Errore: Impossibile caricare il file Maps.txt\n");
        return 1;
    }

    Bombe gestoreBombe(mappa);
    Giocatore player(mappa->_xPspawn(), mappa->_yPspawn(), mappa, &gestoreBombe);

    bool running = true;

    while (running) {
        int c = getch();
        if (c == 'q') break;

        enemylist* elist = mappa->_enemylist();

        player.muovi(c);

        if (mappa->isonN(player)) { 
            Map* prossima = mappa->nextlvl();
            if (prossima != NULL) {
                mappa = prossima;
                gestoreBombe = Bombe(mappa); 
                player.cambiaLivello(mappa, mappa->_xPspawn(), mappa->_yPspawn());
                elist = mappa->_enemylist(); 
            }
        }
        else if (mappa->isonP(player)) { 
            Map* precedente = mappa->preclvl();
            if (precedente != NULL) {
                mappa = precedente;
                gestoreBombe = Bombe(mappa);
                player.cambiaLivello(mappa, mappa->_xPspawn(), mappa->_yPspawn());
                elist = mappa->_enemylist();
            }
        }

        enemylist* tmp = elist;
        while (tmp != NULL) {
           tmp->enemy->controllaMorte(&gestoreBombe);
           tmp = tmp->next;
        }
        player.controllaDanni(elist);
        player.decrementaInvulnerabilita();

        clear();

        mappa->printonscr();
        gestoreBombe.aggiornaEStampa();
        tmp = elist;
        while (tmp != NULL) {
           tmp->enemy->disegna();
           tmp = tmp->next;
        }
        player.disegna();
        mvprintw(20, 0, "Vite: %d", player.getVite());

        if (player.getVite() <= 0) {
            clear();
            mvprintw(10, 15, "GAME OVER - Hai perso tutte le vite");
            mvprintw(12, 12, "Premi un tasto per chiudere il gioco...");
            timeout(-1);
            refresh();
            getch(); 
            running = false; 
        }
    }

    endwin();
    return 0;
}
