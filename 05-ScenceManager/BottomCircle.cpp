#include "BottomCircle.h"
#include "Textures.h"

#define ID_TEX_BOTTOMCIRCLE		20

void BottomCircle::Update(DWORD dt)
{
	CGameObject::Update(dt);
	x += vx * dt;
	y += vy * dt;
}

void BottomCircle::Render()
{
}

void BottomCircle::NewRender(float a, float b)
{
	animation_set->at(0)->Render(a, b, 255);
}

void BottomCircle::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	right = y;
}


