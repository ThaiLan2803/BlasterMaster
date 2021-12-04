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
	int ani;
	if (vx == 0) ani = BANHXE_STATE_IDLE;
	else
		if (vx > 0)
			ani = BANHXE_ANI_WALKING_RIGHT;
		else
			ani = BANHXE_ANI_WALKING_LEFT;
	//if (animation_set)
		animation_set->at(ani)->Render(x, y);
	//else

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
	case BANHXE_STATE_UP:
		vy = -BANHXE_WALKING_SPEED;

	case BANHXE_STATE_IDLE:
		vx = 0, vy =0;
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
	/*r = x + this->w;
	b = y + this->h;*/
}
