#pragma once
#include "GameObject.h"
#define SCREEN_WH	100
#define SCREEN_HH	100
#define W	8
#define H	48
class HealthBar : public CGameObject
{
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt);
	virtual void Render();
	virtual void SetState(int state) { this->state = state; }
	void Render(float a, float b, int ani_id);
};