#pragma once
#include "GameObject.h"

class Map
{
	static Map* _instance;
	vector<LPGAMEOBJECT>* listObj;
	void updateObj();
	Point tf, br;

public:
	int id;
	bool ChangeMap = false;

	Map();
	static Map* GetInstance();
	int Stage;
	void updateMapObject(vector<LPGAMEOBJECT>*);
	void updateMap(float x, float y, Point& tf, Point& br);
	void MapReset();
};

