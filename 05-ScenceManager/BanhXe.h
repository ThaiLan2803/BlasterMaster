#pragma once
#include "GameObject.h"

#define BANHXE_ANI_IDLE_RIGHT		2
#define BANHXE_ANI_IDLE_LEFT			3
#define BANHXE_ANI_WALKING_RIGHT		4
#define BANHXE_ANI_WALKING_LEFT		5

#define BANHXE_WALKING_SPEED		0.1f

#define BANHXE_STATE_IDLE			0
#define BANHXE_STATE_WALKING_RIGHT	100
#define BANHXE_STATE_WALKING_LEFT	200
#define BANHXE_STATE_JUMP			300
#define BANHXE_STATE_DOWN			400

class BanhXe : public CGameObject
{
	int untouchable;
	int w, h;
public:
	void LoadResources();
	void Update(DWORD dt);
	void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual Rect GetBoundingBox();
	void SetState(int state);
	void NewRender(float x, float y);
};

