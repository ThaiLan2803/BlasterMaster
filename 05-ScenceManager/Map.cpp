#include "Map.h"
#include "Rect.h"
#include "Brick.h"


Map* Map::_instance = nullptr;

void Map::updateObj()
{
	
	
}


Map::Map()
{
	Stage = 0;
}

Map* Map::GetInstance()
{
	if (_instance == nullptr) {
		_instance = new Map();
	}
	return _instance;
}

void Map::updateMapObject(vector<LPGAMEOBJECT>* objs)
{
	updateObj();
	//this->listObj = objs;
	for (int i = 0; i < listObj->size(); i++)
		objs->push_back(this->listObj->at(i));
}

void Map::updateMap(float x, float y, Point& tf, Point& br) {
	
}



void Map::MapReset()
{
	listObj->clear();
	
}

