#include "Enemy13.h"
#include "Utils.h"
Enemy13::Enemy13()
{
	state = ENEMY13_STATE_IDLE;
}

void Enemy13::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ENEMY13_STATE_DIE)
	{
		return;
	}
	left = x;
	top = y;
	right = x + ENEMY13_BBOX_WIDTH;
	bottom = y + ENEMY13_BBOX_HEIGHT;
}

void Enemy13::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

}

void Enemy13::Render()
{
	//DebugOut(L"State ene: %d \n", state);
	int ani = ENEMY13_ANI_IDLE;
	if (state == ENEMY13_STATE_ITEM) {
		ani = ENEMY13_ANI_ITEM;
	}
	if (state == ENEMY13_STATE_DIE)
	{
		return;
	}
	RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);

}

void Enemy13::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMY13_STATE_DIE:
		DebugOut(L"ENEMY13 die");
		break;
	}
}