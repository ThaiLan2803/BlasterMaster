#include "BanhXe.h"
#include "Textures.h"
#include "Utils.h"

#define ID_TEX_BANHXE_RIGHT			40
#define ID_TEX_BANHXE_LEFT 			41

void BanhXe::Update(DWORD dt)
{
	CGameObject::Update(dt);
	x += vx * dt;
	y += vy * dt;
}

void BanhXe::Render()
{
	
}

void BanhXe::NewRender(float x, float y)
{
	int ani = -1;
	if (nx > 0)
		ani = BANHXE_ANI_WALKING_RIGHT;
	else
		ani = BANHXE_ANI_WALKING_LEFT;


	int alpha = 255;
	if (untouchable) alpha = 128;
	//if (animation_set)
		animation_set->at(ani)->Render(x, y, 255);
	//else
		DebugOut(L"Render banhxe");
}

void BanhXe::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BANHXE_STATE_WALKING_RIGHT:
		vx = BANHXE_WALKING_SPEED;
		nx = 1;
		break;
	case BANHXE_STATE_WALKING_LEFT:
		vx = -BANHXE_WALKING_SPEED;
		nx = -1;
		break;
	case BANHXE_STATE_JUMP:
		vy = -BANHXE_WALKING_SPEED;

	case BANHXE_STATE_IDLE:
		vx = 0;
		break;

	case BANHXE_STATE_DOWN:
		vy = BANHXE_WALKING_SPEED;
		break;
	}


}
void BanhXe::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + this->w;
	b = y + this->h;
}
//void BanhXe::GetBoundingBox(float &left, float &top, float &right, float &bottom)
//{
//	/*left = x;
//	top = y;
//	right = x + TANK_BBOX_WIDTH;
//	bottom = y + TANK_BBOX_HEIGHT;*/
//}

Rect BanhXe::GetBoundingBox()
{
	return Rect(Point(x, y + 6), 0, 0 - 1);
	//return new Rect();
}

