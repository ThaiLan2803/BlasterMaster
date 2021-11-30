#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include "Quadtree.h"
#include "Tank.h"
#include "Game.h"

CTank::CTank(float x, float y) : CGameObject()
{
	untouchable = 0;
	SetState(TANK_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->yWorld = 496 - float(y);
	
}

void CTank::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	/*x += vx * dt;
	this->y += vy * dt;
	this->yWorld = 496 - y - TANK_BBOX_HEIGHT;*/
	//Simple fall down
//	vy += TANK_GRAVITY;
	if (vx > 0 && x > RIGHT_BORDER) x = RIGHT_BORDER;
	if (vx < 0 && x < LEFT_BORDER) x = LEFT_BORDER;
	if (vy < 0 && y < TOP_BORDER) y = TOP_BORDER;
	if (vy > 0 && y > BOTTOM_BORDER) y = BOTTOM_BORDER;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != TANK_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > TANK_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		yWorld = 496 - y - TANK_BBOX_HEIGHT;
	
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
		yWorld = 496 - y;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		// Collision logic with other objects
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
};

void CTank::Render()
{
	int ani = -1;
	
	float xRender, yRender;
	GetPosition(xRender, yRender);
//	DebugOut(L"Tank render x: %d, y: %d \n", int(xRender), int(y));
	if (nx > 0)
	{
		ani = TANK_ANI_IDLE_RIGHT;
		Gun->NewRender(xRender + 15, yRender);
		WLeft->NewRender(xRender, yRender + 10);
		WRight->NewRender(xRender + 17, yRender + 10);
		bc->NewRender(xRender + 9, yRender + 8);
	}
	else
		if (nx < 0)
		{
			ani = TANK_ANI_IDLE_LEFT;
			Gun->NewRender(xRender - 8, yRender);
			WLeft->NewRender(xRender- 8, yRender + 10);
			WRight->NewRender(xRender + 9, yRender + 10);
			bc->NewRender(xRender, yRender + 8);
		}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(xRender, yRender, alpha);
	
	RenderBoundingBox();
	DebugOut(L"State: %d", ani);
}

void CTank::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case TANK_STATE_WALKING_RIGHT:
		vx = TANK_WALKING_SPEED;
		nx = 1;
		WLeft->SetState(BANHXE_STATE_WALKING_RIGHT);
		WRight->SetState(BANHXE_STATE_WALKING_RIGHT);
		break;
	case TANK_STATE_WALKING_LEFT:
		vx = -TANK_WALKING_SPEED;
		nx = -1;
		WLeft->SetState(BANHXE_STATE_WALKING_LEFT);
		WRight->SetState(BANHXE_STATE_WALKING_LEFT);
		break;
	case TANK_STATE_WALKING_UP:
		vy = TANK_WALKING_SPEED;
		break;
	case TANK_STATE_WALKING_DOWN:
		vy = -TANK_WALKING_SPEED;
		break;
		//	case TANK_STATE_WALKING_DOWN:
		//		vy = TANK_WALKING_SPEED;
		//		ny = 1;
		//		break;
		//	case TANK_STATE_JUMP:
		//		vy = TANK_JUMP_SPEED_Y;
		//		break;
	case TANK_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
		//	case TANK_STATE_DIE:
		//		vy = -TANK_DIE_DEFLECT_SPEED;
		//		break;
	}
}

void CTank::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = yWorld;
	right = x + TANK_BBOX_WIDTH;
	bottom = yWorld + TANK_BBOX_HEIGHT;
	
}

void CTank::Reset()
{
	SetState(TANK_STATE_IDLE);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}
//
//Rect CTank::GetBoundingBox()
//{
//	return Rect(Point(x, y + 6), TANK_BBOX_WIDTH - 1, TANK_BBOX_HEIGHT - 1);
//}
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