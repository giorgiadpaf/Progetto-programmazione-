#ifndef CLASSIFICA_HPP
#define CLASSIFICA_HPP

struct Record {
    char nome[50];
    int punteggio;
};

class Classifica {
public:
    void salvaPunteggio(char* nome, int punti);
    void visualizzaTopN();
};

#endif
