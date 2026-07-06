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
#include "Tempo.hpp"

void victory(WINDOW* win) {
    clear();
    box(win, 0, 0);
    int max_y, max_x;
    getmaxyx(win, max_y, max_x);

    const char* scritta[6] = {
        "██╗   ██╗██╗████████╗████████╗██████╗ ██████╗ ██╗ █████╗ ",
        "██║   ██║██║╚══██╔══╝╚══██╔══╝██╔══██╗██╔══██╗██║██╔══██╗",
        "██║   ██║██║   ██║      ██║   ██║  ██║██████╔╝██║███████║",
        "╚██╗ ██╔╝██║   ██║      ██║   ██║  ██║██╔══██╗██║██╔══██║",
        " ╚████╔╝ ██║   ██║      ██║   ██████╔╝██║  ██║██║██║  ██║",
        "  ╚═══╝  ╚═╝   ╚═╝      ╚═╝   ╚═════╝ ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝"
    };

    int larghezza_scritta = 57;
    int altezza_scritta = 6;
    int altezza_totale = 11;

    int start_y = (max_y - altezza_totale) / 2;
    int start_x_scritta = (max_x - larghezza_scritta) / 2;

    for (int i = 0; i < altezza_scritta; i++) {
        mvwprintw(win, start_y + i, start_x_scritta, "%s", scritta[i]);
    }
    //possibilmente stampare anche  il punteggio a schermo
    const char* msg1 = "HAI COMPLETATO TUTTI I LIVELLI!";
    const char* msg2 = "Premi un tasto per uscire...";
    const char* msg3 = "Inserisci il tuo nome per aggiornare la classifica: ";
    int start_x_msg1 = (max_x - strlen(msg1)) / 2;
    int start_x_msg2 = (max_x - strlen(msg2)) / 2;
    int start_x_msg3 = (max_x - strlen(msg3)) / 2;

    mvwprintw(win, start_y + altezza_scritta + 2, start_x_msg1, "%s", msg1);
    mvwprintw(win, start_y + altezza_scritta + 4, start_x_msg2, "%s", msg2);
    mvwprintw(win, start_y + altezza_scritta + 6, start_x_msg3, "%s", msg3);
    wrefresh(win);

    timeout(-1); // Ferma l'esecuzione all'infinito in attesa di input
    getch();     // Cattura il tasto per poi chiudere
}

void lost(WINDOW* win) {
    clear();
    box(win, 0, 0);
    int max_y, max_x;
    getmaxyx(win, max_y, max_x);

    const char* scritta[6] = {
        "██╗  ██╗ █████╗ ██╗    ██████╗ ███████╗██████╗ ███████╗ ██████╗ ",
        "██║  ██║██╔══██╗██║    ██╔══██╗██╔════╝██╔══██╗██╔════╝██╔═══██╗",
        "███████║███████║██║    ██████╔╝█████╗  ██████╔╝███████╗██║   ██║",
        "██╔══██║██╔══██║██║    ██╔═══╝ ██╔══╝  ██╔══██╗╚════██║██║   ██║",
        "██║  ██║██║  ██║██║    ██║     ███████╗██║  ██║███████║╚██████╔╝",
        "╚═╝  ╚═╝╚═╝  ╚═╝╚═╝    ╚═╝     ╚══════╝╚═╝  ╚═╝╚══════╝ ╚═════╝ "
    };

    int larghezza_scritta = 64;
    int altezza_scritta = 6;
    int altezza_totale = 11;

    int start_y = (max_y - altezza_totale) / 2;
    int start_x_scritta = (max_x - larghezza_scritta) / 2;

    for (int i = 0; i < altezza_scritta; i++) {
        mvwprintw(win, start_y + i, start_x_scritta, "%s", scritta[i]);
    }
	const char* msg1;
    if(player->getVite() <= 0) msg1 = "HAI TERMINATO LE VITE A DISPOSIZIONE :(";
    else msg1 = "HAI TERMINATO IL TEMPO A DISPOSIZIONE :(";
    int start_x_msg1 = (max_x - strlen(msg1)) / 2;
    mvwprintw(win, start_y + altezza_scritta + 2, start_x_msg1, "%s", msg1);
    char prompt[50];
    sprintf(prompt, "PUNTEGGIO FINALE: %d", player->getPunteggio());
    mvwprintw(win, start_y + altezza_scritta + 4, (max_x - strlen(prompt)) / 2, "%s", prompt);
    const char* chiedi_nome = "Inserisci il tuo nome per la classifica:";
    mvwprintw(win, start_y + altezza_scritta + 6, (max_x - strlen(chiedi_nome)) / 2, "%s", chiedi_nome);
    wrefresh(win);
    char nomeUtente[50];
    echo();             
    curs_set(1);       
    wmove(win, start_y + altezza_scritta + 9, (max_x / 2) - 10);
    wgetnstr(win, nomeUtente, 49);
    noecho();           
    curs_set(0);        
    Classifica cl;
    cl.salvaPunteggio(nomeUtente, player->getPunteggio());
    cl.visualizzaTopN();
}


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
//main aggiornato per permettere al giocatore di muoversi tra una mappa e l'altra
//i nemici non si muovono, non so come funzionano
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

    Bombe gestoreBombe(mappa);
    Giocatore player(mappa->_yPspawn(), mappa->_xPspawn(), mappa, &gestoreBombe);

    Tempo timerPartita(600);
    timerPartita.start();

    bool won = false;
    bool running = true;

    while (running) {
        int c = getch();
        if (c == 'q') break;

        enemylist* elist = mappa->_enemylist();

        player.muovi(c);

	//controlla se il giocatore calpersta item
  	char tileSottoPlayer = mappa->whatsthere(player.getY(), player.getX());
	if (tileSottoPlayer == '^') {
		gestoreBombe.raccogliItem(10);
		mappa->setTile(player.getY(), player.getX(), '.');
	}
	else if (tileSottoPlayer == '&') {
		timerPartita.aggiungiTempo(30); //aggiunge 30 secondi 
		mappa->setTile(player.getY(), player.getX(), '.');
	}

        if (mappa->isonN(player)) { 
            Map* prossima = mappa->nextlvl();
            if (prossima != NULL) {
                mappa->setPspawn(player.getX()-1,player.getY());
                mappa = prossima;
                gestoreBombe = Bombe(mappa);
                player.cambiaLivello(mappa, mappa->_xPspawn(), mappa->_yPspawn());
                elist = mappa->_enemylist();
            }else{won = true;}

        }else if (mappa->isonP(player)) {
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
		   if (tmp->enemy->isVivo()) tmp->enemy->movimento(player.getY(), player.getX(), &gestoreBombe);
           tmp->enemy->controllaMorte(&gestoreBombe, &player);
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
		mvprintw(21, 0, "Tempo: %02d:%02d", timerPartita.getMinuti(), timerPartita.getSecondi());
		mvprintw(22, 0, "Punteggio: %d", player.getPunteggio());

       if (player.getVite() <= 0 || timerPartita.isScaduto()) {
            clear();
            lost(stdscr, &player);
            running = false;
        }else if(won == true){
       	    clear();
            victory(stdscr);
            running = false;
        }

    }

    endwin();
    return 0;
}
