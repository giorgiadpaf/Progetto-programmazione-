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



int main() {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE); 
    timeout(50);
    srand(time(NULL));
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);    // Esplosione
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Item raggio
    init_pair(3, COLOR_GREEN, COLOR_BLACK);  // Item tempo

    Menu menu;

    // --- CICLO ESTERNO: Gestisce il ritorno al Menu ---
    while (true) {
        bool avviaGioco = false;

        // FASE 1: GESTIONE MENU
        while (!avviaGioco) {
            int scelta = menu.opzione();
            if (scelta == 2) { // ESCI
                endwin();
                return 0;
            }
            else if (scelta == 1) { // CLASSIFICA
                Classifica cl;
                cl.visualizzaTopN();
            }
            else if (scelta == 0) { // NUOVA PARTITA
                avviaGioco = true;
            }
        }

        // FASE 2: INIZIALIZZAZIONE PARTITA
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
        
        // Salviamo le posizioni precedenti
        int oldx = player.getX();
        int oldy = player.getY();

        // FASE 3: GAME LOOP
        while (running) {
            int c = getch();
            if (c == 'q') {
                running = false; 
                break;
            }

            enemylist* elist = currmap->_enemylist();
            player.muovi(c);

            // LOGICA ITEM
            char tileSottoPlayer = currmap->whatsthere(player.getY(), player.getX());
            if (tileSottoPlayer == '^') {
                gestoreBombe.raccogliItem(10);
                player.aggiungiPunteggio(5);
                currmap->setTile(player.getY(), player.getX(), '.');
            }
            else if (tileSottoPlayer == '&') {
                timerPartita.aggiungiTempo(30);
                player.aggiungiPunteggio(5); 
                currmap->setTile(player.getY(), player.getX(), '.');
            }

            if (currmap->isonN(player)) {
                Map* prossima = currmap->nextlvl();
                if (prossima != NULL) {
                    currmap->setPspawn(oldx, oldy); // Usa le coordinate salvate
                    currmap = prossima;
                    gestoreBombe = Bombe(currmap);
                    player.cambiaLivello(currmap, currmap->_yPspawn(), currmap->_xPspawn());
                    elist = currmap->_enemylist();
                } else {
                    won = true; // Fine dei livelli
                }
            }
            else if (currmap->isonP(player)) {
                Map* precedente = currmap->preclvl();
                if (precedente != NULL) {
                    currmap = precedente;
                    gestoreBombe = Bombe(currmap);
                    player.cambiaLivello(currmap, currmap->_yPspawn(), currmap->_xPspawn());
                    elist = currmap->_enemylist();
                }
            }

            // UPDATE NEMICI
            enemylist* tmp = elist;
            while (tmp != NULL) {
                bool eraVivo = tmp->enemy->isVivo();
                if (eraVivo) {
                    tmp->enemy->movimento(player.getY(), player.getX(), &gestoreBombe);
                }
                tmp->enemy->controllaMorte(&gestoreBombe, &player);
                
                // Punti per nemico ucciso
                if (eraVivo && !tmp->enemy->isVivo()) {
                    player.aggiungiPunteggio(100);
                }
                tmp = tmp->next;
            }

            player.controllaDanni(elist);
            player.decrementaInvulnerabilita();

            // RENDERING
            clear();
            currmap->printonscr();
            gestoreBombe.aggiornaEStampa();
            
            tmp = currmap->_enemylist();
            while (tmp != NULL) {
                tmp->enemy->disegna();
                tmp = tmp->next;
            }
            player.disegna();

            // Interfaccia di gioco
            mvprintw(LINES - 2, 0, "Vite: %d | Tempo: %02d:%02d | Punteggio: %d", 
                     player.getVite(), timerPartita.getMinuti(), timerPartita.getSecondi(), player.getPunteggio());

            // GESTIONE FINE PARTITA (Schermate centrate)
            if (player.getVite() <= 0 || timerPartita.isScaduto()) {
                lost(stdscr, &player); // Chiamata alla tua funzione centrata
                running = false;
            } 
            else if (won) {
                victory(stdscr, &player, timerPartita); // Chiamata alla tua funzione centrata
                running = false;
            }

            refresh();
            
            // Aggiorna le coordinate "old" per il prossimo frame
            oldx = player.getX();
            oldy = player.getY();
        }

        // FASE 4: PULIZIA (Prima di tornare al menu)
        delete_maplist(mappa); 
        timeout(50); // Assicura che il menu non sia bloccato
    }

    endwin();
    return 0;
}
