#include "Tempo.hpp"

Tempo::Tempo(int secondi) {
    durataMaxSecondi = secondi;
    tempoInizio = time(NULL);
}

void Tempo::start() {
    tempoInizio = time(NULL);
}

int Tempo::getTempoRimasto() const {
    int tempoTrascorso = difftime(time(NULL), tempoInizio);
    int tempoRimasto = durataMaxSecondi - tempoTrascorso;
    
    //evita che il tempo scenda sotto zero
    if (tempoRimasto < 0) {
        return 0;
    }
    return tempoRimasto;
}

bool Tempo::isScaduto() const {
    return getTempoRimasto() <= 0;
}

int Tempo::getMinuti() const {
    return getTempoRimasto() / 60;
}

int Tempo::getSecondi() const {
    return getTempoRimasto() % 60;
}
