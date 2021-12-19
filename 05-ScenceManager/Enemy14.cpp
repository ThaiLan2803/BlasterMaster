#include "Enemy14.h"
#include "Utils.h"
Enemy14::Enemy14()
{
	state = ENEMY14_STATE_IDLE;
}

void Enemy14::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == ENEMY14_STATE_DIE)
	{
		return;
	}
	left = x;
	top = y;
	right = x + ENEMY14_BBOX_WIDTH;
	bottom = y + ENEMY14_BBOX_HEIGHT;
}

void Enemy14::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

}

void Enemy14::Render()
{
	//DebugOut(L"State ene: %d \n", state);
	int ani = ENEMY14_ANI_IDLE;
	if (state == ENEMY14_STATE_ITEM) {
		ani = ENEMY14_ANI_ITEM;
	}
	if (state == ENEMY14_STATE_DIE)
	{
		return;
	}
	RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);

}

void Enemy14::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMY14_STATE_DIE:
		DebugOut(L"Enemy14 die");
		break;
	}
}