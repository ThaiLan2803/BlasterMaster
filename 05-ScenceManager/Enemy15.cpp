#include "Enemy15.h"
#include "Utils.h"
Enemy15::Enemy15()
{
	state = ENEMY15_STATE_IDLE;
}

void Enemy15::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state != STATE_DIE)
	{
		left = x;
		top = y;
		right = x + ENEMY15_BBOX_WIDTH;
		bottom = y + ENEMY15_BBOX_HEIGHT;
	}
}

void Enemy15::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	float player_x, player_y;
	coObjects->at(coObjects->size() - 1)->GetPosition(player_x, player_y);
	float distance = sqrt((player_x - x) * (player_x - x) + (player_y - y) * (player_y - y));
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (state != ENEMY15_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		vx = vy = ENEMY_SPEED;
		if (distance <= DISTANCE && state != STATE_ITEM)
			FollowPlayer(player_x, player_y);
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Enemy15::Render()
{
	int ani = get_hit;
	if (state == STATE_DIE)
		return;
	//RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);
	
}

void Enemy15::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_DIE:
		vx = vy = 0;
		break;
	case STATE_ITEM:
		vx = vy = 0;
		break;
	}
}
void Enemy15::FollowPlayer(float a, float b)
{
	//DebugOut(L"Move X: %f, Y: %f \n", vx, vy);
	float t0 = a - x;
	float t1 = b - y;
	if (state == STATE_DIE)
		return;
	x += vx * t0;
	y += vy * t1;
}