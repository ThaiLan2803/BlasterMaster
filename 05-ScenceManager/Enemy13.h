#pragma once
#include "GameObject.h"

#define ENEMY13_BBOX_WIDTH 22
#define ENEMY13_BBOX_HEIGHT 18

#define ENEMY13_STATE_IDLE 200
#define ENEMY13_STATE_DIE 100
#define ENEMY13_STATE_ITEM 300

#define ENEMY13_ANI_ITEM 1
#define ENEMY13_ANI_IDLE 0
class Enemy13 : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Enemy13();
	virtual void SetState(int state);
};
