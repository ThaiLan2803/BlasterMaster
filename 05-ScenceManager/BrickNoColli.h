#pragma once
#include "GameObject.h"

class BrickNoColli : public CGameObject
{

public:
	BrickNoColli() {
		IsNoColli = true;
	}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};