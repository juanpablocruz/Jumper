#ifndef MAP_H
#define MAP_H

#ifdef _WIN32 
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#else
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#endif

#include "variables.h"
#include <vector>

using namespace std;

class Event{
public:
	int x_start,y_start,t_wait, i;
	vector<int> path;

	Event(int x, int y);
	void wait_time(int t);
	bool sleep_time();
	int move_to(int x_h, int y_h, int x_speed);
	void addStep(int x);

};

class Map{
public:
	int id_bg, mapa[1+(MAPWIDTH)][MAPHEIGHT+1];
	vector<Event*> eventos;

	Map(int b);
	~Map();
	int checkEvents(int x, int y);
	void createEvent(int x,int y);
	void copyMap(int (*M)[MAPHEIGHT+1]);
};
static vector<Map*> mapas;
static vector<ALLEGRO_BITMAP*> bg;

void addMap(vector<Map*> &mapas,vector<ALLEGRO_BITMAP*> &bg,const char* m);

#endif