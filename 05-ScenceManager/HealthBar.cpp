#include "HealthBar.h"
#include "Utils.h"

void HealthBar::Update(DWORD dt)
{
	CGameObject::Update(dt);
	x += vx * dt;
	y += vy * dt;
}

void HealthBar::Render()
{
}

void HealthBar::Render(float a, float b, int ani_id)
{
	int alpha = 255;
	if (ani_id < animation_set->size())
		animation_set->at(ani_id)->Render(a, b, alpha);
}

void HealthBar::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}