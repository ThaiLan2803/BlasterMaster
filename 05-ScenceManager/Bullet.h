#pragma once
#include "GameObject.h"

#define DAN_HEIGHT_H	10
#define DAN_WIDTH_H		24
#define DAN_HEIGHT_UP	24
#define DAN_WIDTH_UP	10
#define JASON_BULLET_H	18
#define JASON_BULLET_W	18

#define BULLET_SPEED 0.5f

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
	int t;
	float v1, v2;
	float x0, y1;
public:
	bool IsJason = false;
	Bullet(int nx, int ny, int v);
	void SetT(int v) { t = v; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	void Move();
};