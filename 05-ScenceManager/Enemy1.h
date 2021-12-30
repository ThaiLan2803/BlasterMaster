#pragma once
#include "GameObject.h"
#include "Enemy4.h"

#define ENEMY1_BBOX_WIDTH 22
#define ENEMY1_BBOX_HEIGHT 20

#define ENEMY1_STATE_DIE 100
#define ENEMY1_STATE_IDLE 200
#define ENEMY1_STATE_ITEM 300

#define ENEMY1_ANI_IDLE 0
#define ENEMY1_ANI_ITEM 1

class Enemy1 : public CGameObject
{
	int tc;
	int isSet = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	Enemy4* enm4;
public:
	Enemy1();
	virtual void SetState(int state);
	virtual void SetEnemy(Enemy4* e) { enm4 = e; };
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};