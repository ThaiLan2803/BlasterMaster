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
		if (x < 30 && vx < 0)
			x = 30;
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

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		// Collision logic with other objects
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<BrickNoColli*>(e->obj))
			{
				x += dx;
				y += dy;
			}
			if (dynamic_cast<Enemy2*>(e->obj))
			{
				Enemy2* e2 = dynamic_cast<Enemy2*>(e->obj);
				e2->SetState(ENEMY2_STATE_DIE);
			}
			else if (dynamic_cast<CPortal*>(e->obj))
			{
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
	if (nx == 0 && ny == 0)
		ani = JASON_ANI_IDLE;
	if (nx > 0)
	{
		//ani = TANK_ANI_WALKING_RIGHT;
		if (!IsJason())
		{
			//ani = TANK_ANI_IDLE_RIGHT;
			if (bl_ny == 0)
			{
				ani = TANK_ANI_IDLE_RIGHT;
				Gun->NewRender(x + 15, y);
				Gun->SetState(SUNG_STATE_RIGHT);
				WLeft->NewRender(x - 5, y - 12);
				WRight->NewRender(x + 11, y - 12);
				bc->NewRender(x + 4, y - 8);
				animation_set->at(1)->Render(x, y, 255);
			}
			else
			{
				Gun->SetState(SUNG_STATE_UP);
				Gun->NewRender(x + 8, y + 12);
				WLeft->NewRender(x + 5, y - 12);
				WRight->NewRender(x + 15, y - 12);
				bc->NewRender(x + 11, y - 6);
				animation_set->at(3)->Render(x, y + 4, 255);
			}
		
		}
	}
	else
		if (nx < 0)
		{
			//ani = TANK_ANI_WALKING_LEFT;
			if (!IsJason())
			{
				//ani = TANK_ANI_IDLE_LEFT;
				if (bl_ny == 0)
				{
					ani = TANK_ANI_IDLE_LEFT;
					Gun->NewRender(x - 8, y);
					Gun->SetState(SUNG_STATE_LEFT);
					WLeft->NewRender(x - 5, y - 12);
					WRight->NewRender(x + 11, y - 12);
					bc->NewRender(x + 4, y - 8);
					animation_set->at(0)->Render(x, y, 255);
				}
				else
				{
					animation_set->at(2)->Render(x, y + 4, 255);
					Gun->SetState(SUNG_STATE_UP);
					Gun->NewRender(x - 2, y + 13);
					WLeft->NewRender(x - 7, y - 12);
					WRight->NewRender(x + 3, y - 12);
					bc->NewRender(x - 1, y - 6);
				}
				
			}
		}
	int alpha = 255;
	if (untouchable) alpha = 128;
	if (ny > 0)
		ani = JASON_ANI_BACK;
	if (ny < 0)
		ani = JASON_ANI_IDLE;
	
	if (IsJason())
	{
		animation_set->at(ani)->Render(x, y, alpha);
	/*	WLeft->NewRender(x - 5, y - 12);
		WRight->NewRender(x + 11, y - 12);
		bc->NewRender(x + 4, y - 8);*/
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
		nx = 1;
		if (IsJason())
		{
			vy = 0;
			ny = 0;
		}
		if (WLeft != NULL && WRight != NULL && Gun != NULL)
		{
			WLeft->SetState(BANHXE_STATE_WALKING_RIGHT);
			WRight->SetState(BANHXE_STATE_WALKING_RIGHT);
			//Gun->SetState(SUNG_STATE_RIGHT);
		}
		
		break;
	case TANK_STATE_WALKING_LEFT:
		vx = -TANK_WALKING_SPEED;
		nx = -1;
		if (IsJason())
		{
			vy = 0;
			ny = 0;
		}
		if (WLeft != NULL && WRight != NULL && Gun != NULL)
		{
			WLeft->SetState(BANHXE_STATE_WALKING_LEFT);
			WRight->SetState(BANHXE_STATE_WALKING_LEFT);
			//Gun->SetState(SUNG_STATE_LEFT);
		}
		
		break;
	case JASON_STATE_WALKING_UP:
		if (IsJason())
		{
			vy = TANK_WALKING_SPEED;
			vx = 0;
			nx = 0;
			ny = 1;
		}
		if (WLeft != NULL && WRight != NULL)
		{
			WLeft->SetState(BANHXE_STATE_WALKING_RIGHT);
			WRight->SetState(BANHXE_STATE_WALKING_RIGHT);
		}
		break;
	case JASON_STATE_WALKING_DOWN:
		if (IsJason())
		{
			vy = -TANK_WALKING_SPEED;
			vx = 0;
			ny = -1;
			nx = 0;
		}
		if (WLeft != NULL && WRight != NULL)
		{
			WLeft->SetState(BANHXE_STATE_WALKING_LEFT);
			WRight->SetState(BANHXE_STATE_WALKING_LEFT);
		}
		break;
	case TANK_STATE_JUMP:
		vy = TANK_JUMP_SPEED_Y;
		break;
	case TANK_STATE_IDLE:
		vx = 0;
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
		bl_ny = 0;
		if (IsJason())
		{
			vx = 0;
			vy = 0;
		}
		if (WLeft != NULL && WRight != NULL)
		{
			WLeft->SetState(BANHXE_STATE_IDLE);
			WRight->SetState(BANHXE_STATE_IDLE);
		}
		break;
	case TANK_STATE_DAN_UP:
		if (IsJason())
			ny = 1;
		else
			bl_ny = 1;
	}
}

void CTank::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y - 11;
	if (!IsJason())
	{
		right = x + TANK_BBOX_WIDTH;
		bottom = y + TANK_BBOX_HEIGHT - 11;
	}
	else
	{
		right = x + JASON_BBOX_WIDTH-10;
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
	bullet->IsJason = IsJason();
}
void CTank::Shoot()
{
	int bullet_first = bullets.size();
	Bullet* newBullet;
	if (IsJason())
		newBullet = new Bullet(nx, ny);
	else
		newBullet = new Bullet(nx, bl_ny);
	newBullet->SetAnimationSet(bullet->animation_set);
	newBullet->SetPosition(x, y);
	bullets.push_back(newBullet);
	//DebugOut(L"Size: %d \n", (int)bullets.size());

}