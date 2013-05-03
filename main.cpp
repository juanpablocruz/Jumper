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

#include <vector>
#include <string>
#include <math.h>
#include "objects.h"
#include "text.h"

#ifndef MAPWIDTH
#define MAPWIDTH 1600
#endif

enum Keys{UP, DOWN, LEFT, RIGHT, SPACE};
bool keys[5] = {false, false, false, false, false};

Character *hero, *heroine;


int main(void){
	bool done = false;
	bool gameStarted = false;
	bool redraw = true;
	bool drawLine = false;
	const int FPS = 20;
	bool boundary = false;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	vector<ALLEGRO_BITMAP*> bg;
	ALLEGRO_BITMAP *ground = NULL;

	if(!al_init())
		return -1;
	display = al_create_display(WIDTH,HEIGHT);
	al_set_window_title(display,"Jumper");

	if(!display)
		return -1;

	al_init_primitives_addon();
	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon();
	al_init_ttf_addon();

	for (int i = 0; i < 1+MAPWIDTH; i++)
	{
		for (int j = 0; j < 1+(HEIGHT/36); j++)
		{
			Mapa[i][j] = -2;
		}
	}
	for (int i = 0; i < 1+MAPWIDTH; i++)
	{
		Mapa[i][(HEIGHT/36)] = -1;
	}
	Mapa[300/18][(HEIGHT-96)/36] = 0;
	Mapa[20][(HEIGHT/36)] = -2;
	Mapa[21][(HEIGHT/36)] = -2;
	Mapa[22][(HEIGHT/36)] = -2;

	resources.push_back(al_load_bitmap("images/tiles/wall.png"));
	bg.push_back(al_load_bitmap("images/bg/bg.png"));
	bg.push_back(al_load_bitmap("images/bg/cave.png"));

	hero = new Character(100,HEIGHT-80,muros);
	resources.push_back(al_load_bitmap("images/characters/hero.png"));
	hero->assignResource(resources.size()-1);
	hero->assignMap(Mapa);

	heroine = new Character(700,HEIGHT-80,muros);
	resources.push_back(al_load_bitmap("images/characters/character.png"));
	heroine->assignResource(resources.size()-1);

	ground = al_load_bitmap("images/tiles/ground.png");

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	
	textList.push_back(new Text("fonts/hobbit.ttf", 42,"Welcome",200,150));
	textList[0]->createTimer(3);

	textList.push_back(new Text("fonts/arial.ttf", 14,"",200,150));
	textList[1]->active = false;
	

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(timer);
	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER){
			redraw = true;
			if(!hero->moving){
				hero->imgy = 0;
				hero->imgx = 0;
			}

			if(keys[LEFT]){
				hero->medio++;
				if(hero->medio%6==0){
					hero->imgx++;
					hero->medio = 0;
				}
				hero->imgy = 1;
				if((hero->x-WIDTH/2)>-hero->xSpeed && (hero->x-WIDTH/2) <= 0){
					if(hero->viewPoint>0){
						hero->viewPoint--;
					}
					else hero->move(-1);
				}
				else hero->move(-1);
			}
			if(keys[RIGHT]){
				hero->medio++;
				if(hero->medio%6==0){
					hero->imgx++;
					hero->medio = 0;
				}
				hero->imgy = 2;
				if((hero->x-WIDTH/2)>-hero->xSpeed && !boundary){
					//if(drawx==12)drawx=0;
					//else
					hero->viewPoint++;
				}
				else	hero->move(1);
			}
			hero->imgx =(hero->imgx)%(hero->COLS);
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
			done = true;
		}
		/*
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES ){
		}

		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
      	}*/

		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch(ev.keyboard.keycode){
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				hero->moving = true;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				hero->moving = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				hero->moving = true;
				break;
			case ALLEGRO_KEY_SPACE:
				hero->numJumps++;
				hero->jump();
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP){
			switch(ev.keyboard.keycode){
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				hero->moving = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				hero->moving = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				hero->moving = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}
		if(redraw && al_is_event_queue_empty(event_queue)){
			redraw = false;
			int drawing = (MAPWIDTH-(hero->viewPoint*10+WIDTH));
			if(drawing <= 0) boundary = true;
			else if(drawing>0) boundary = false;
			
			al_draw_bitmap_region(bg[1],hero->viewPoint*10,0,WIDTH,HEIGHT,0,0,0);

			//Draw ground		
			for (int i = hero->viewPoint; i < 1+hero->viewPoint+(WIDTH/36); i++)
			{
				for (int j = 0; j < 1+(HEIGHT/36); j++)
				{
					switch(Mapa[i][j]){
					case -1:
						al_draw_bitmap(ground,(i-hero->viewPoint)*36,j*36,0);
						break;
					case -2:
						break;
					default:
						al_draw_bitmap(resources[Mapa[i][j]],
							(i-hero->viewPoint)*36, // x to draw
							j*36,0);
						break;
					}
					//al_draw_textf(font12, al_map_rgb(255, 255, 255), (i-hero->viewPoint)*36+15,(j*36)+11, 0, "%d",Mapa[i][j]);
				}
			}

			for (unsigned int i=0;i<textList.size();i++){
				if(textList[i]->active){
					textList[i]->render();
				}
			}
			hero->update();
			for(unsigned int i=0;i<muros.size();i++){
				al_draw_bitmap(resources[muros[i]->sprite],muros[i]->x,muros[i]->y,0);
			}
			render(hero,resources);
			if(hero->x+hero->viewPoint >= 600){
				render(heroine,resources);
			}
			al_draw_textf(textList[1]->fuente, al_map_rgb(255, 255, 255), 205, 5, 0, "%d,",
				(MAPWIDTH-(hero->viewPoint*10+WIDTH)));
			al_draw_textf(textList[1]->fuente, al_map_rgb(255, 255, 255), 285, 5, 0, " %d",
				hero->Mapa[(int) (hero->x/18)+hero->viewPoint][(int) (hero->y/36)+1]);

			//al_draw_filled_rectangle((hero->x/18)+hero->viewPoint,(hero->y/36),(hero->x/18)+hero->viewPoint+32,(hero->y/36)+48,al_map_rgba(150,0,0,150));
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	for(unsigned int i=0;i<resources.size();i++){
		al_destroy_bitmap(resources[i]);
	};

	delete hero;
	delete heroine;

	for (unsigned int i=0;i<textList.size();i++)
		delete textList[i];
	for (unsigned int i=0;i<muros.size();i++)
		delete muros[i];
	for (unsigned int i=0;i<bg.size();i++)
		al_destroy_bitmap(bg[i]);
	al_destroy_bitmap(ground);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);						//destroy our display object

	return 0;
}