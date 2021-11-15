#include "Sung.h"
#include "Textures.h"

#define ID_TEX_GUN_RIGHT			30
#define ID_TEX_GUN_LEFT 			31

void Gun::Update(DWORD dt)
{
	CGameObject::Update(dt);
}

void Gun::Render()
{
	int ani;
	if (nx > 0) ani = GUN_ANI_IDLE_RIGHT;
	else ani = GUN_ANI_IDLE_LEFT;
	animation_set->at(0)->Render(x, y);
}

void Gun::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GUN_STATE_RIGHT:
		nx = 1;
		break;
	case GUN_STATE_LEFT:
		nx = -1;
		break;
	}


}

