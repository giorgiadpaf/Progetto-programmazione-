#ifndef ITEM_HPP
#define ITEM_HPP

#include <ctime>

class Item {
private:
    bool attivo;
    time_t tempoInizio;
    int durataSecondi;

public:
    Item();

    //attiva effetto item e fa partire il timer
    void raccogli(int secondi);

    //controlla se il tempo è scaduto
    void aggiorna();

    //true se l'item e' attivo
    bool isAttivo() const;
};

#endif
