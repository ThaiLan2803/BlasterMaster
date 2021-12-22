#pragma once
#include "GameObject.h"
#include "Rect.h"
#include "Sung.h"
#include "BanhXe.h"
#include "BottomCircle.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Enemy5.h"
#include "Bullet.h"
#include "Portal.h"
#include "BrickNoColli.h"
#define TANK_WALKING_SPEED		0.15f 
#define TANK_JUMP_SPEED_Y		0.5f
#define TANK_GRAVITY			-0.02f

#define TANK_STATE_IDLE					0
#define TANK_STATE_WALKING_RIGHT		1
#define TANK_STATE_WALKING_LEFT			2
#define TANK_STATE_JUMP					3
#define TANK_STATE_DIE					-1
#define JASON_STATE_WALKING_UP			4
#define JASON_STATE_WALKING_DOWN		5
#define TANK_STATE_STOP					6
#define TANK_STATE_BULLET				7
#define TANK_STATE_DAN_UP				8

#define TANK_ANI_IDLE_RIGHT				1
#define TANK_ANI_IDLE_LEFT				0
#define TANK_ANI_WALKING_RIGHT			2
#define TANK_ANI_WALKING_LEFT			3
#define JASON_ANI_WALKING_UP				4
#define JASON_ANI_WALKING_DOWN			5
#define TANK_ANI_DAN_UP_LEFT		6
#define TANK_ANI_DAN_UP_RIGHT		7


#define JASON_ANI_IDLE		0
#define JASON_ANI_BACK		1

#define JASON_BBOX_HEIGHT			20
#define JASON_BBOX_WIDTH 			25

#define TANK_BBOX_WIDTH  24
#define TANK_BBOX_HEIGHT 20

#define TOP_BORDER  0
#define LEFT_BORDER  15
#define BOTTOM_BORDER  520 - TANK_BBOX_HEIGHT
#define RIGHT_BORDER  1232 - TANK_BBOX_WIDTH

#define TANK_UNTOUCHABLE_TIME 5000
#define TANK_AMOUNT_BULLET	1

class CTank : public CGameObject
{
protected:
//	int level;
	int untouchable;
	DWORD untouchable_start;
	int createBl_count;
	int bl_ny = 0;
	float start_x;			// initial position of TANK at scene
	float start_y;
	bool isJason = false;
	int old_ani;
	vector<LPGAMEOBJECT> bullets;
	BanhXe * WLeft, *WRight;
	Sung* Gun;
	BottomCircle* bc;
	Bullet* bullet;
	~CTank();
public:

	CTank(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetJason() { isJason = true; }
	bool IsJason() { return isJason; }
	void SetState(int state);
//	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void Reset();
	void SetPosition(float x, float y)
	{

		try
		{
			this->x = x, this->y = y; this->y = y; 
		}
		catch (exception e)
		{

		}
	}
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetBullet(Bullet* bl);
	void Shoot();
	void SetBanhXe(BanhXe* bx);
	void SetSung(Sung* s);
	void SetBtc(BottomCircle* btc);
};