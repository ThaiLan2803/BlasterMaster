#pragma once
#include "GameObject.h"
#include "Rect.h"
#define BTC_HEIGHT	8
#define BTC_WIDTH	8
class BottomCircle : public CGameObject
{
public:
	void Update(DWORD dt);
	void Render();
	void NewRender(float x, float y);
	void SetState(int state) { this->state = state; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual Rect GetBoundingBox();
};

