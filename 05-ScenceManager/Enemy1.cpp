#include "Enemy1.h"
Enemy1::Enemy1()
{
	state = ENEMY1_STATE_IDLE;
}

void Enemy1::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ENEMY1_BBOX_WIDTH;
	bottom = y + ENEMY1_BBOX_HEIGHT;
}

void Enemy1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void Enemy1::Render()
{
	int ani = ENEMY1_ANI_IDLE;
	if (state == ENEMY1_STATE_ITEM) {
		ani = ENEMY1_ANI_ITEM;
	}
	if (state == ENEMY1_STATE_DIE)
	{
		return;
	}
	//RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);
}

void Enemy1::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMY1_STATE_DIE:
		break;
	}
}