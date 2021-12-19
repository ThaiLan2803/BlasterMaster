#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Quadtree.h"
#include "Bullet.h"
#include "Portal.h"
using namespace std;
vector<vector<int>> MapTile;
vector<vector<vector<int>>> MapObj;
vector<LPGAMEOBJECT> objects, screenObj, actObj, moveObj;
vector<LPGAMEOBJECT>* coObj = new vector<LPGAMEOBJECT>();
vector<LPGAMEOBJECT>*p = new vector<LPGAMEOBJECT>();
LPDIRECT3DTEXTURE9 texMap1;

Quadtree* CPlayScene::CreateQuadtree(vector<LPGAMEOBJECT> entity_list)
{
	int count = 0;
	Quadtree* quadtree = new Quadtree(1, new Rect(0, 0, 1500, 1000));
	for (auto i = entity_list.begin(); i != entity_list.end(); i++)
	{
		count++;
		quadtree->Insert(*i);
	}
	return quadtree;
}


CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}




void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	DebugOut(L"ID tex: %d, size: %d", atoi(tokens[0].c_str()), tokens.size());
	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time


	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());
		
		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_BACKGROUND:
		obj = new CBackground();
		bg = (CBackground*)obj;
		break;
	case OBJECT_TYPE_TANK:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] TANK object was created before!\n");
			return;
		}
		obj = new CTank(x,y); 
		player = (CTank*)obj;  
		if (tank_previous_state != 0)
			player->SetState(tank_previous_state);
		break;
	case OBJECT_TYPE_JASON:
		if (player != NULL)
		{
			return;
		}
		obj = new CTank(x, y);
		player = (CTank*)obj;
		player->SetJason();
		if (tank_previous_state != 0)
			player->SetState(tank_previous_state);
		break;
	case OBJECT_TYPE_BRICK:
		obj = new CBrick();
		break;
	case OBJECT_TYPE_BRICK2:
		obj = new Brick2();
		break;
	case OBJECT_TYPE_BRICK3:
		obj = new Brick3();
		break;
	case OBJECT_TYPE_BRICKNOCOLLI:
		obj = new BrickNoColli();
		break;
	case OBJECT_TYPE_BANHXE:
		obj = new BanhXe();
		bx = (BanhXe*)obj;
		player->SetBanhXe(bx);
		break;
	case OBJECT_TYPE_GUN:
		obj = new Sung();
		s = (Sung*)obj;
		player->SetSung(s);
		break;
	case OBJECT_TYPE_BTC:
		obj = new BottomCircle();
		bc = (BottomCircle*)obj;
		player->SetBtc((BottomCircle*)obj);
		break;
	case OBJECT_TYPE_ENEMY1:
		obj = new Enemy1();
		break;
	case OBJECT_TYPE_ENEMY2:
		obj = new Enemy2();
		break;
	case OBJECT_TYPE_ENEMY3:
		obj = new Enemy3();
		break;
	case OBJECT_TYPE_ENEMY4:
		obj = new Enemy4();
		break;
	case OBJECT_TYPE_ENEMY5:
		obj = new Enemy5();
		break;
	case OBJECT_TYPE_ENEMY6:
		obj = new Enemy6();
		break;
	case OBJECT_TYPE_ENEMY7:
		obj = new Enemy7();
		break;
	case OBJECT_TYPE_ENEMY8:
		obj = new Enemy8();
		break;
	case OBJECT_TYPE_ENEMY9:
		obj = new Enemy9();
		break;
	case OBJECT_TYPE_ENEMY10:
		obj = new Enemy10();
		break;
	case OBJECT_TYPE_ENEMY12:
		obj = new Enemy12();
		break;
	case OBJECT_TYPE_ENEMY13:
		obj = new Enemy13();
		break;
	case OBJECT_TYPE_ENEMY14:
		obj = new Enemy14();
		break;
	case OBJECT_TYPE_BULLET:
		obj = new Bullet(0,0);
		player->SetBullet((Bullet*)obj);

		DebugOut(L"Set bulll");
		break;
	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		Stage = scene_id;
		obj = new CPortal(x, y, r, b, scene_id);
		break;
	}

	default:
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
//	DebugOut(L"Obj: %d , Ani_set_id: %d", object_type, ani_set_id);
	obj->SetAnimationSet(ani_set);
	switch (object_type)
	{
	case OBJECT_TYPE_TANK:
		break;
	case OBJECT_TYPE_GUN:
		break;
	case OBJECT_TYPE_BTC: 
		break;
	case OBJECT_TYPE_BANHXE: 
		break;
	case OBJECT_TYPE_BULLET:
		break;
	case OBJECT_TYPE_BRICKNOCOLLI:
		p->push_back(obj);
		break;
	case OBJECT_TYPE_BACKGROUND:
		break;
	default:
		objects.push_back(obj);
		return;
	}

}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") { 
			section = SCENE_SECTION_SPRITES; continue; }
		if (line == "[ANIMATIONS]") { 
			section = SCENE_SECTION_ANIMATIONS; continue; }
		if (line == "[ANIMATION_SETS]") { 
			section = SCENE_SECTION_ANIMATION_SETS; continue; }
		if (line == "[OBJECTS]") { 
			section = SCENE_SECTION_OBJECTS; 
			continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
			case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	coObj->clear();
	quadtree = CreateQuadtree(objects);
	quadtree->Retrieve(coObj, player);
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < coObj->size(); i++)
	{
		if (coObj->at(i)->IsEnable())
			coObj->at(i)->Update(dt, coObj);
		else
			coObj->erase(coObj->begin() + i);
	}
	if (player == NULL) return; 
	player->Update(dt, coObj);
	CGame::GetInstance()->SetCamPos(player);
	//quadtree->~Quadtree();
}

void CPlayScene::Render()
{
	if (bg)
		bg->Render();
	if (player)
		player->Render();
	for (int i = 0; i < p->size(); i++)
		if (p->at(i)->IsEnable())
			p->at(i)->Render();
		else
			p->erase(p->begin() + i);
	for (int i = 0; i < coObj->size(); i++)
		if (coObj->at(i)->IsEnable())
			coObj->at(i)->Render();
		else
			coObj->erase(coObj->begin() + i);
}

void CPlayScene::Unload()
{
	//if (player != NULL)
	//	tank_previous_state = player->GetState();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Disable();

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s loaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_A:
		CTank* tank = ((CPlayScene*)scence)->GetPlayer();
		tank->Shoot();
		break;
	}
}
void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CTank *tank = ((CPlayScene*)scence)->GetPlayer();
	tank->SetState(TANK_STATE_STOP);
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CTank *tank = ((CPlayScene*)scence)->GetPlayer();
 
	if (tank->GetState() == TANK_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
		tank->SetState(TANK_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		tank->SetState(TANK_STATE_WALKING_LEFT);
	else if (game->IsKeyDown(DIK_W))
		tank->SetState(TANK_STATE_DAN_UP);
	else if (game->IsKeyDown(DIK_UP))
		tank->SetState(JASON_STATE_WALKING_UP);
	else if (game->IsKeyDown(DIK_DOWN))
		tank->SetState(JASON_STATE_WALKING_DOWN);
	else if (game->IsKeyDown(DIK_SPACE))
		tank->SetState(TANK_STATE_JUMP);
	//else if (game->IsKeyDown(DIK_A))
	//	tank->Shoot();
	else
		tank->SetState(TANK_STATE_IDLE);
}