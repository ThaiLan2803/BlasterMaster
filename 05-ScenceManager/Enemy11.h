#pragma once
#include "GameObject.h"

#define DAN_HEIGHT_H	10
#define DAN_WIDTH_H	24
#define DAN_HEIGHT_UP	24
#define DAN_WIDTH_UP	10

#define	BULLET_STATE_DIE	1
#define BULLET_UNTOUCHABLE_TIME 			5000

#define SPEED	0.1f;

class Enemy11 : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;
	int nx, ny_;
public:
	Enemy11(int nx, int ny);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
};