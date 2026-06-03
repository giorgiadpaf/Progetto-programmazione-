#ifndef CLASSIFICA_HPP
#define CLASSIFICA_HPP

#include <fstream>

struct Record {
    char nome[50];
    int punteggio;
};

class Classifica {
public:
    // Scrive un nuovo punteggio in fondo al file
    void salvaPunteggio(const char* nome, int punti);

    // Legge, ordina e mostra i migliori N giocatori
    void visualizzaTopN(int n);
};

#endif
