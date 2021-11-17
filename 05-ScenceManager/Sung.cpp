#include "Sung.h"
#include "Textures.h"
#include "Rect.h"


#define ID_TEX_SUNG_RIGHT			30
#define ID_TEX_SUNG_LEFT 			31

void Sung::Update(DWORD dt)
{
	CGameObject::Update(dt);
}

void Sung::NewRender(float x, float y)
{
	//int ani;
	//if (nx > 0) ani = SUNG_ANI_IDLE_RIGHT;
	//else ani = SUNG_ANI_IDLE_LEFT;
	//animation_set->at(0)->Render(x, y);
	//DebugOut(L"Render sung");
	
}
void Sung::Render()
{

}

void Sung::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SUNG_STATE_RIGHT:
		nx = 1;
		break;
	case SUNG_STATE_LEFT:
		nx = -1;
		break;
	}


}
void Sung::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	/*left = x;
	top = y;
	right = x + TANK_BBOX_WIDTH;
	bottom = y + TANK_BBOX_HEIGHT;*/
}


Rect Sung::GetBoundingBox()
{
	return Rect(Point(x, y + 6), 0,0);
	//return CGameObject::GetBoundingBox();
}

void Sung::LoadResources()
{

}