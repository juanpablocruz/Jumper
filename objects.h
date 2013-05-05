#ifndef OBJECTS_H
#define OBJECTS_H

#ifdef _WIN32 
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#else
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#endif

#include <vector>
#include "Map.h"
#include "variables.h"

#define PI 3.14159265

using namespace std;

static vector<ALLEGRO_BITMAP*> resources;

class Character{
public:
	int sprite,numJumps, viewPoint,sw,sh;
	int COLS,ROWS,imgx,imgy,sentido,medio;
	float x,y,g,xSpeed,ySpeed;
	bool moving,onGround,locked;
	Map *curr_map;
	int currentBg,bgNum;
	ALLEGRO_SAMPLE *jumpSound,*drownSound,*endSound,*winSound;


	Character(float x,float y);
	~Character();

	void setDim(int w,int h);
	void move(int i);
	void jump();
	void assignResource(int id);
	void update();
	bool checkHorizontalCollide();
	bool checkVerticalCollide();

	void assignMap(Map *M);
};


class NPC : public Character{
public:
	int desfasex,id_mapa;
	bool active;

	NPC(float x,float y, int df, int id_m);
	~NPC();
};

class Hero : public Character{
public:
	std::vector<NPC *> npcs;

	bool checkCollide(int i);
	Hero(float x,float y);
	~Hero();
};



void render(Hero *c,vector<ALLEGRO_BITMAP*> rc);
void render(NPC *c,int vp,vector<ALLEGRO_BITMAP*> rc);
#endif