#include "Enemy4.h"
Enemy4::Enemy4()
{
	SetState(ENEMY4_STATE_WALKING);
}

void Enemy4::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state != STATE_DIE)
	{
		left = x;
		top = y;
		right = x + ENEMY4_BBOX_WIDTH;
		bottom = y + ENEMY4_BBOX_HEIGHT;
	}
}

void Enemy4::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (x_ == 0)
		x_ = x;
	if (y_ == 0)
		y_ = y;
	x += dx;
	if (y_ < 200)
		y = 100 - 60 * sin(8 * x);
	else
		y = 300 - 60 * sin(8 * x);

	if (vx < 0 && x < x_ - 200) {
		x = x_ - 200; vx = -vx;
	}

	if (vx > 0 && x > x_ + 50) {
		x = x_ + 50; vx = -vx;
	}
}

void Enemy4::Render()
{
	int ani = get_hit;
	if (state == STATE_DIE)
		return;
	animation_set->at(ani)->Render(x, y);
}

void Enemy4::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	case ENEMY4_STATE_WALKING:
		vx = -ENEMY4_WALKING_SPEED;
		break;
	case STATE_ITEM:
		vx = vy = 0;
		break;
	}
}