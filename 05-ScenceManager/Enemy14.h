#pragma once
#include "GameObject.h"
#include "Enemy11.h"

#define ENEMY14_BBOX_WIDTH	22
#define ENEMY14_BBOX_HEIGHT 18

#define ENEMY14_STATE_IDLE	200
#define ENEMY14_STATE_DIE	100
#define ENEMY14_STATE_ITEM	300

#define ENEMY14_ANI_ITEM 1
#define ENEMY14_ANI_IDLE 0
#define ENEMY14_SPEED 0.009f
#define	DISTANCE 100
#define	TIME 100
class Enemy14 : public CGameObject
{
	int x0, y0 = 0;
	int timecount;
	float t0, t1;
	Enemy11* bullet;
	vector<LPGAMEOBJECT> bullets;
	float vx = vy = ENEMY14_SPEED;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	Enemy14();
	void Shoot();
	void AddBullet(Enemy11* bulletF) { bullet = bulletF; };
	virtual void SetState(int state);
	void FollowPlayer(float a, float b);
};
