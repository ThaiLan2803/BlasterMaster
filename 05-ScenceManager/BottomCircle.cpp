#include "BottomCircle.h"
#include "Textures.h"
#include "Rect.h"

#define ID_TEX_BOTTOMCIRCLE		20

void BottomCircle::Update(DWORD dt)
{
	CGameObject::Update(dt);
}

void BottomCircle::Render()
{
	//animation_set->at(0)->Render(x, y);
}

void BottomCircle::NewRender(float a, float b)
{
	animation_set->at(0)->Render(a, b);
}

void BottomCircle::SetState(int state)
{
	CGameObject::SetState(state);
}
void BottomCircle::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	/*left = x;
	top = y;
	right = x + TANK_BBOX_WIDTH;
	bottom = y + TANK_BBOX_HEIGHT;*/
}


Rect BottomCircle::GetBoundingBox()
{
	return Rect(Point(x, y + 6), 0, 0);
	//return CGameObject::GetBoundingBox();
}

void BottomCircle::LoadResources()
{

}