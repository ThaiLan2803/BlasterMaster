#include "Jason.h"



CJason::~CJason()
{
}

void CJason::SetState(JasonState state)
{
	switch (state)
	{
	case JASON_IDLE:
		break;
	case JASON_WALKING_LEFT:
		break;
	case JASON_WALKING_RIGHT:
		break;
	case JASON_JUMPING:
		break;
	default:
		break;
	}
}

void CJason::Update(DWORD dt)
{
	
	
}

void CJason::Render()
{
	
}


