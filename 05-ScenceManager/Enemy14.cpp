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
	float player_x, player_y;
	coObjects->at(coObjects->size() - 1)->GetPosition(player_x, player_y);
	float distance = sqrt((player_x - x) * (player_x - x) + (player_y - y) * (player_y - y));
	if (distance <= DISTANCE)
		FollowPlayer(player_x, player_y);
}

void Enemy14::FollowPlayer(float a, float b)
{
	float t0 = a - x;
	float t1 = b - y;
	x += vx * t0;
	y += vy * t1;
}
void Enemy14::Render()
{
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
		break;
	}
}