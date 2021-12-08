#pragma once
#include "GameObject.h"

#define BULLET_HEIGHT	8
#define BULLET_WIDTH	20

#define DAN_ANI_LEFT	0
#define DAN_ANI_RIGHT	1
class Bullet : public CGameObject
{
public:
	Bullet(int nx);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
};