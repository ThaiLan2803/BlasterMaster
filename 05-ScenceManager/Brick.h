#pragma once
#include "GameObject.h"

class CBrick : public CGameObject
{
	float width;
	float height;
public:
	CBrick(float, float);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual Rect GetBoundingBox();
};