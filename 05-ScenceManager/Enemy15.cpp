#include "Enemy15.h"
#include "Utils.h"
Enemy15::Enemy15()
{
	state = ENEMY15_STATE_IDLE;
}

void Enemy15::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ENEMY15_STATE_DIE)
	{
		return;
	}
	left = x;
	top = y;
	right = x + ENEMY15_BBOX_WIDTH;
	bottom = y + ENEMY15_BBOX_HEIGHT;
}

void Enemy15::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

}

void Enemy15::Render()
{

	int ani = ENEMY15_ANI_IDLE;
	if (state == ENEMY15_STATE_ITEM) {
		ani = ENEMY15_ANI_ITEM;
	}
	if (state == ENEMY15_STATE_DIE)
	{
		return;
	}
	RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);

}

void Enemy15::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMY15_STATE_DIE:
		break;
	}
}