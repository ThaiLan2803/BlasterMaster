#include "Enemy12.h"
#include "Utils.h"
#include "Brick2.h"
#include "BrickNoColli.h"
Enemy12::Enemy12()
{
	state = ENEMY12_STATE_IDLE;
}

void Enemy12::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ENEMY12_STATE_DIE)
	{
		return;
	}
	left = x;
	top = y;
	right = x + ENEMY12_BBOX_WIDTH;
	bottom = y + ENEMY12_BBOX_HEIGHT;
}

void Enemy12::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	x += vx * dt;
	if (x < 30 && vx < 0)
	{
		x = 30;
		vx = -vx;
	}
	if (x > 200 && vx > 0)
	{
		x = 200;
		vx = -vx;
	}
}

void Enemy12::Render()
{
	int ani = get_hit;
	if (state == STATE_DIE)
	{
		return;
	}
	/*RenderBoundingBox();*/
	animation_set->at(ani)->Render(x, y);
}

void Enemy12::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_DIE:
		break;
	case STATE_ITEM:
		vx = vy = 0;
		break;
	}
}