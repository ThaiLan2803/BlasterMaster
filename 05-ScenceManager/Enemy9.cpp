#include "Enemy9.h"
#include "Utils.h"

Enemy9::Enemy9()
{
	SetState(ENEMY9_STATE_WALKING);
}

void Enemy9::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state != STATE_DIE)
	{
		left = x;
		top = y;
		right = x + ENEMY9_BBOX_WIDTH;
		bottom = y + ENEMY9_BBOX_HEIGHT;
	}
}

void Enemy9::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	for (int i = 0; i < bullets.size(); i++)
		if (bullets[i]->GetState() == BULLET_STATE_DIE)
			bullets.erase(bullets.begin() + i);
	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->Update(dt, coObjects);
	/*x += vx * dt;
	if (x_ == 0)
		x_ = x;
	x += dx;

	if (vx < 0 && x < x_ - 70) {
		x = x_ - 70; vx = -vx;
	}

	if (vx > 0 && x > x_ + 70) {
		x = x_ + 70; vx = -vx;
	}*/
	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->Update(dt, coObjects);
	timecount++;
	if (timecount >= 100 && state != STATE_ITEM)
	{
		Shoot();
		timecount = 0;
	}
}

void Enemy9::Render()
{
	int ani = get_hit;
	if (state == STATE_DIE) {
		return;
	}
	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->Render();
	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void Enemy9::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	case ENEMY9_STATE_WALKING:
		vx = ENEMY9_WALKING_SPEED;
		break;
	case STATE_ITEM:
		vx = vy = 0;
		break;
	}
}
void Enemy9::Shoot()
{
		Enemy11* newBullet;
		newBullet = new Enemy11(0, -1);
		newBullet->SetAnimationSet(bullet->animation_set);
		newBullet->SetPosition(x -10, y + 20);
		bullets.push_back(newBullet);
}