#ifdef _WIN32 
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#else
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#endif

#include "objects.h"

Character::Character(float x,float y,vector<Wall*> muros){
	this->x = x;
	this->y = y;
	this->moving = false;
	this->imgx = 0;
	this->imgy = 1;
	this->COLS = 4;
	this->ROWS = 4;
	this->onGround = true;
	this->g = 5;
	this->ySpeed = 0;
	this->xSpeed = 8;
	this->medio = 0;
	this->numJumps = 0;
	this->muros = muros;
	this->viewPoint = 0;
};

bool Character::checkCollide(){
	for(int i=0;i<muros.size();i++){
		if((x >= (muros[i]->x-muros[i]->width/2) && x <= (muros[i]->x+muros[i]->width/2))
		 && (y+46 >= (muros[i]->y-muros[i]->height/2) && y <= (muros[i]->y+muros[i]->height/2))){
		 	//if(!onGround)
			//	this->y = muros[i]->y-46;
			return true;
		}
	}
	return false;
}

bool Character::checkHorizontalCollide(){
	if(this->Mapa[(int) (x/18)+this->viewPoint][(int) y/36] == 0 
		|| this->Mapa[(int) (x/18)+this->viewPoint][(int) (y/36)-1] == 0
		|| this->Mapa[(int) (x/18)+this->viewPoint][(int) (y/36)+1] == 0)
		return true;
	return false;	
}
bool Character::checkVerticalCollide(){
	if(this->Mapa[(int)(x/18)][(int)(y/18)+1]==1)return true;
	return false;
}
void Character::assignResource(int id){
	this->sprite = id;
}

void Character::update(){
	if(!checkCollide() && this->y+82 <= HEIGHT)onGround=false;
	if(!onGround){		
		this->ySpeed += g; 
		this->y += ySpeed;
		if(checkCollide()){
			this->ySpeed = 0;
			this->onGround = true;
			this->numJumps = 0;
		}
		if(this->y+82 >= HEIGHT){
			this->onGround=true;
			this->y = HEIGHT-82;
			this->ySpeed = 0;
			this->numJumps = 0;
		}
	}
}

void Character::move(int i){

	this->sentido = i;
	this->x += xSpeed*i;
	if(checkHorizontalCollide()){
		this->x -= xSpeed*i;
	}
	switch(i){
	case 1:
		if(this->x+32 >= WIDTH)this->x = WIDTH-32;
		break;
	case -1:
		if(this->x <= 0)this->x = 0;
		break;
	}
}

void Character::jump(){
	if(numJumps<= 2){
		this->onGround = false;
		this->ySpeed = -35;
	}
}

void render(Character *c,vector<ALLEGRO_BITMAP*> resources){
	al_draw_bitmap_region(resources[c->sprite],c->imgx*32,c->imgy*48,32,48,c->x,c->y,0);
}

Wall::Wall(float x,float y, float w, float h, bool ground){
	this->x =x;
	this->y = y;
	this->width = w;
	this->height = h;
	this->ground = ground;
}

Character::~Character(){
}
Wall::~Wall(){
}

void Character::assignMap(int (*M)[(HEIGHT/36)+1]){
	for(int i=0;i<1+(MAPWIDTH);i++){
		for(int j=0;j<(HEIGHT/36)+1;j++){
			this->Mapa[i][j] = M[i][j];
		}
	}
}