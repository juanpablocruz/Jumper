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

using namespace std;

static vector<ALLEGRO_BITMAP*> resources;

static const int WIDTH = 800;
static const int HEIGHT = 500;

static int Mapa[(WIDTH/18)+1][(HEIGHT/36)+1];

class Wall{
public:
	float width,height,x,y,sprite;
	bool ground,collide;

	Wall(float x,float y, float w, float h, bool ground);
	~Wall();
};

class Character{
public:
	int sprite,numJumps;
	int COLS,ROWS,imgx,imgy,sentido,medio;
	float x,y,g,xSpeed,ySpeed;
	bool moving,onGround;
	vector<Wall*> muros;

	Character(float x,float y,vector<Wall*> muros);
	~Character();

	void move(int i);
	void jump();
	void assignResource(int id);
	void update();
	bool checkCollide();
	bool checkHorizontalCollide();
	bool checkVerticalCollide();
};



static vector<Wall*> muros;

void render(Character *c,vector<ALLEGRO_BITMAP*> resources);
#endif