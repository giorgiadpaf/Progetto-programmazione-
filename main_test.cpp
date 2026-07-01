#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "Mappa.hpp"
#include "Nemico.hpp"
#include "NemicoSparante.hpp"
#include "Giocatore.hpp"
#include "Bombe.hpp" //MODIFICA: inclusione header

int main() {
    initscr();
    noecho();
    curs_set(0);
    timeout(50);
    srand(time(NULL));

    Mappa mappa;
    Bombe gestoreBombe(&mappa); //MODIFICA: inizializzato il gestore delle bombe passandogli mappa
    
    Giocatore player(18, 38, &mappa, &gestoreBombe); //MODIFICA: passato il gestore al costruttore 
    Nemico n1(1, 1, &mappa, 1);
    Nemico n2(1, 2, &mappa, 2);
    NemicoSparante n3(1,5, &mappa);
    int d = 1;
    while (true) {
        int c = getch();
        if (c == 'q') break;

        player.muovi(c);
        int y = player.getY();
        int x = player.getX();
        d = n1.movimento(0,0,d);
        n2.movimento(y,x,0);
        n3.movimento(y,x,0);
        Nemico* lista[] = { &n1, &n2, &n3 };
        player.controllaDanni(lista, 3);
        player.decrementaInvulnerabilita();

	//MODIFICA: aggiunto controllo morte per ogni nemico
	n1.controllaMorte(&gestoreBombe);
	n2.controllaMorte(&gestoreBombe);
	n3.controllaMorte(&gestoreBombe);

        clear();
        // Disegna i bordi
        for(int i=0; i<40; i++) { mvaddch(0, i, '-'); mvaddch(19, i, '-'); }
        for(int i=0; i<20; i++) { mvaddch(i, 0, '|'); mvaddch(i, 39, '|'); }

        player.disegna();
        n1.disegna();
        n2.disegna();
        n3.disegna();
        
	//MODIFICA: chiamata che aggiorna i timer delle bombe e stampa esplosione bombe
	gestoreBombe.aggiornaEStampa();

	mvprintw(0, 0, "Vite: %d", player.getVite());
        if(player.getVite() <= 0){
            clear();
            mvprintw(10, 15, "GAME OVER - Hai perso tutte le vite");
            mvprintw(12, 12, "Premi un tasto per chiudere il gioco...");
            timeout(-1); // Disabilita il timeout (aspetta per sempre)
            refresh();
            getch();    // Aspetta l'input dell'utente
            break;
        }
        refresh();
    }

    endwin();
    return 0;
}
