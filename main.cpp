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

#ifndef  ALLEGRO_STATICLINK
#define ALLEGRO_STATICLINK
#endif

#include <vector>
#include <string>
#include <math.h>
#include "objects.h"
#include "text.h"
#include "Map.h"
#include "variables.h"


enum Keys{UP, DOWN, LEFT, RIGHT, SPACE};
bool keys[5] = {false, false, false, false, false};

Hero *hero;
std::vector<NPC*> npc;


//ALLEGRO_SAMPLE_INSTANCE *songInstance = NULL;

int main(void){
	bool done = false;
	bool gameStarted = false;
	bool redraw = true;
	bool drawLine = false;
	const int FPS = 20;
	bool boundary = false;
	int curr_water = 0;
	int fps_counter = 0;
	int cont_water_drawn = 0;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *ground = NULL;
	ALLEGRO_SAMPLE *song= NULL;
	ALLEGRO_SAMPLE_INSTANCE *sI = NULL;

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
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(10);

	song = al_load_sample("sound/bso.ogg");
	sI = al_create_sample_instance(song);
	al_set_sample_instance_playmode(sI,ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(sI,al_get_default_mixer());

	resources.push_back(al_load_bitmap("images/tiles/wall.png"));
	resources.push_back(al_load_bitmap("images/tiles/water.png"));

	bg.push_back(al_load_bitmap("images/bg/bg.png"));
	mapas.push_back(new Map(bg.size()-1));
	for (int i = 0; i < 1+MAPWIDTH; i++)
	{
		mapas[bg.size()-1]->mapa[i][MAPHEIGHT] = -1;
	}
	mapas[bg.size()-1]->mapa[300/18][(HEIGHT-96)/36] = 0;
	mapas[bg.size()-1]->mapa[20][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[21][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[22][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->eventos.push_back(new Event(132,HEIGHT-78));
	mapas[bg.size()-1]->eventos[0]->path.push_back(140);
	mapas[bg.size()-1]->eventos[0]->path.push_back(-2);
	mapas[bg.size()-1]->eventos[0]->path.push_back(124);
	bg.push_back(al_load_bitmap("images/bg/beach.png"));
	mapas.push_back(new Map(bg.size()-1));
	for (int i = 0; i < 1+MAPWIDTH; i++)
	{
		mapas[bg.size()-1]->mapa[i][MAPHEIGHT] = -1;
	}
	mapas[bg.size()-1]->mapa[23][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[24][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[25][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[26][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[53][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[54][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[55][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[56][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[57][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[80][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[81][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[82][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[83][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[84][MAPHEIGHT] = -3;


	bg.push_back(al_load_bitmap("images/bg/underground.png"));
	mapas.push_back(new Map(bg.size()-1));
	for (int i = 0; i < 1+MAPWIDTH; i++)
	{
		mapas[bg.size()-1]->mapa[i][MAPHEIGHT] = -1;
	}
	mapas[bg.size()-1]->mapa[33][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[34][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[35][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[66][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[67][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[69][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[70][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[71][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[72][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[73][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[74][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[75][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[76][MAPHEIGHT] = -1;
	mapas[bg.size()-1]->mapa[77][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[78][MAPHEIGHT] = -3;
	mapas[bg.size()-1]->mapa[79][MAPHEIGHT] = -3;

	bg.push_back(al_load_bitmap("images/bg/cave.png"));
	mapas.push_back(new Map(bg.size()-1));
	bg.push_back(al_load_bitmap("images/bg/jungle.png"));
	mapas.push_back(new Map(bg.size()-1));
	bg.push_back(al_load_bitmap("images/bg/clouds.png"));
	mapas.push_back(new Map(bg.size()-1));
	bg.push_back(al_load_bitmap("images/bg/studio.png"));
	mapas.push_back(new Map(bg.size()-1));

	npc.push_back(new NPC(3300,HEIGHT-78,40,2));
	resources.push_back(al_load_bitmap("images/characters/character.png"));
	npc[npc.size()-1]->assignResource(resources.size()-1);
	npc[npc.size()-1]->setDim(32,48);


	npc.push_back(new NPC(400,HEIGHT-74,0,0));
	resources.push_back(al_load_bitmap("images/characters/camera.png"));
	npc[npc.size()-1]->assignResource(resources.size()-1);
	npc[npc.size()-1]->setDim(36,44);

	hero = new Hero(100,HEIGHT-78);
	resources.push_back(al_load_bitmap("images/characters/hero.png"));
	hero->assignResource(resources.size()-1);
	hero->assignMap(mapas[hero->currentBg]);
	hero->setDim(32,48);
	hero->npcs = npc;
	hero->bgNum = bg.size();
	ground = al_load_bitmap("images/tiles/ground_green.png");

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	
	textList.push_back(new Text("fonts/hobbit.ttf", 42,"Welcome",(WIDTH/2)-(3*42),70));
	textList[textList.size()-1]->createTimer(3);

	textList.push_back(new Text("fonts/arcade.ttf", 18,"VICTORY",(WIDTH/2)-(3*18),HEIGHT/2));
	textList[textList.size()-1]->createTimer(3);
	textList[textList.size()-1]->active = false;

	

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_play_sample_instance(sI);
	al_start_timer(timer);
	while(!done){
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER){
			redraw = true;
			if(!hero->moving && !hero->locked){
				hero->imgy = 0;
				hero->imgx = 0;
			}

			if(keys[LEFT]&& !hero->locked){
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
			if(keys[RIGHT] && !hero->locked){
				hero->medio++;
				if(hero->medio%6==0){
					hero->imgx++;
					hero->medio = 0;
				}
				hero->imgy = 2;
				if((hero->x-WIDTH/2)>-hero->xSpeed && !boundary){
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
				if(!hero->locked){
					hero->numJumps++;
					hero->jump();
				}
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
			fps_counter++;
			int drawing = ((MAPWIDTH)-(hero->viewPoint*10+WIDTH));
			if(drawing <= 0) boundary = true;
			else if(drawing>0) boundary = false;
			int evento=mapas[hero->currentBg]->checkEvents(hero->x+hero->viewPoint,hero->y);
			if(evento!=-1){
				hero->locked = true;
				if(mapas[hero->currentBg]->eventos[evento]->t_wait>0){
					if(fps_counter%20 == 0)
						mapas[hero->currentBg]->eventos[evento]->sleep_time();
				}
				else mapas[hero->currentBg]->eventos[evento]->move_to(hero->x,hero->y,hero->xSpeed);
			}

			if(hero->currentBg != hero->curr_map->id_bg)
				hero->curr_map = mapas[hero->currentBg];

			al_draw_bitmap_region(bg[hero->curr_map->id_bg],hero->viewPoint*10,0,WIDTH,HEIGHT,0,0,0);

			//Draw ground		
			for (int i = hero->viewPoint; i < 1+hero->viewPoint+(WIDTH/32); i++)
			{
				for (int j = 0; j < 1+MAPHEIGHT; j++)
				{
					switch(hero->curr_map->mapa[i][j]){
					case -1:{
						if(hero->curr_map->mapa[i+1][j]!=-1)
							al_draw_bitmap_region(ground,64,0,32,32,(i-hero->viewPoint)*32,j*36,0);
						else if(hero->curr_map->mapa[i-1][j]!=-1)
							al_draw_bitmap_region(ground,0,0,32,32,(i-hero->viewPoint)*32,j*36,0);
						else
							al_draw_bitmap_region(ground,32,0,32,32,(i-hero->viewPoint)*32,j*36,0);
						cont_water_drawn = 0;
						break;
							}
					case -2:
						break;
					case -3:
						{
							al_draw_bitmap_region(resources[1],(cont_water_drawn+curr_water)*32,0,32,32,(i-hero->viewPoint)*32,j*36,0);
							cont_water_drawn++;
							if(fps_counter%10 == 0)
								curr_water = (curr_water++)%2;
							break;
						}
					default:
						al_draw_bitmap(resources[hero->curr_map->mapa[i][j]],
							(i-hero->viewPoint)*36, // x to draw
							j*36,0);
						cont_water_drawn = 0;
						break;
					}
				}
			}
			if(hero->locked && (hero->x+hero->xSpeed)>=WIDTH-32)
				textList[1]->active = true;

			for (unsigned int i=0;i<textList.size();i++){
				if(textList[i]->active){
					textList[i]->render();
				}
			}

			for(unsigned int i=0;i<npc.size();i++){
				if(npc[i]->id_mapa == hero->currentBg && (npc[i]->x)<=36*( 1+hero->viewPoint+(WIDTH/32))){
					if(hero->checkCollide(i))
						npc[i]->active = false;
					if(npc[i]->active)
						render(npc[i],hero->viewPoint,resources);
				}
			}

			hero->update();

			render(hero,resources);

			al_draw_textf(textList[1]->fuente, al_map_rgb(255, 255, 255), 205, 5, 0, "%d,",
				(int) hero->x+hero->viewPoint);
			al_draw_textf(textList[1]->fuente, al_map_rgb(255, 255, 255), 285, 5, 0, " %d",
				(int)hero->currentBg);

			//al_draw_filled_rectangle((hero->x/18)+hero->viewPoint,(hero->y/36),(hero->x/18)+hero->viewPoint+32,(hero->y/36)+48,al_map_rgba(150,0,0,150));
			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}
	al_stop_sample_instance(sI);
	for(unsigned int i=0;i<resources.size();i++){
		al_destroy_bitmap(resources[i]);
	};
	for(unsigned int i=0;i<npc.size();i++){
		delete npc[i];
	};
	delete hero;
	for (unsigned int i=0;i<mapas.size();i++)
		delete mapas[i];
	for (unsigned int i=0;i<textList.size();i++)
		delete textList[i];
	for (unsigned int i=0;i<bg.size();i++)
		al_destroy_bitmap(bg[i]);
	al_destroy_sample(song);
	al_destroy_sample_instance(sI);
	al_destroy_bitmap(ground);
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);						//destroy our display object

	return 0;
}