#include "Bullet.h"
#include "Utils.h"
Bullet::Bullet(int nx)
{
	vx = 0.9*nx;
}
void Bullet::Render()
{
	animation_set->at(0)->Render(x, y);
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