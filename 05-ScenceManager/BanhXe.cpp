#include "BanhXe.h"
#include "Textures.h"
#include "Utils.h"

#define ID_TEX_BANHXE_RIGHT			40
#define ID_TEX_BANHXE_LEFT 			41

void BanhXe::Update(DWORD dt)
{
	CGameObject::Update(dt);
	x += vx * dt;
	y += vy * dt;
}

void BanhXe::Render()
{
	
}

void BanhXe::NewRender(float x, float y)
{
	int ani = -1;
	if (vx == 0)
	{
		if (nx > 0) ani = 0;
		else ani = 1;
	}
	else if (vx > 0)
		ani = 2;
	else ani =3;


	int alpha = 255;
	if (untouchable) alpha = 128;
	//if (animation_set)
		animation_set->at(0)->Render(x, y, 255);
	//else
		DebugOut(L"Render banhxe");
}

void BanhXe::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BANHXE_STATE_WALKING_RIGHT:
		vx = BANHXE_WALKING_SPEED;
		nx = 1;
		break;
	case BANHXE_STATE_WALKING_LEFT:
		vx = -BANHXE_WALKING_SPEED;
		nx = -1;
		break;
	case BANHXE_STATE_JUMP:
		vy = -BANHXE_WALKING_SPEED;

	case BANHXE_STATE_IDLE:
		vx = 0;
		break;

	case BANHXE_STATE_DOWN:
		vy = BANHXE_WALKING_SPEED;
		break;
	}


}
void BanhXe::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + this->w;
	b = y + this->h;
}
//void BanhXe::GetBoundingBox(float &left, float &top, float &right, float &bottom)
//{
//	/*left = x;
//	top = y;
//	right = x + TANK_BBOX_WIDTH;
//	bottom = y + TANK_BBOX_HEIGHT;*/
//}

Rect BanhXe::GetBoundingBox()
{
	return Rect(Point(x, y + 6), 0, 0 - 1);
	//return new Rect();
}

void BanhXe::LoadResources()
{
	CTextures* textures = CTextures::GetInstance();

	textures->Add(ID_TEX_BANHXE_RIGHT, L"textures\\CarAndMainRight.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_BANHXE_LEFT, L"textures\\CarAndMainLeft.png", D3DCOLOR_XRGB(176, 224, 248));

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texBanhXeRight = textures->Get(ID_TEX_BANHXE_RIGHT);
	LPDIRECT3DTEXTURE9 texBanhXeLeft = textures->Get(ID_TEX_BANHXE_LEFT);

	sprites->Add(10001, 390, 21, 398, 29, texBanhXeRight);

	sprites->Add(10002, 399, 21, 407, 29, texBanhXeRight);
	sprites->Add(10003, 372, 21, 380, 29, texBanhXeRight);
	sprites->Add(10004, 381, 21, 389, 29, texBanhXeRight);


	sprites->Add(10011, 12, 21, 20, 29, texBanhXeLeft);

	sprites->Add(10012, 3, 21, 11, 29, texBanhXeLeft);
	sprites->Add(10013, 30, 21, 38, 29, texBanhXeLeft);
	sprites->Add(10014, 21, 21, 29, 29, texBanhXeLeft);


	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	animations->Add(401, ani);


	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	animations->Add(500, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	animations->Add(501, ani);

	//BanhXe::AddAnimation(400);		// idle right
	//BanhXe::AddAnimation(401);		// idle left
	//BanhXe::AddAnimation(500);		// walk right
	//BanhXe::AddAnimation(501);		// walk left
}