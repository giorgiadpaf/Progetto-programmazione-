#include <cstring>
#include "Menu.hpp"

int Menu::opzione() {
    int selezione = 0; 
    int tasto;

    while (true) {
        clear();
    
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
