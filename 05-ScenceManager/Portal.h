#pragma once

#include "GameObject.h"

#define BOX_W 40
#define BOX_H 40
class CPortal : public CGameObject
{
	int scene_id;	

	int width;
	int height;
public:
	CPortal(float l, float t, float r, float b, int scene_id);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetSceneId() { return scene_id; }
};