#pragma once
#include "GameObject.h"

#define JASON_WALKING_SPEED		0.1f
#define JASON_JUMP_SPEED_Y		0.53f
#define JASON_GRAVITY			0.0026f

#define JASON_WIDTH 8.0f
#define JASON_HEIGHT 16.0f

enum JasonState
{
	JASON_IDLE,
	JASON_WALKING_LEFT,
	JASON_WALKING_RIGHT,
	JASON_JUMPING
};

class CJason : public CGameObject
{
protected:
	JasonState state;

public:
	CJason();
	~CJason();
	void SetState(JasonState state);

	void Update(DWORD dt);
	void Render();
};