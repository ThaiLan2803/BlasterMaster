#pragma once
#include "GameObject.h"

#define ENEMY15_BBOX_WIDTH 22
#define ENEMY15_BBOX_HEIGHT 18

#define ENEMY15_STATE_IDLE 200
#define ENEMY15_STATE_DIE 100
#define ENEMY15_STATE_ITEM 300

#define ENEMY15_ANI_ITEM 1
#define ENEMY15_ANI_IDLE 0

#define ENEMY_SPEED 0.1f
class Enemy15 : public CGameObject
{
	int x0, y0 = 0;
	float vx = vy = ENEMY_SPEED;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Enemy15();
	virtual void SetState(int state);
	void FollowPlayer(float a, float b);
};

