#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "Animations.h"
#include "Rect.h"

using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

#define BRICK_BBOX_WIDTH			16
#define BRICK_BBOX_HEIGHT 			16
#define STATE_DIE	1000
#define STATE_ITEM	2000

class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj, obj_1;
	float t, nx, ny;
	
	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL) 
	{ 
		this->t = t; 
		this->nx = nx; 
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj; 
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};


class CGameObject
{
public:

	float x; 
	float y;
	

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;


	int nx;	 
	int ny;


	int state;
	bool isEnable = true;
	int get_hit = 0;
	int hit_times;
	DWORD dt; 

	LPANIMATION_SET animation_set;
	LPCOLLISIONEVENT e;

public: 
	bool IsNoColli = false;
	virtual void SetPosition(float x, float y)
	{

		try
		{
			this->x = x, this->y = y; 
		}
		catch (exception e)
		{

		}
	}
	bool IsEnable() { return isEnable; }
	void Disable() { isEnable = false; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	int GetState() { return this->state; }
	void Hit() 
	{
		get_hit++;
		if (animation_set->size() > 1 && get_hit == animation_set->size() - 1)
			SetState(STATE_ITEM);
		if (get_hit == animation_set->size())
			SetState(STATE_DIE);
	};
	void SetHit() { hit_times = animation_set->size(); }
	void RenderBoundingBox();

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny, 
		float &rdx, 
		float &rdy);

	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; };
//	virtual Rect GetBoundingBox() = 0;

	~CGameObject();
};

