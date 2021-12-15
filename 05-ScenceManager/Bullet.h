#pragma once
#include "GameObject.h"

#define DAN_HEIGHT_H	10
#define DAN_WIDTH_H		24
#define DAN_HEIGHT_UP	24
#define DAN_WIDTH_UP	10

#define BULLET_SPEED 0.9f

#define	BULLET_STATE_DIE	1
#define BULLET_UNTOUCHABLE_TIME	5000

#define DAN_ANI_LEFT	0
#define DAN_ANI_RIGHT	1
#define	DAN_ANI_UP		2

#define OBJECT_TYPE_BULLET	14
class Bullet : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;
	int nx, bl_ny;
public:
	Bullet(int nx, int ny);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
};