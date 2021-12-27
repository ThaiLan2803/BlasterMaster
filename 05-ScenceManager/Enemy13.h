#pragma once
#include "GameObject.h"
#include "Enemy11.h"
#define ENEMY13_BBOX_WIDTH	 22
#define ENEMY13_BBOX_HEIGHT 18

#define ENEMY13_STATE_IDLE		200
#define ENEMY13_STATE_DIE		100
#define ENEMY13_STATE_ITEM		300

#define ENEMY13_ANI_ITEM 1
#define ENEMY13_ANI_IDLE 0
#define ENEMY13_SPEED	 0.1f
class Enemy13 : public CGameObject
{
	int untouchable;
	Enemy11* bullet;
	int timecount;
	float x0 = 0;
	DWORD untouchable_start;
	float vx = ENEMY13_SPEED;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	vector<LPGAMEOBJECT> bullets;
public:
	Enemy13();
	void AddBullet(Enemy11* bulletF) { bullet = bulletF; };
	void Shoot();
	virtual void SetState(int state);
};
