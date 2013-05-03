#ifndef OBJECTS_H
#define OBJECTS_H

#ifdef _WIN32 
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#else
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
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

class Wall{
public:
	float width,height,x,y,sprite;
	bool ground,collide;

	Wall(float x,float y, float w, float h, bool ground);
	~Wall();
};

class Character{
public:
	int sprite,numJumps, viewPoint,sw,sh;
	int COLS,ROWS,imgx,imgy,sentido,medio;
	float x,y,g,xSpeed,ySpeed;
	bool moving,onGround,locked;
	vector<Wall*> muros;
	int Mapa[1+(MAPWIDTH)][(HEIGHT/36)+1];
	int currentBg;


	Character(float x,float y,vector<Wall*> muros);
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



static vector<Wall*> muros;

void render(Character *c,vector<ALLEGRO_BITMAP*> resources);
#endif