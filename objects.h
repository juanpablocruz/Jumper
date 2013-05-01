#ifndef OBJECTS_H
#define OBJECTS_H

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <vector>

#define PI 3.14159265

using namespace std;

static vector<ALLEGRO_BITMAP*> resources;

static const int WIDTH = 800;
static const int HEIGHT = 600;

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
};



static vector<Wall*> muros;

void render(Character *c,vector<ALLEGRO_BITMAP*> resources);
#endif