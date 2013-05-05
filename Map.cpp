#include "Map.h"
#include "objects.h"
#include <vector>

using namespace std;

Map::Map(int b){
	this->id_bg = b;

	for(int i=0;i<1+(MAPWIDTH);i++){
		for(int j=0;j<MAPHEIGHT+1;j++){
			this->mapa[i][j] = -2;
		}
	}

}

void Map::copyMap(int (*M)[MAPHEIGHT+1]){
	for(int i=0;i<1+(MAPWIDTH);i++){
		for(int j=0;j<MAPHEIGHT+1;j++){
			this->mapa[i][j] = M[i][j];
		}
	}
}

void Map::createEvent(int x,int y){
	this->eventos.push_back(new Event(x,y));
}

int Map::checkEvents(int x, int y){
	for(unsigned int i=0;i<eventos.size();i++){
		if(eventos[i]->x_start == x && eventos[i]->y_start == y)
			return i;
	}
	return -1;
}
Map::~Map(){
	for(unsigned int i=0;i<this->eventos.size();i++)
		delete this->eventos[i];
}

Event::Event(int x, int y){
	this->x_start = x;
	this->y_start = y;
	this->i=0;
}
void Event::wait_time(int t){
	this->t_wait = t;
}
bool Event::sleep_time(){
	if(this->t_wait <= 0)
		return true;
	else
		this->t_wait--;
	return false;
}
int Event::move_to(int x_h, int y_h, int x_speed){
	if(this->path[i] < 0){
		this->wait_time(this->path[i]);
		this->i++;
	}
	else if(x_h+x_speed != this->path[i]){
		if(this->path[i]-x_h>0)return 1;
		else if(this->path[i]-x_h<0)return -1;
	}
	else{
		this->i++;
		return 0;
	}
}
void Event::addStep(int x){
	this->path.push_back(x);
}