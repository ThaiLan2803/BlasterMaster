#include "BanhXe.h"
#include "Textures.h"
#include "Game.h"

#define ID_TEX_WHEEL_RIGHT			40
#define ID_TEX_WHEEL_LEFT 			41

void Wheel::Update(DWORD dt)
{
	CGameObject::Update(dt);
	x += vx * dt;
	y += vy * dt;
}

void Wheel::Render()
{
	int ani;
	int alpha = 255;
	if (nx > 0) ani = WHEEL_ANI_IDLE_RIGHT;
	else ani = WHEEL_ANI_IDLE_LEFT;
	animation_set->at(0)->Render(x, y);
}

void Wheel::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WHEEL_STATE_WALKING_RIGHT:
		vx = WHEEL_WALKING_SPEED;
		nx = 1;
		break;
	case WHEEL_STATE_WALKING_LEFT:
		vx = -WHEEL_WALKING_SPEED;
		nx = -1;
		break;
	case WHEEL_STATE_JUMP:
		vy = -WHEEL_WALKING_SPEED;

	case WHEEL_STATE_IDLE:
		vx = 0;
		break;

	case WHEEL_STATE_DOWN:
		vy = WHEEL_WALKING_SPEED;
		break;
	}


}
