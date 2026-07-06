#ifndef TEMPO_HPP
#define TEMPO_HPP
#include <ctime>

class Tempo {
private:
    time_t tempoInizio;
    int durataMaxSecondi;

public:
    //costruttore imposta la durata massima
    Tempo(int secondi);

    //fa partire timer
    void start();

    //restituisce secondi totali rimanenti
    int getTempoRimasto() const;

    //true se il tempo è finito
    bool isScaduto() const;

    //funzioni per minutio e secondi
    int getMinuti() const;
    int getSecondi() const;

    void aggiungiTempo(int secondi);
};

#endif
