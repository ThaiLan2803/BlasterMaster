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
	float h_x, h_y;
	h_x = h_y = 0.0f;
	if (a - SCREEN_WH < 0)
		h_x = 0;
	else h_x = a - SCREEN_WH;
	if (b - SCREEN_HH < 0)
		h_y = H;
	else h_y = b - 30;
	if (ani_id < animation_set->size())
		animation_set->at(ani_id)->Render(h_x, h_y, alpha);
}

void HealthBar::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}