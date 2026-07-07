#ifndef MENU_HPP
#define MENU_HPP
#include "Giocatore.hpp"
#include <cstdint>
#include <ncurses.h>

class Menu {
public:
	int opzione(); //le opzioni del menu sono 3
	void victory(WINDOW* win);
	void lost(WINDOW* win, Giocatore* player);
};

#endif
