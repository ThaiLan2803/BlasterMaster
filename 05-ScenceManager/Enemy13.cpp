#include "Enemy13.h"
#include "Utils.h"
#include "Brick2.h"
#include "BrickNoColli.h"

Enemy13::Enemy13()
{
	state = ENEMY13_STATE_IDLE;
}

void Enemy13::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state != STATE_DIE)
	{
		left = x;
		top = y;
		right = x + ENEMY13_BBOX_WIDTH;
		bottom = y + ENEMY13_BBOX_HEIGHT;
	}
}

void Enemy13::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	for (int i = 0; i < bullets.size(); i++)
		if (bullets[i]->GetState() == BULLET_STATE_DIE)
			bullets.erase(bullets.begin() + i);
	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->Update(dt, coObjects);
	x += vx * dt;
	if (x0 == 0)
		x0 = x;
	if (x < x0 - 200 && vx < 0)
	{
		x = x0 - 200;
		vx = -vx;
	}
	if (x > x0 && vx > 0)
	{
		x = x0;
		vx = -vx;
	}
	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->Update(dt, coObjects);
	timecount++;
	if (timecount >= 100)
	{
		Shoot();
		timecount = 0;
	}
}

void Enemy13::Render()
{
	int ani = get_hit;
	if (state == STATE_DIE)
	{
		return;
	}
	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->Render();
	RenderBoundingBox();
	animation_set->at(ani)->Render(x, y);

}

void Enemy13::SetState(int state)
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
void Enemy13::Shoot()
{
	Enemy11* newBullet;
	newBullet = new Enemy11(0, -1);
	newBullet->SetAnimationSet(bullet->animation_set);
	newBullet->SetPosition(x+20, y);
	bullets.push_back(newBullet);

}