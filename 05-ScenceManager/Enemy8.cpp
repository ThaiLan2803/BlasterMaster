#include "Enemy8.h"
#include "Utils.h"
Enemy8::Enemy8()
{
	SetState(ENEMY8_STATE_WALKING);
}

void Enemy8::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ENEMY8_BBOX_WIDTH;
	bottom = y + ENEMY8_BBOX_HEIGHT;
}

void Enemy8::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += dx;
	y += dy;
	if (x_ == 0)
		x_ = x;
	if (y_ == 0)
		y_ = y;
	if (vx < 0 && x < x_ - 30)
		vx = -vx;
	if (vx > 0 && x > x_ + 30)
		vx = -vx;
	if (vy < 0 && y < y_ - 20)
		vy = -vy;
	if (vy > 0 && y > y_ + 20)
		vy = -vy;
}

void Enemy8::Render()
{
	int ani = ENEMY8_ANI_WALKING;
	if (state == ENEMY8_STATE_DIE) {
		return;
	}
	else 
		animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void Enemy8::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMY8_STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	case ENEMY8_STATE_WALKING:
		vx = ENEMY8_WALKING_SPEED;
		vy = -ENEMY8_WALKING_SPEED
	}
}