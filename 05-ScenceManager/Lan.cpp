#include "Lan.h"

CLan::CLan() : CGameObject()
{
	this->vx = LAN_WALKING_SPEED;
	
}
void CLan::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + LAN_BBOX_WIDTH;
	bottom = y + LAN_BBOX_HEIGHT;
}

void CLan::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	
	x += vx*dt;
	y += vy*dt;

	if (nx == 1 && vx > 0 && x > (SCREEN_WIDTH - LAN_BBOX_WIDTH*2)) 
	{
		ny = 1;
		vy = LAN_WALKING_SPEED; vx = 0;
		dy += ny * vy;
	}
	else if (ny == 1 && vy > 0 && y > (SCREEN_HEIGHT - LAN_BBOX_HEIGHT*3.2))
	{
		nx = -1;
		vx = -LAN_WALKING_SPEED; vy = 0;
		dx += nx * vx;
	}
	else if (nx == -1 && vx < 0 && x < 2)
	{
		ny = -1;
		vy = -LAN_WALKING_SPEED; vx = 0;
		dy += ny * vy;
	}
	else if (ny == -1 && vy < 0 && y < 2)
	{
		nx = 1;
		vx = LAN_WALKING_SPEED; vy = 0;
		dx += nx * vx;
	}
	
	
}


void CLan::Render()
{
	int ani = LAN_ANI_WALKING;
	
	int alpha = 255;
	animation_set->at(ani)->Render(x, y, alpha);
	RenderBoundingBox();
}

void CLan::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LAN_STATE_WALKING:
		vx = -LAN_WALKING_SPEED;
	}
}
