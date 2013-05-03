#ifndef TEXT_H
#define TEXT_H

#ifdef _WIN32 
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#else
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#endif

#include <vector>

class Text{
public:
	bool fade,active;
	float x,y;
	ALLEGRO_FONT *fuente;
	char *text;
	int FPS,currTime,fadeTimmer;
	int r,g,b,a;

	Text(char *font,int size,char *text,float x,float y);
	ALLEGRO_FONT* load_font(char *font,int size);
	void createTimer(int timer);
	void incrTimer();
	void render();
	void changeText(char *txt);
	~Text();
};

static std::vector<Text*> textList;
#endif