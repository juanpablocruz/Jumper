#include "text.h"

Text::Text(char *font,int size,char *text,float x,float y){
	this->currTime = 0;
	this->fade = false;
	this->active = true;
	this->text = text;
	this->x = x;
	this->y = y;
	this->FPS=20;
	this->r = 255;
	this->g = 255;
	this->b = 255;
	this->a = 0;
	this->fuente=load_font(font,size);
}
ALLEGRO_FONT* Text::load_font(char *font,int size){
	return al_load_font(font,size,0);
}
Text::~Text(){
	al_destroy_font(this->fuente);
}

void Text::createTimer(int timer){
	this->fade = true;
	this->fadeTimmer = timer;
}

void Text::incrTimer(){
	this->currTime++;
	if((currTime%10)==0){
		this->a += 10;
		this->r-=a;
		this->g-=a;
		this->b-=a;
	}
	if((currTime%FPS)==0){
		this->fadeTimmer--;
		if(this->fadeTimmer == 0){
			this->active = false;
		}
	}
}
void Text::changeText(char *txt){
	this->text = txt;
}
void Text::render(){
	if(this->fade){
		this->incrTimer();
	}
	al_draw_textf(fuente, al_map_rgba(r, g, b,a), x, y, 0, text);
}