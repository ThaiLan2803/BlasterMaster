#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Brick2.h"
#include "Brick3.h"
#include "Tank.h"
#include "Lan.h"
#include "Background.h"
#include "BanhXe.h"
#include "Sung.h"
#include "BottomCircle.h"
#include "Background.h"
#include "Quadtree.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Enemy5.h"
#include "Enemy6.h"
#include "Enemy7.h"
#include "Enemy8.h"
#include "Enemy9.h"
#include "Enemy10.h"
#include "Enemy12.h"
#include "Enemy13.h"
#include "Enemy14.h"
#include "BrickNoColli.h"
#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6

#define OBJECT_TYPE_TANK	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_JASON		2
#define OBJECT_TYPE_BANHXE	3
#define OBJECT_TYPE_GUN		4
#define OBJECT_TYPE_BACKGROUND		5
#define OBJECT_TYPE_BTC		6
#define OBJECT_TYPE_ENEMY1	7
#define OBJECT_TYPE_ENEMY2	8
#define OBJECT_TYPE_ENEMY3	9
#define OBJECT_TYPE_ENEMY4	10
#define OBJECT_TYPE_ENEMY5	11
#define OBJECT_TYPE_ENEMY6	12
#define OBJECT_TYPE_ENEMY7	13
#define OBJECT_TYPE_BULLET	14
#define OBJECT_TYPE_PORTAL	15
#define OBJECT_TYPE_ENEMY8	16
#define OBJECT_TYPE_ENEMY9	17
#define OBJECT_TYPE_ENEMY10	18
#define OBJECT_TYPE_ENEMY12	19
#define OBJECT_TYPE_ENEMY13	20
#define OBJECT_TYPE_ENEMY14	21
#define	OBJECT_TYPE_BRICK2	1001
#define	OBJECT_TYPE_BRICK3	1002
#define	OBJECT_TYPE_BRICKNOCOLLI	1003
#define MAX_SCENE_LINE 1024


#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

#define BRICK_WIDTH 32
#define BRICK_HEIGHT 32

#define BULLET_DISTANCE	10

class CPlayScene: public CScene
{
protected: 
	CTank *player;					// A play scene has to have player, right? 
	CLan *lan;
	CBackground* bg;
	BanhXe *bx;
	Sung *s;
	BottomCircle *bc;
	int lx, ly;
	int Stage;
	int tank_previous_state = 0;
	Quadtree* quadtree;
	Bullet* bullet;
	vector<LPGAMEOBJECT> objects;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);

	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CTank * GetPlayer() { return player; }
	
	Quadtree* CreateQuadtree(vector<LPGAMEOBJECT> list);
	void UpdateActObj(Point p);
	void UpdateObj(CGameObject* obj, DWORD dt);
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

