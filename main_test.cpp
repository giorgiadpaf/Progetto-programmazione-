#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "Mappa.hpp"
#include "Nemico.hpp"
#include "NemicoSparante.hpp" // Aggiungi questa riga in alto
#include "Giocatore.hpp"
int main() {
    initscr();
    noecho();
    curs_set(0);
    timeout(50);
    srand(time(NULL));

    Mappa mappa;
    // Corretta la parentesi e rimosso 'new' per semplicità nel test
    Giocatore player(18, 38, &mappa);
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

        clear();
        // Disegna i bordi
        for(int i=0; i<40; i++) { mvaddch(0, i, '-'); mvaddch(19, i, '-'); }
        for(int i=0; i<20; i++) { mvaddch(i, 0, '|'); mvaddch(i, 39, '|'); }
        player.disegna();
        n1.disegna();
        n2.disegna();
        n3.disegna();
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
