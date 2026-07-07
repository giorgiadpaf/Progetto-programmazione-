#include <clocale>
#include <cstddef>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "Map.hpp"
#include "Nemico.hpp"
#include "NemicoSparante.hpp"
#include "Giocatore.hpp"
#include "Classifica.hpp"
#include "Bombe.hpp"
#include <fstream>
#include <cstring>
#include "Menu.hpp"
#include "Tempo.hpp"


//funzione che fa il parsing di un file e costruisce direttamente la lista di livelli
// inserisce sia la lista di nemici sia il punto di spawn del giocatore e concatena tutte le mappe
Map* loadMapsFromFile(const char* fileName, WINDOW* win) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        return NULL;
    }

    Map* head = NULL;
    Map* currentMap = NULL;
    char word[1700];

    while (file >> word) {
        if (strcmp(word, "MAPPA") == 0) {
            char newLogic[20][81];

            for (int i = 0; i < 20; i++) {
                file >> word;
                for (int k = 0; k < 80; k++) {
                    newLogic[i][k] = word[k];
                }
                newLogic[i][80] = '\0';
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

//Funzione di delete per la classe map
void delete_maplist(Map* mappa){
    while(mappa->preclvl() != NULL){
        mappa = mappa->preclvl();
    }

    while (mappa != NULL){
        enemylist* tmp = mappa->_enemylist();
        enemylist* prec = tmp;
        while(tmp != NULL){
            prec = tmp;
            tmp = tmp->next;
            delete prec->enemy;
            delete prec;
        }
        Map* tmpmap = mappa;
        mappa = mappa->nextlvl();
        delete tmpmap;
    }
}

//main aggiornato per permettere al giocatore di muoversi tra una mappa e l'altra
int main() {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE); //MODIFICA: funzione per far funzionare le frecce
    timeout(50);
    srand(time(NULL));
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK); //colore esplosione bomba
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); //colore item raggio
    init_pair(3, COLOR_GREEN, COLOR_BLACK); //colore item tempo

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
        Classifica cl;
        cl.visualizzaTopN();
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

    Map* currmap = mappa;
    Bombe gestoreBombe(currmap);
    Giocatore player(currmap->_yPspawn(), currmap->_xPspawn(), currmap, &gestoreBombe);

    Tempo timerPartita(600);
    timerPartita.start();

    bool won = false;
    bool running = true;
    int oldx = player.getX();
    int oldy = player.getY();
    while (running) {
        int c = getch();
        if (c == 'q') {
            delete_maplist(mappa);
            break;
        }

        enemylist* elist = currmap->_enemylist();

        player.muovi(c);

<<<<<<< HEAD
    	//controlla se il giocatore calpersta item
    	char tileSottoPlayer = currmap->whatsthere(player.getY(), player.getX());
    	if (tileSottoPlayer == '^') {
    		gestoreBombe.raccogliItem(10);
    		currmap->setTile(player.getY(), player.getX(), '.');
    	}
    	else if (tileSottoPlayer == '&') {
    		timerPartita.aggiungiTempo(30); //aggiunge 30 secondi
    		currmap->setTile(player.getY(), player.getX(), '.');
    	}
=======
	//controlla se il giocatore calpersta item
  	char tileSottoPlayer = mappa->whatsthere(player.getY(), player.getX());
	if (tileSottoPlayer == '^') {
		gestoreBombe.raccogliItem(10);
		player.aggiungiPunteggio(5);
		mappa->setTile(player.getY(), player.getX(), '.');
	}
	else if (tileSottoPlayer == '&') {
		timerPartita.aggiungiTempo(30); //aggiunge 30 secondi
		player.aggiungiPunteggio(5);
		mappa->setTile(player.getY(), player.getX(), '.');
	}
>>>>>>> 60056f412d2dfc63445a2ecff6876b0dcfb7396e

        if (currmap->isonN(player)) {
            Map* prossima = currmap->nextlvl();
            if (prossima != NULL) {
                currmap->setPspawn(oldx,oldy);
                currmap = prossima;
                gestoreBombe = Bombe(currmap);
                player.cambiaLivello(currmap, currmap->_xPspawn(), currmap->_yPspawn());
                elist = currmap->_enemylist();
            }else{won = true;}

        }else if (currmap->isonP(player)) {
            Map* precedente = currmap->preclvl();
            if (precedente != NULL) {
                currmap = precedente;
                gestoreBombe = Bombe(currmap);
                player.cambiaLivello(currmap, currmap->_xPspawn(), currmap->_yPspawn());
                elist = currmap->_enemylist();
            }
        }

        enemylist* tmp = elist;
        while (tmp != NULL) {
		   if (tmp->enemy->isVivo()) tmp->enemy->movimento(player.getY(), player.getX(), &gestoreBombe);
           tmp->enemy->controllaMorte(&gestoreBombe, &player);
           tmp = tmp->next;
        }
        player.controllaDanni(elist);
        player.decrementaInvulnerabilita();

        clear();

        currmap->printonscr();
        gestoreBombe.aggiornaEStampa();
        tmp = elist;
        while (tmp != NULL) {
           tmp->enemy->disegna();
           tmp = tmp->next;
        }
        player.disegna();
        mvprintw(20, 0, "Vite: %d", player.getVite());
		mvprintw(21, 0, "Tempo: %02d:%02d", timerPartita.getMinuti(), timerPartita.getSecondi());
		mvprintw(22, 0, "Punteggio: %d", player.getPunteggio());

       if (player.getVite() <= 0 || timerPartita.isScaduto()) {
            clear();
            menu.lost(stdscr, &player);
            delete_maplist(mappa);
            running = false;
        }else if(won == true){
       	    clear();
<<<<<<< HEAD
            menu.victory(stdscr, &player, timerPartita);
            delete_maplist(mappa);
=======
>>>>>>> 60056f412d2dfc63445a2ecff6876b0dcfb7396e
            running = false;
        }

       oldx = player.getX();
       oldy = player.getY();
    }


    endwin();
    return 0;
}
