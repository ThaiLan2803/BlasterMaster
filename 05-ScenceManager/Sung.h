#pragma once
#include "GameObject.h"

#define SUNG_ANI_IDLE_RIGHT		0
#define SUNG_ANI_IDLE_LEFT		1

#define SUNG_STATE_RIGHT		0
#define SUNG_STATE_LEFT			100

#define SUNG_WALKING_SPEED		0.15f

class Sung : public CGameObject
{
public:
	void LoadResources();
	void Update(DWORD dt);
	void NewRender(float x, float y);
	void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual Rect GetBoundingBox();
	void Render();
};
