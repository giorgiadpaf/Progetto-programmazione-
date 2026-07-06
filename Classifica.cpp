#include "Classifica.hpp"
#include <ncurses.h>
#include <fstream>
#include <cstring>

using namespace std;

void Classifica::salvaPunteggio(char* nome, int punti) {
    Record elenco[100];
    int count = 0;
    ifstream fileLettura;
    fileLettura.open("classifica.txt");
    if (fileLettura.is_open()) {
        // Legge finché il file non finisce o arriviamo a 99 record
        while (count < 99 && fileLettura >> elenco[count].nome >> elenco[count].punti) {
            count++;
        }
        fileLettura.close();
    }
    strncpy(elenco[count].nome, nome, 49);
    elenco[count].nome[49] = '\0';
    elenco[count].punti = punti;
    count++;
    for (int i = 1; i < count; i++) {
        Record chiave = elenco[i];
        int j = i - 1;
        while (j >= 0 && elenco[j].punti < chiave.punti) {
            elenco[j + 1] = elenco[j];
            j = j - 1;
        }
        elenco[j + 1] = chiave;
    }
    ofstream fileScrittura;
    fileScrittura.open("classifica.txt"); 
    if (fileScrittura.is_open()) {
        for (int i = 0; i < count; i++) {
            fileScrittura << elenco[i].nome << " " << elenco[i].punti << endl;
        }
        fileScrittura.close();
    }
}

void Classifica::visualizzaTopN(int n) {
    ifstream file;
    file.open("classifica.txt");

    clear();
    char titolo[] = "=== TOP PLAYERS ===";
    mvprintw(LINES / 4, (COLS - strlen(titolo)) / 2, "%s", titolo);
    if (file.is_open()) {
        char nomeLetto[50];
        int puntiLetti;
        int riga = 0;
        while (riga < n && file >> nomeLetto >> puntiLetti) {
            mvprintw(LINES / 4 + 3 + riga, (COLS - 20) / 2, "%d. %s : %d", riga + 1, nomeLetto, puntiLetti);
            riga++;
        }
        file.close();
        if (riga == 0) {
            mvprintw(LINES / 2, (COLS - 22) / 2, "Nessun record trovato.");
        }
    } else {
        mvprintw(LINES / 2, (COLS - 25) / 2, "Impossibile aprire il file.");
    }

    char msgEsci[] = "Premi un tasto per tornare al menu...";
    mvprintw(LINES - 4, (COLS - strlen(msgEsci)) / 2, "%s", msgEsci);
    refresh();
    timeout(-1); 
    getch();
    timeout(50); 
}
