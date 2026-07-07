#include <cstddef>
#include <ncurses.h>
#include <ctime>
#include "Map.hpp"
#include "Nemico.hpp"
#include "NemicoSparante.hpp"
using namespace std;

Map::Map(Map* prec_, Map* next_,char logicmap_ [][81], int xPspawn_, int yPspawn_, WINDOW* window_, enemylist* enemyL_){
    enemyL = enemyL_;
    window = window_;
    prec = prec_;
    next = next_;

    xPspawn = xPspawn_;
    yPspawn = yPspawn_;

    for(int i = 0; i < 20; i++){
        for(int k = 0; k <= 80; k++){
            logicmap[i][k] = logicmap_[i][k];
        }
    }
}

void Map::setPspawn(int y, int x){xPspawn = x; yPspawn = y;}
char Map::whatsthere(int y,int x){return logicmap[y][x];}
int Map::_xPspawn(){return xPspawn;}
int Map::_yPspawn(){return yPspawn;}
enemylist* Map::_enemylist(){return enemyL;}

void Map::printonscr() {
    if (logicmap == NULL) return;

    for (int row = 0; row < 20; row++) {
        for (int col = 0; col < 80; col++) {
            char cell = logicmap[row][col];

            if(cell == 'N' || cell == 'P'){
                mvwprintw(window, row, col, "%s", "⊞");
            }else if (cell == '#') {
                mvwprintw(window, row, col, "%s", "█");
            }else if (cell == '*' || cell == '$' || cell == '%' || cell == 'n') {
                mvwprintw(window, row, col, "%s", "▒");
            }else if (cell == '^') {
    		    attron(COLOR_PAIR(2));
    		    mvwprintw(window, row, col, "%s", "?"); //item: aumento raggio
    		    attroff(COLOR_PAIR(2));
    	    }else if (cell == '&') {
    		    attron(COLOR_PAIR(3));
    		    mvwprintw(window, row, col, "%s", "+");//item: tempo extra
    		    attroff(COLOR_PAIR(3));
    	    }else {
                mvwprintw(window, row, col, "%c", ' ');
            }
        }
    }

    wrefresh(window);
}
bool Map::isempty(int y, int x){
    return logicmap[y][x] == ' ' || logicmap[y][x] == 'N' ||logicmap[y][x] == 'P' || logicmap[y][x] == '.' ||
	    logicmap[y][x] == '^' || logicmap[y][x] == '&';
}

void Map::addmapinq(Map* newmap){
    if (newmap == NULL) return;

    delete next;
    next = newmap;
    next->prec = this;
}

Map* Map::nextlvl(){
    return next;
}

Map* Map::preclvl(){
    return prec;
}


bool Map::isonN(Giocatore& player){
    return logicmap[player.getY()][player.getX()] == 'N';
}

bool Map::isonP(Giocatore& player){
    return logicmap[player.getY()][player.getX()] == 'P';
}

void Map::addenemy(int y, int x, int t){
    if (!isempty(y, x)) return;
    enemylist* tmp = new enemylist;
    if(t < 3){
        tmp->enemy = new Nemico(y,x, this, t);
        tmp->next = enemyL;
        enemyL = tmp;
    }else{
        tmp->enemy = new NemicoSparante(y,x, this);
        tmp->next = enemyL;
        enemyL = tmp;
    }
}

//per esplosione muri
void Map::setTile(int y, int x, char c){
	logicmap[y][x]=c;
}
