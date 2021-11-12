#pragma once
#include "GameObject.h"

#define LAN_WALKING_SPEED 0.15f;

#define LAN_BBOX_WIDTH	24
#define LAN_BBOX_HEIGHT 18


#define LAN_STATE_WALKING 0

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define LAN_ANI_WALKING 0


class CLan : public CGameObject
{
	

public:
	CLan();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
};