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

enum Keys{UP, DOWN, LEFT, RIGHT, SPACE};
bool keys[5] = {false, false, false, false, false};
ALLEGRO_FONT *font12 = NULL;

Character *hero;
int drawx, drawy;


int main(void){
	bool done = false;
	bool gameStarted = false;
	bool redraw = true;
	bool drawLine = false;
	const int FPS = 20;
	drawy=0;
	drawx=0;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
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
	
	for (int i = 0; i < 1+(WIDTH/18); i++)
	{
		for (int j = 0; j < 1+(HEIGHT/36); j++)
		{
			Mapa[i][j] = -2;
		}
	}
	for (int i = 0; i < 1+(WIDTH/18); i++)
	{
		Mapa[i][(HEIGHT/36)] = -1;
	}
	Mapa[300/18][(HEIGHT-96)/36] = 0;
	/*
	muros.push_back(new Wall(300,HEIGHT-96,36,36,true));*/
	resources.push_back(al_load_bitmap("wall.png"));/*
	muros[muros.size()-1]->sprite = resources.size()-1;

	muros.push_back(new Wall(350,HEIGHT-120,36,36,true));
	muros[muros.size()-1]->sprite = resources.size()-1;

	muros.push_back(new Wall(390,HEIGHT-155,36,36,true));
	muros[muros.size()-1]->sprite = resources.size()-1;
	muros.push_back(new Wall(426,HEIGHT-155,36,36,true));
	muros[muros.size()-1]->sprite = resources.size()-1;
	muros.push_back(new Wall(462,HEIGHT-155,36,36,true));
	muros[muros.size()-1]->sprite = resources.size()-1;
	*/
	hero = new Character(100,HEIGHT-86,muros);
	resources.push_back(al_load_bitmap("character.png"));
	hero->assignResource(resources.size()-1);

	ground = al_load_bitmap("ground.png");

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	font12 = al_load_font("arial.ttf", 12, 0);

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
				if((hero->x-WIDTH/2)>-hero->xSpeed){
					if(drawx>0){
						drawx--;
					}
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
				if((hero->x-WIDTH/2)>-hero->xSpeed){
					if(drawx==13)drawx=0;
					else
					drawx++;
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
			
			//Draw ground		
			for (int i = drawy; i < 1+drawy+(WIDTH/18); i++)
			{
				for (int j = drawx; j < 1+drawx+(HEIGHT/36); j++)
				{
					if(Mapa[i][j]==-1)al_draw_bitmap(ground,i*36,j*36,0);
					else if(Mapa[i][j]!=-2)al_draw_bitmap(resources[Mapa[i][j]],(i-drawx)*36,(j)*36,0);

				}
			}
	 
			hero->update();
			for(int i=0;i<muros.size();i++){
				al_draw_bitmap(resources[muros[i]->sprite],muros[i]->x,muros[i]->y,0);
			}
			render(hero,resources);
			al_draw_textf(font12, al_map_rgb(255, 255, 255), 205, 5, 0, "herox: %d",Mapa[(int)hero->x/36][(int)hero->y/36]);
			al_flip_display();
			al_clear_to_color(al_map_rgb(100,100,250));
		}
	}
	for(int i=0;i<resources.size();i++){
		al_destroy_bitmap(resources[i]);
	};
	al_destroy_bitmap(ground);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_font(font12);
	al_destroy_display(display);						//destroy our display object

	return 0;
}