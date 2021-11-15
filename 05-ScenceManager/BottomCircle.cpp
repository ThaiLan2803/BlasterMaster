#include "BottomCircle.h"
#include "Textures.h"

#define ID_TEX_BOTTOMCIRCLE		20

void BottomCircle::Update(DWORD dt)
{
	CGameObject::Update(dt);
}

void BottomCircle::Render()
{
	animation_set->at(0)->Render(x, y);
}

void BottomCircle::SetState(int state)
{
	CGameObject::SetState(state);
}
