#include "Bullet.h"
#include "Utils.h"
Bullet::Bullet(int nx)
{
	vx = 0.9*nx;
}
void Bullet::Render()
{
		int ani;
			if (vx > 0)
				ani = DAN_ANI_RIGHT;
			else
				ani = DAN_ANI_LEFT;
		//if (animation_set)
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void Bullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BULLET_WIDTH;
	b = y + BULLET_HEIGHT;
}

void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	x += vx * dt;
	//y += 0.1;
}