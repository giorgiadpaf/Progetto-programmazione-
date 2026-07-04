#pragma once
#include <cstddef>
#include <ncurses.h>
#include <cstdlib>
#include "Giocatore.hpp"
#include "Nemico.hpp"

struct enemylist{
    Nemico *enemy;
    enemylist* next;
};

class Map{
private:
    WINDOW* window;
    Map* prec;
    Map* next;
    char logicmap[20][41];
    int xPspawn;
    int yPspawn;
    int xD;
    int yD;
    enemylist* enemyL;

public:
    Map(Map* prec_ = NULL, Map* next_ = NULL, char logicmap_ [][41] = NULL, int xPspawn_ = 0, int yPspawn_ = 0, WINDOW* window_ = NULL, enemylist* enemyL_ = NULL);

    char whatsthere(int x, int y); //Ritorna il carattere presente nella logicmap della mappa nel punto (x,y)

    enemylist* _enemylist(); //ritorna un puntatore alla enemylist della mappa
    int _xPspawn();
    int _yPspawn();
    void printonscr(); //disegna a schermo a partire dalla logicmap della mappa

    void addenemy(int y, int x, int t); //aggiunge un nemico in testa alla enemylist della mappa

    bool isempty(int y, int x); //ritorna true se in quelle coordinate c'è una porta o se non c'è nulla

    void addmapinq(Map* newmap);

    Map* nextlvl(); //ritornano il puntatore next o prec della mappa
    Map* preclvl();


    //ritornano true se il giocatore è su una porta
    bool isonN(Giocatore& player);
    bool isonP(Giocatore& player);

    void setTile(int y, int x, char c);//per eliminare i muri
};
