#include "Item.hpp"

Item::Item() {
    attivo = false;
    durataSecondi = 0;
}

void Item::raccogli(int secondi) {
    attivo = true;
    durataSecondi = secondi;
    tempoInizio = time(NULL);
}

void Item::aggiorna() {
    if (attivo) {
        //disattiva item
        if (difftime(time(NULL), tempoInizio) >= durataSecondi) {
            attivo = false;
        }
    }
}

bool Item::isAttivo() const {
    return attivo;
}
