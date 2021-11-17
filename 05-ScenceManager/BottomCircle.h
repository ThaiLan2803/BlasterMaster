#pragma once
#include "GameObject.h"

class BottomCircle : public CGameObject
{
public:
	void LoadResources();
	void Update(DWORD dt);
	void Render();
	void NewRender(float x, float y);
	void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual Rect GetBoundingBox();
};

