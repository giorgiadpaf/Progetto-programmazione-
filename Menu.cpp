#include <cstring>
#include <ncurses.h>
#include "Menu.hpp"
#include "Classifica.hpp"

int Menu::opzione() {
    int selezione = 0;
    int tasto;

    while (true) {
        clear();
        box(stdscr, 0, 0);
        const char* titolo[6] = {
            "██████╗  ██████╗ ███╗   ███╗██████╗ ███████╗██████╗ ███╗   ███╗ █████╗ ███╗   ██╗",
            "██╔══██╗██╔═══██╗████╗ ████║██╔══██╗██╔════╝██╔══██╗████╗ ████║██╔══██╗████╗  ██║",
            "██████╔╝██║   ██║██╔████╔██║██████╔╝█████╗  ██████╔╝██╔████╔██║███████║██╔██╗ ██║",
            "██╔══██╗██║   ██║██║╚██╔╝██║██╔══██╗██╔══╝  ██╔══██╗██║╚██╔╝██║██╔══██║██║╚██╗██║",
            "██████╔╝╚██████╔╝██║ ╚═╝ ██║██████╔╝███████╗██║  ██║██║ ╚═╝ ██║██║  ██║██║ ╚████║",
            "╚═════╝  ╚═════╝ ╚═╝     ╚═╝╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝"
        };

        int larghezza_titolo = 81;
        int center_titolo = (COLS - larghezza_titolo) / 2;

        for (int i = 0; i < 6; i++) {
            mvprintw(4 + i, center_titolo, "%s", titolo[i]);
        }

        const char* opt0 = (selezione == 0) ? "> NUOVA PARTITA"      : "  NUOVA PARTITA";
        const char* opt1 = (selezione == 1) ? "> CLASSIFICA" : "  CLASSIFICA";
        const char* opt2 = (selezione == 2) ? "> ESCI"       : "  ESCI";

        int center_opt = (COLS - 12) / 2;

        mvprintw(15, center_opt, "%s", opt0);
        mvprintw(18, center_opt, "%s", opt1);
        mvprintw(21, center_opt, "%s", opt2);

        refresh();

        tasto = getch();
        switch(tasto) {
            case KEY_UP:
                selezione--;
                if(selezione < 0) selezione = 2;
                break;
            case KEY_DOWN:
                selezione++;
                if(selezione > 2) selezione = 0;
                break;
            case 10:
                return selezione;
        }
    }
}


void Menu::victory(WINDOW* win) {
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
    const char* msg2 = "Inserisci il tuo nome per aggiornare la classifica: ";
    int start_x_msg1 = (max_x - strlen(msg1)) / 2;
    int start_x_msg2 = (max_x - strlen(msg2)) / 2;

    mvwprintw(win, start_y + altezza_scritta + 2, start_x_msg1, "%s", msg1);
    mvwprintw(win, start_y + altezza_scritta + 6, start_x_msg2, "%s", msg2);
    wrefresh(win);

    timeout(-1); // Ferma l'esecuzione all'infinito in attesa di input
    getch();     // Cattura il tasto per poi chiudere
}

void Menu::lost(WINDOW* win, Giocatore* player) {
	flushinp();
    timeout(-1);
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
