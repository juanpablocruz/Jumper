#ifdef _WIN32 
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#else
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#endif

#include "objects.h"

Character::Character(float x,float y){
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
	this->viewPoint = 0;
	this->locked = false;
	this->currentBg = 0;
	this->jumpSound = al_load_sample("sound/jump.wav");
	this->drownSound = al_load_sample("sound/drown.wav");
	this->endSound = al_load_sample("sound/end.wav");
	this->winSound = al_load_sample("sound/win.wav");
};

bool Character::checkCollide(){
	return false;
}

bool Character::checkHorizontalCollide(){
	if(this->Mapa[(int) (x/32)+viewPoint+1][(int) (y/36)] == 0 
		|| this->Mapa[(int) (x/32)+this->viewPoint-1][(int) (y/36)] == 0
		|| this->Mapa[(int) (x/32)+this->viewPoint+1][(int) (y/36)+1] == 0)
		return true;
	return false;	
}
bool Character::checkVerticalCollide(){
	if(this->Mapa[(int) (x/32)+viewPoint][(int) (y/36)+2] == 0 ||
		this->Mapa[(int) (x/32)+viewPoint][(int) (y/36)+2]== -1)return true;
	else if (this->Mapa[(int) (x/32)+viewPoint][(int) (y/36)+2] == -3)return false;
	return false;
}
void Character::assignResource(int id){
	this->sprite = id;
}

void Character::update(){
	if(!locked){
	if(this->x+this->viewPoint >=600)locked = true;
	else locked = false;
	if(!checkVerticalCollide())onGround=false;
	if(!onGround){		
		this->ySpeed += g; 
		this->y += ySpeed;
		if(checkVerticalCollide()){
			this->ySpeed = 0;
			this->onGround = true;
			this->numJumps = 0;
		}
		if((int)this->y >= HEIGHT){
			this->x =30;
			this->y = HEIGHT-(32+49);
			this->viewPoint = 0;
			this->onGround = true;
			this->ySpeed = 0;
			this->numJumps = 0;
			al_play_sample(this->drownSound, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		}
	}
	}
	else{
		if((this->x+xSpeed)>=WIDTH-32){
			al_play_sample(this->winSound, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
			this->locked = false;
			this->x = 30;
			this->y = HEIGHT-78;
			this->currentBg=(++this->currentBg)%this->bgNum;
			this->viewPoint = 0;

		}else{
			this->x +=xSpeed;
			this->medio++;
			if(this->medio%6==0){
				this->imgx++;
				this->medio = 0;
			}
			this->imgx =(this->imgx)%(this->COLS);
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

void Character::setDim(int w,int h){
	this->sw = w;
	this->sh = h;
}

void Character::jump(){
	if(numJumps<= 2){
		al_play_sample(this->jumpSound, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
		this->onGround = false;
		switch(numJumps){
		case 1:
			this->ySpeed = -35;
			break;
		case 2:
			this->ySpeed = -20;
			break;
		}

	}
}

void render(Hero *c,vector<ALLEGRO_BITMAP*> resources){
	al_draw_bitmap_region(resources[c->sprite],c->imgx*c->sw,c->imgy*c->sh,c->sw,c->sh,c->x,c->y,0);
}
void render(NPC *c,int vp,vector<ALLEGRO_BITMAP*> resources){
	al_draw_bitmap_region(resources[c->sprite],0,0,
					c->sw,c->sh,c->x-(32*vp),c->y,0);
}


Character::~Character(){
	al_destroy_sample(jumpSound);
	al_destroy_sample(endSound);
	al_destroy_sample(winSound);
	al_destroy_sample(drownSound);
}


void Character::assignMap(int (*M)[(HEIGHT/36)+1]){
	for(int i=0;i<1+(MAPWIDTH);i++){
		for(int j=0;j<(HEIGHT/36)+1;j++){
			this->Mapa[i][j] = M[i][j];
		}
	}
}

Hero::Hero(float x,float y):Character(x,y){
	
}

NPC::NPC(float x,float y, int df):Character(x,y){
	this->desfasex = df;
}

Hero::~Hero(){
}
NPC::~NPC(){
}