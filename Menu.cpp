#include <cstring>
#include "Menu.hpp"

int Menu::opzione() {
    int selezione = 0; //0 = GIOCA, 1 = CLASSIFICA, 2 = ESCI
    int tasto;

    while (true) {
        clear();
	
	//definisco le scritte
        const char* titolo = "--- BOMBERMAN ---";
	const char* opt0   = (selezione == 0) ? "> GIOCA"      : "  GIOCA";
	const char* opt1   = (selezione == 1) ? "> CLASSIFICA" : "  CLASSIFICA";
	const char* opt2   = (selezione == 2) ? "> ESCI"       : "  ESCI";
 
	//variabile per il centro del titolo
	int center= (COLS - strlen(titolo)) /2; //COLS=lunghezza massima colonne
	
	//stampo il titolo
	mvprintw(8, center, "%s", titolo);

	//stampo le opzioni
	mvprintw(15, center+1, "%s", opt0);
	mvprintw(16, center+1, "%s", opt1);
	mvprintw(17, center+1, "%s", opt2);

	refresh();
        
	//logica per "scorrere" le opzioni
        tasto = getch();
        switch(tasto) {
            case KEY_UP:
		    selezione--;
		    if(selezione<0) selezione = 2; //se andiamo sopra GIOCA, va in fondo a ESCI
		    break;
            case KEY_DOWN:
                selezione++;
                if(selezione>2) selezione = 0; //se andiamo sotto a ESCI, torna sopra su GIOCA
		break;
            case 10: //10=Invio/Enter
		return selezione;
        }
    }
}
