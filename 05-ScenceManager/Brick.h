#pragma once
#include "GameObject.h"
#define BRICK_BBOX_WIDTH  14
#define BRICK_BBOX_HEIGHT 10
class CBrick : public CGameObject
{
public:
//	void SetPosition(float x, float y) { this->x = x, this->y = 496 - y; }
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
//	virtual Rect GetBoundingBox();
};