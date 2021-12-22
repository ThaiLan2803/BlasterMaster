#pragma once
#include "GameObject.h"

#define ENEMY12_BBOX_WIDTH	22
#define ENEMY12_BBOX_HEIGHT 18

#define ENEMY12_STATE_IDLE	200
#define ENEMY12_STATE_DIE	100
#define ENEMY12_STATE_ITEM	300

#define ENEMY12_ANI_ITEM 1
#define ENEMY12_ANI_IDLE 0
#define ENEMY12_SPEED	0.15f
class Enemy12 : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Enemy12();
	virtual void SetState(int state);
};
