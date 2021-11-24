#pragma once
#include "GameObject.h"

class CBackground : public CGameObject
{
	float width;
	float height;
public:
	CBackground();
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual Rect GetBoundingBox();
};