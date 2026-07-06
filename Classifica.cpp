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

void Classifica::visualizzaTopN() {
    timeout(-1);
    flushinp();
    clear();
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    box(stdscr, 0, 0);

    const char* titolo_n = "IMPOSTAZIONI CLASSIFICA";
    const char* prompt_n = "Quanti campioni vuoi visualizzare?";

    mvprintw(max_y / 2 - 4, (max_x - strlen(titolo_n)) / 2, "%s", titolo_n);
    mvprintw(max_y / 2 - 2, (max_x - strlen(prompt_n)) / 2, "%s", prompt_n);
    echo();
    curs_set(1);

    int n_scelto = 0;
    move(max_y / 2, max_x / 2 - 2);
    scanw("%d", &n_scelto);
    noecho();
    curs_set(0);
    if (n_scelto <= 0) n_scelto = 5;
    if (n_scelto > 100) n_scelto = 100;
    clear();
    box(stdscr, 0, 0);

    const char* scritta_arcade[6] = {
        "████████╗ ██████╗ ██████╗     ██████╗ ██╗      █████╗ ██╗   ██╗███████╗██████╗ ███████╗",
        "╚══██╔══╝██╔═══██╗██╔══██╗    ██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██╔════╝██╔══██╗██╔════╝",
        "   ██║   ██║   ██║██████╔╝    ██████╔╝██║     ███████║ ╚████╔╝ █████╗  ██████╔╝███████╗",
        "   ██║   ██║   ██║██╔═══╝     ██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██╔══╝  ██╔══██╗╚════██║",
        "   ██║   ╚██████╔╝██║         ██║     ███████╗██║  ██║   ██║   ███████╗██║  ██║███████║",
        "   ╚═╝    ╚═════╝ ╚═╝         ╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚══════╝"
    };

    int start_y = 3;
    int start_x = (max_x - 90) / 2;

    if (max_x >= 90) {
        for (int i = 0; i < 6; i++) {
            mvprintw(start_y + i, start_x, "%s", scritta_arcade[i]);
        }
        start_y += 8;
    } else {
        mvprintw(start_y, (max_x - 12) / 2, "=== TOP PLAYERS ===");
        start_y += 3;
    }

    ifstream file;
    file.open("classifica.txt");
    if (file.is_open()) {
        char nomeLetto[50];
        int puntiLetti;
        int riga = 0;
        char nomeTroncato[21];
        while (riga < n_scelto && file >> nomeLetto >> puntiLetti) {
            strncpy(nomeTroncato, nomeLetto, 20);
            nomeTroncato[20] = '\0';
            char rigaTesto[100];
            sprintf(rigaTesto, "%2d. %-20s  %6d", riga + 1, nomeTroncato, puntiLetti);
            int x_centrata = (max_x - strlen(rigaTesto)) / 2;
            mvprintw(start_y + riga, x_centrata, "%s", rigaTesto);
            riga++;
        }
        file.close();
        if (riga == 0) {
            mvprintw(max_y / 2, (max_x - 22) / 2, "NESSUN RECORD PRESENTE");
        }
    }

    char msgEsci[] = "Premi un tasto per tornare al menu...";
    mvprintw(LINES - 4, (COLS - strlen(msgEsci)) / 2, "%s", msgEsci);
    refresh();
    timeout(-1); 
    getch();
    timeout(50); 
}
