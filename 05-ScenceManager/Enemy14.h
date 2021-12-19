#pragma once
#include "GameObject.h"

#define ENEMY14_BBOX_WIDTH 22
#define ENEMY14_BBOX_HEIGHT 18

#define ENEMY14_STATE_IDLE 200
#define ENEMY14_STATE_DIE 100
#define ENEMY14_STATE_ITEM 300

#define ENEMY14_ANI_ITEM 1
#define ENEMY14_ANI_IDLE 0
class Enemy14 : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Enemy14();
	virtual void SetState(int state);
};
