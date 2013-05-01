#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <vector>
#include <string>
#include "objects.h"

enum Keys{UP, DOWN, LEFT, RIGHT, SPACE};
bool keys[5] = {false, false, false, false, false};
ALLEGRO_FONT *font12 = NULL;

Character *hero;


int main(void){
	bool done = false;
	bool gameStarted = false;
	bool redraw = true;
	bool drawLine = false;
	const int FPS = 20;


	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

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

	muros.push_back(new Wall(300,HEIGHT-60,36,36,true));
	resources.push_back(al_load_bitmap("wall.png"));
	muros[muros.size()-1]->sprite = resources.size()-1;
	
	hero = new Character(100,HEIGHT-50,muros);
	resources.push_back(al_load_bitmap("character.png"));
	hero->assignResource(resources.size()-1);

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
			if(keys[LEFT]){
				hero->medio++;
				if(hero->medio%6==0){
					hero->imgx++;
					hero->medio = 0;
				}
				hero->imgy = 1;
				hero->move(-1);
			}
			if(keys[RIGHT]){
				hero->medio++;
				if(hero->medio%6==0){
					hero->imgx++;
					hero->medio = 0;
				}
				hero->imgy = 2;
				hero->move(1);
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
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
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
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}
		if(redraw && al_is_event_queue_empty(event_queue)){
			redraw = false;
			hero->update();
			for(int i=0;i<muros.size();i++){
				al_draw_bitmap(resources[muros[i]->sprite],muros[i]->x,muros[i]->y,0);
			}
			render(hero,resources);
			al_draw_textf(font12, al_map_rgb(255, 255, 255), 205, 5, 0, "Muro x: %.2f Muro y: %.2f",muros[0]->x,muros[0]->y);
			al_draw_textf(font12, al_map_rgb(255, 255, 255), 205, 20, 0, "Hero x: %.2f Hero y: %.2f",hero->x,hero->y);
			if(hero->checkCollide())
				al_draw_textf(font12, al_map_rgb(255, 255, 255), 205, 35, 0, "Choca");
			else
				al_draw_textf(font12, al_map_rgb(255, 255, 255), 205, 35, 0, "No Choca");
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	for(int i=0;i<resources.size();i++){
		al_destroy_bitmap(resources[i]);
	};
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_font(font12);
	al_destroy_display(display);						//destroy our display object

	return 0;
}