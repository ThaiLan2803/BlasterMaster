#pragma once
#include "GameObject.h"

class BottomCircle : public CGameObject
{
public:
	void LoadResources();
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};

