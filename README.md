Bomberman ASCII - Progetto di Programmazione

Repository del progetto "Bomberman" per l'esame del corso di "Programmazione" AA. 2025-2026 del corso triennale di Informatica presso l'Università di Bologna. 
Il software è un'implementazione del classico videogioco arcade, sviluppata interamente in C++ con l'ausilio della libreria grafica ncurses per terminali Debian/Linux.
Lo scopo di Bomberman è eliminare gli avversari piazzando bombe su una griglia. Un livello è completo quando vengono eliminati tutti i nemici. 
Per vincera bisogna completare tutti i 5 livelli. Muoviti nei corridoi, distruggi i muri di mattoni, raccogli i potenziamenti nascosti e trova le porte per passare di livello. 
👥 Sviluppatori

    Componente #1: Giorgia Dal Prà - Gestione Entità (Giocatore/Nemici), Punteggio e Classifica.

    Componente #2: [Nome Compagno] - Gestione Mappa, Livelli e grafica.

    Componente #3: [Nome Compagno] - Gestione Bombe, Item, Menu, Tempo.

Requisiti e Compilazione

Il progetto è stato sviluppato per ambiente Debian. Per compilare il gioco è necessario il compilatore g++ e la libreria ncurses.
Installazione dipendenze:

sudo apt update
sudo apt install build-essential libncursesw5-dev

Compilazione:
Utilizzare il Makefile incluso o il comando manuale:

g++ *.cpp -lncursesw -o bomberman

(Nota: l'uso di -lncursesw garantisce il supporto ai caratteri speciali del terminale).
Esecuzione:

./bomberman

🎮 Comandi di Gioco

    WASD / Frecce direzionali: Movimento del giocatore.

    Barra Spaziatrice: Piazzamento bomba.

    Q: Uscita rapida dalla partita.
