#include "Enemy14.h"
#include "Utils.h"
#include "Brick2.h"
Enemy14::Enemy14()
{
	state = ENEMY14_STATE_IDLE;
}

void Enemy14::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state != STATE_DIE)
	{
		left = x;
		top = y;
		right = x + ENEMY14_BBOX_WIDTH;
		bottom = y + ENEMY14_BBOX_HEIGHT;
	}
}

void Enemy14::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	float player_x, player_y;
	for (int i = 0; i < bullets.size(); i++)
		if (bullets[i]->GetState() == BULLET_STATE_DIE)
			bullets.erase(bullets.begin() + i);
	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->Update(dt, coObjects);
	coObjects->at(coObjects->size() - 1)->GetPosition(player_x, player_y);
	float distance = sqrt((player_x - x) * (player_x - x) + (player_y - y) * (player_y - y));
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (state != ENEMY14_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		vx = vy = ENEMY14_SPEED;
		if (distance <= DISTANCE)
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

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			try {
				if (dynamic_cast<Brick2*>(e->obj))
				{
					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;
				}
			}
			catch (exception e) {

			}
		}
	}
	timecount++;

	if (timecount >= TIME && state != STATE_ITEM)
	{
		Shoot();
		timecount = 0;
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Enemy14::FollowPlayer(float a, float b)
{
	t0 = a - x;
	t1 = b - y;
	x += vx * t0;
	y += vy * t1;
}
void Enemy14::Render()
{
	int ani = get_hit;
	if (state == STATE_DIE)
	{
		return;
	}
	RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);
	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->Render();

}

void Enemy14::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMY14_STATE_DIE:
		break;
	case STATE_ITEM:
		vx = vy = 0;
		break;
	}
}
void Enemy14::Shoot()
{
	Enemy11* newBullet;
	newBullet = new Enemy11(t0 / abs(t0), t1 / abs(t1));
	newBullet->SetAnimationSet(bullet->animation_set);
	newBullet->SetPosition(x, y);
	bullets.push_back(newBullet);
}