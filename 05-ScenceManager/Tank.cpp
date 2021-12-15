#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include "Quadtree.h"
#include "Tank.h"
#include "Game.h"

CTank::CTank(float x, float y) : CGameObject()
{
	SetState(TANK_STATE_IDLE);
	this->x = x;
	this->y = y;
}

void CTank::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	//DebugOut(L"Tank: %dx, %dy", int(x), int(y));
	for (int i = 0; i < bullets.size(); i++)
		if (bullets[i]->GetState() == BULLET_STATE_DIE)
			bullets.erase(bullets.begin() + i);
	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->Update(dt, coObjects);
	//Simple fall down
	if (!IsJason())
		vy = TANK_GRAVITY*dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != TANK_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > TANK_UNTOUCHABLE_TIME)
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
		/*if (rdx != 0 && rdx!=dx)
		x += nx*abs(rdx); */
		
		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
//		IsCollide = true;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		/*if (vx > 0 && x > RIGHT_BORDER) x = RIGHT_BORDER;
		if (vx < 0 && x < LEFT_BORDER) x = LEFT_BORDER;
		if (vy < 0 && y < TOP_BORDER) y = TOP_BORDER;
		if (vy > 0 && y > BOTTOM_BORDER) y = BOTTOM_BORDER;*/
		// Collision logic with other objects
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Enemy2*>(e->obj))
			{
				Enemy2* e2 = dynamic_cast<Enemy2*>(e->obj);
				e2->SetState(ENEMY2_STATE_DIE);
			}
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				DebugOut(L"P colli");
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}

		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
};

void CTank::Render()
{
	int ani;
	if (nx > 0)
	{
		if (vx == 0)
			ani = JASON_ANI_IDLE;
		else
		ani = TANK_ANI_IDLE_RIGHT;
		if (!IsJason())
		{
			if (bl_ny == 0)
			{
				Gun->NewRender(x + 15, y);
				Gun->SetState(SUNG_STATE_RIGHT);
			}
			else
			{
				Gun->SetState(SUNG_STATE_UP);
				Gun->NewRender(x, y + 10);
			}
		}
	}
	else
		if (nx < 0)
		{
			if (vx == 0)
				ani = JASON_ANI_IDLE;
			else
				ani = TANK_ANI_IDLE_LEFT;
			if (!IsJason())
			{
				if (bl_ny == 0)
				{
					Gun->NewRender(x - 8, y);
					Gun->SetState(SUNG_STATE_LEFT);
				}
				else
				{
					Gun->SetState(SUNG_STATE_UP);
					Gun->NewRender(x, y + 10);
				}
			}
		}
	if (ny > 0)
		ani = JASON_ANI_BACK;
	int alpha = 255;
	if (untouchable) alpha = 128;
	/*WLeft->NewRender(x, y- 10);
	WRight->NewRender(x + 17, y - 10);
	bc->NewRender(x + 9, y - 8);*/
	animation_set->at(ani)->Render(x, y, alpha);
	if (!IsJason())
	{
		WLeft->NewRender(x - 5, y - 12);
		WRight->NewRender(x + 11, y - 12);
		bc->NewRender(x + 3, y - 8);
	}
	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->Render();
	RenderBoundingBox();
}

void CTank::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case TANK_STATE_WALKING_RIGHT:
		vx = TANK_WALKING_SPEED;
		if (IsJason())
			vy = 0;
		nx = 1;
		if (WLeft != NULL && WRight != NULL)
		{
			WLeft->SetState(BANHXE_STATE_WALKING_RIGHT);
			WRight->SetState(BANHXE_STATE_WALKING_RIGHT);
		
		}
		
		break;
	case TANK_STATE_WALKING_LEFT:
		vx = -TANK_WALKING_SPEED;
		if (IsJason())
			vy = 0;
		nx = -1;
		if (WLeft != NULL && WRight != NULL)
		{
			WLeft->SetState(BANHXE_STATE_WALKING_LEFT);
			WRight->SetState(BANHXE_STATE_WALKING_LEFT);
			
		}
		
		break;
	case TANK_STATE_WALKING_UP:
		vy = TANK_WALKING_SPEED;
		break;
	/*case TANK_STATE_WALKING_DOWN:
		vy = -TANK_WALKING_SPEED;
		break;*/
	case TANK_STATE_JUMP:
		vy = TANK_JUMP_SPEED_Y;
		break;
	case TANK_STATE_IDLE:
		vx = 0;
		bl_ny = 0;
		if (WLeft && WRight)
		{
			WLeft->SetState(BANHXE_STATE_IDLE);
			WRight->SetState(BANHXE_STATE_IDLE);
		}
		break;
	case TANK_STATE_BULLET:
		createBl_count = TANK_AMOUNT_BULLET;
		this->Shoot();
		break;
	case TANK_STATE_STOP:
		if (IsJason())
		{
			vx = 0;
			vy = 0;
		}
		WLeft->SetState(BANHXE_STATE_IDLE);
		WRight->SetState(BANHXE_STATE_IDLE);
		break;
	case TANK_STATE_DAN_UP:
		bl_ny = 1;
	}
}

void CTank::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x - 6;
	top = y - 11;
	if (!IsJason())
	{
		right = x + TANK_BBOX_WIDTH - 5;
		bottom = y + TANK_BBOX_HEIGHT - 11;
	}
	else
	{
		right = x + JASON_BBOX_WIDTH;
		bottom = y + JASON_BBOX_HEIGHT - 11;
	}
	
}

void CTank::Reset()
{
	SetState(TANK_STATE_IDLE);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}
void CTank::SetBanhXe(BanhXe* bx)
{
	WLeft = WRight = bx;
}
void CTank::SetSung(Sung* s)
{
	 Gun = s;
}
void CTank::SetBtc(BottomCircle* btc)
{
	bc = btc;
}
void CTank::SetBullet(Bullet* bl)
{
	bullet = bl;
	DebugOut(L"Set bulll");
}
void CTank::Shoot()
{
	int bullet_first = bullets.size();
	Bullet* newBullet = new Bullet(nx, bl_ny);
	newBullet->SetAnimationSet(bullet->animation_set);
	newBullet->SetPosition(x, y);
	bullets.push_back(newBullet);
	if (bullets.size() - bullet_first > TANK_AMOUNT_BULLET)
		bullets.erase(bullets.begin() + bullets.size() - 1 - TANK_AMOUNT_BULLET, bullets.end());
	//DebugOut(L"Size: %d \n", (int)bullets.size());

}