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

#define PI 3.14159265

#ifndef MAPWIDTH
#define MAPWIDTH 1600
#endif

using namespace std;

static vector<ALLEGRO_BITMAP*> resources;

static const int WIDTH = 800;
static const int HEIGHT = 500;

static int Mapa[1+(MAPWIDTH)][(HEIGHT/36)+1];

class Character{
public:
	int sprite,numJumps, viewPoint,sw,sh;
	int COLS,ROWS,imgx,imgy,sentido,medio;
	float x,y,g,xSpeed,ySpeed;
	bool moving,onGround,locked;
	int Mapa[1+(MAPWIDTH)][(HEIGHT/36)+1];
	int currentBg,bgNum;
	ALLEGRO_SAMPLE *jumpSound,*drownSound,*endSound,*winSound;


	Character(float x,float y);
	~Character();

	void setDim(int w,int h);
	void move(int i);
	void jump();
	void assignResource(int id);
	void update();
	bool checkCollide();
	bool checkHorizontalCollide();
	bool checkVerticalCollide();
	void assignMap(int (*M)[(HEIGHT/36)+1]);
};


class NPC : public Character{
public:
	int desfasex;

	NPC(float x,float y, int df);
	~NPC();
};

class Hero : public Character{
public:
	std::vector<NPC *> npcs;

	Hero(float x,float y);
	~Hero();
};



void render(Hero *c,vector<ALLEGRO_BITMAP*> resources);
void render(NPC *c,int vp,vector<ALLEGRO_BITMAP*> resources);
#endif