#include "Enemy2.h"
#include "Utils.h"
Enemy2::Enemy2()
{
	SetState(ENEMY2_STATE_WALKING);
}

void Enemy2::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state != ENEMY2_STATE_DIE)
	{
		left = x;
		top = y;
		right = x + ENEMY2_BBOX_WIDTH;
		bottom = y + ENEMY2_BBOX_HEIGHT;
	}
}

void Enemy2::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	x += dx;
	y += dy;

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
}

void Enemy2::Render()
{
	int ani = ENEMY2_ANI_WALKING;
	if (this->GetState() != ENEMY2_STATE_DIE)
		animation_set->at(ani)->Render(x, y);
	else
		return;
	//RenderBoundingBox();
}

void Enemy2::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMY2_STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	}
}