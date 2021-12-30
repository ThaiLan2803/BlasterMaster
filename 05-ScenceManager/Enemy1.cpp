#include "Enemy1.h"
Enemy1::Enemy1()
{
	state = ENEMY1_STATE_IDLE;
}

void Enemy1::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state != STATE_DIE)
	{
		left = x;
		top = y;
		right = x + ENEMY1_BBOX_WIDTH;
		bottom = y + ENEMY1_BBOX_HEIGHT;
	}
}

void Enemy1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (state == STATE_ITEM)
	{
		tc++;
		if (tc > 100)
			enm4->Update(dt, coObjects);
	}
}

void Enemy1::Render()
{
	int ani = get_hit;
	if (state == STATE_ITEM) {
		if (!isSet)
		{
			enm4->SetPosition(x, y);
			isSet = true;
		}
		enm4->Render();
	}
	else

	//RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);
}

void Enemy1::SetState(int state)
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