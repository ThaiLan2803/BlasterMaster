#include "Bullet.h"
#include "Utils.h"
#include "Utils.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Enemy5.h"
#include "Enemy6.h"
#include "Enemy7.h"
#include "Enemy8.h"
#include "Enemy9.h"
#include "Enemy10.h"
#include "Brick.h"
Bullet::Bullet(int nx, int ny)
{
	this->bl_ny = ny;
	this->nx = nx; 
	if (bl_ny != 0)
		vy = BULLET_SPEED * bl_ny;
	else
		vx = nx * BULLET_SPEED;
}
void Bullet::Render()
{
	int ani;
	if (bl_ny != 0)
	{
		ani = DAN_ANI_UP;
		animation_set->at(ani)->Render(x, y+20);
	}
	else if (vx != 0)
	{
		if (vx > 0)
		{
			ani = DAN_ANI_RIGHT;
			animation_set->at(ani)->Render(x + 5, y);
		}
		else
		{
			ani = DAN_ANI_LEFT;
			animation_set->at(ani)->Render(x - 15, y);
		}
	}
	/*if (bl_ny != 0)
			animation_set->at(1)->Render(x - 5, y + 20);
		else
			animation_set->at(0)->Render(x + nx * 5, y);
		RenderBoundingBox();*/
}

void Bullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	if (bl_ny != 0)
	{
		r = x + DAN_WIDTH_UP;
		b = y + DAN_HEIGHT_UP;
	}
	else
	{
		r = x + DAN_WIDTH_H;
		b = y + DAN_HEIGHT_H;
	}
}

void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != BULLET_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > BULLET_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{

		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		this->SetState(BULLET_STATE_DIE);
		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick*>(e->obj))
			{
				this->SetState(BULLET_STATE_DIE);
			}
			if (dynamic_cast<Enemy1*>(e->obj))
			{
				Enemy1* e1 = dynamic_cast<Enemy1*>(e->obj);
				e1->SetState(ENEMY1_STATE_ITEM);
			}
			if (dynamic_cast<Enemy2*>(e->obj))
			{
				Enemy2* e2 = dynamic_cast<Enemy2*>(e->obj);
				e2->SetState(ENEMY2_STATE_DIE);
			}
			if (dynamic_cast<Enemy3*>(e->obj))
			{
				Enemy3* e3 = dynamic_cast<Enemy3*>(e->obj);
				e3->SetState(ENEMY3_STATE_DIE);
			}
			if (dynamic_cast<Enemy4*>(e->obj))
			{
				Enemy4* e4 = dynamic_cast<Enemy4*>(e->obj);
				e4->SetState(ENEMY4_STATE_DIE);
			}
			if (dynamic_cast<Enemy5*>(e->obj))
			{
				Enemy5* e5 = dynamic_cast<Enemy5*>(e->obj);
				e5->SetState(ENEMY5_STATE_DIE);
			}
			if (dynamic_cast<Enemy6*>(e->obj))
			{
 				Enemy6* e6 = dynamic_cast<Enemy6*>(e->obj);
 				e6->SetState(ENEMY6_STATE_DIE);
			}
			if (dynamic_cast<Enemy7*>(e->obj))
			{
				Enemy7* e7 = dynamic_cast<Enemy7*>(e->obj);
				e7->SetState(ENEMY7_STATE_DIE);
			}
			if (dynamic_cast<Enemy8*>(e->obj))
			{
				Enemy8* e8 = dynamic_cast<Enemy8*>(e->obj);
				e8->SetState(ENEMY8_STATE_DIE);
			}
			if (dynamic_cast<Enemy9*>(e->obj))
			{
				Enemy9* e9 = dynamic_cast<Enemy9*>(e->obj);
				e9->SetState(ENEMY9_STATE_DIE);
			}
			if (dynamic_cast<Enemy10*>(e->obj))
			{
				Enemy10* e10 = dynamic_cast<Enemy10*>(e->obj);
				e10->SetState(ENEMY10_STATE_DIE);
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void Bullet::SetState(int state)
{
	this->state = state;
}