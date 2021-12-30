//#pragma once
//#pragma warning
//#include "GameObject.h"
//#include "Sung.h"
//#include "BanhXe.h"
//#include "BottomCircle.h"
//#include "Rect.h"
//#include "Point.h"
//#include "Bullet.h"
//#include "HealthBar.h"
//
//#define SJASON_WALKING_SPEED		0.05f
//#define SJASON_JUMP_SPEED_Y		0.5f
//#define SJASON_GRAVITY			-0.009f
//
//#define SJASON_STATE_WALKING	100
//#define SJASON_STATE_JUMP			300
//
//#define SJASON_ANI_JUMP		0
//#define SJASON_ANI_WALK		1
//
//#define SJASON_BBOX_H			17
//#define SJASON_BBOX_W 			16
//#define SJASON_UNTOUCHABLE_TIME 			5000
//
//
//class SmallJason : public CGameObject
//{
//protected:
//	int untouchable;
//	DWORD untouchable_start;
//	float start_x;			// initial position of Mario at scene
//	float start_y;
//	int nyy;
//	vector<LPGAMEOBJECT> bullets;
//	~SmallJason();
//public:
//	bool Active = false;
//	SmallJason();
//	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
//	virtual void Render();
//
//	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
//	void SetState(int state);
//
//	void Reset();
//	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
//	SmallJason(float x = 0.0f, float y = 0.0f);
//	virtual void SetPosition(float x, float y) { this->x = x, this->y = y; }
//};
//
//
