#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Quadtree.h"


vector<vector<int>> MapTile;
vector<vector<vector<int>>> MapObj;
vector<LPGAMEOBJECT> objects, screenObj, actObj, moveObj;
vector<LPGAMEOBJECT>* coObj = new vector<LPGAMEOBJECT>();

LPDIRECT3DTEXTURE9 texMap1;
int lx, ly;
int Stage;
Point tf, br;
Quadtree* quadtree;

Quadtree* CPlayScene::CreateQuadtree(vector<LPGAMEOBJECT> list, Point p)
{
	// Init base game region for detecting collision
	Quadtree* quadtree = new Quadtree(1, new Rect(p - Point(5, 5) * 16, p + Point(5, 5) * 16));
	for (auto i = list.begin(); i != list.end(); i++)
		quadtree->Insert(*i);

	return quadtree;
}
void CPlayScene::UpdateActObj(Point p) {
	float cx = p.x, cy = p.y;
	int stx = int(cx / BRICK_HEIGHT) - 5, sty = int(cy / BRICK_WIDTH) - 5;
	if (stx < 0) stx = 0;
	if (sty < 0) sty = 0;
	actObj.clear();
	for (int y = sty; y < sty + 5 + SCREEN_HEIGHT / BRICK_HEIGHT && y < MapTile.size(); y++) {
		for (int x = stx; x < stx + 5 + SCREEN_WIDTH / BRICK_WIDTH && x < MapTile[y].size(); x++) {
			for (int i = 0; i < MapObj[y][x].size(); i++)
				if (MapObj[y][x][i] != -1)
					actObj.push_back(objects.at(MapObj[y][x][i]));
		}
	}
	//actObj.push_back(&trigg);
}
void CPlayScene::UpdateObj(CGameObject* obj, DWORD dt) {
	vector<LPGAMEOBJECT>* _coObj = new vector<LPGAMEOBJECT>();

	float cx, cy;
	player->GetPosition(cx, cy);

	float x, y;

	obj->GetPosition(x, y);

	UpdateActObj(Point(x, y));

	quadtree = CreateQuadtree(actObj, Point(x, y));

	quadtree->Retrieve(_coObj, obj);

	_coObj->push_back(player);

	obj->Update(dt, _coObj);

	quadtree->~Quadtree();
}

using namespace std;

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

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
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

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());
	float x1 = atof(tokens[1].c_str());
	float y1 = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());

	
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_BACKGROUND:
		obj = new CBackground();
		break;
	case OBJECT_TYPE_TANK:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CTank(x,y); 
		player = (CTank*)obj;  

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_BRICK:
		obj = new CBrick();
		DebugOut(L"[INFO] Brick object created!\n");
		break;
	case OBJECT_TYPE_BANHXE:
		if (bx != NULL)
		{
			DebugOut(L"[ERROR] Banh xe object was created before!\n");
			return;
		}
		obj = new BanhXe();
		bx = (BanhXe*)obj;
		player->SetBanhXe(bx);
		//DebugOut(L"Create Object type: %d\n", object_type);
		break;
	case OBJECT_TYPE_GUN:
		obj = new Sung();
		s = (Sung*)obj;
		player->SetSung(s);
		//DebugOut(L"Create Object type: %d\n", object_type);
		break;
//	case OBJECT_TYPE_LAN:
//		if (lan != NULL)
//		{
//			DebugOut(L"[ERROR] MARIO object was created before!\n");
//			return;
//		} 
//		obj = new CLan();
//
//		DebugOut(L"[INFO] Player object created!\n");
//		break;

	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	DebugOut(L"Obj: %d , Ani_set_id: %d", object_type, ani_set_id);
	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
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
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	float cx, cy;
	coObj->clear();
	player->GetPosition(cx, cy);

	UpdateActObj(Point(cx, cy));
	quadtree = CreateQuadtree(actObj, Point(cx, cy));

	
	player->GetPosition(cx, cy);
	coObj->push_back(player);
	for (size_t i = 0; i < objects.size(); i++)
	{
		coObj->push_back(objects[i]);
	}

	quadtree->Retrieve(coObj, player);

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, coObj);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	player->Update(dt, coObj);
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= game->GetScreenHeight() / 2;
	CGame::GetInstance()->SetCamPos(player);
	
}

void CPlayScene::Render()
{
	for (int i = 0; i < coObj->size(); i++)
		coObj->at(i)->Render();
}

void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CTank *tank = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_SPACE:
		tank->SetState(TANK_STATE_JUMP);
		break;
	case DIK_A: 
		tank->Reset();
		break;
	}
}
void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CTank *tank = ((CPlayScene*)scence)->GetPlayer();
	tank->SetState(TANK_STATE_IDLE);
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CTank *tank = ((CPlayScene*)scence)->GetPlayer();

	// disable control key when Mario die 
	if (tank->GetState() == TANK_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
		tank->SetState(TANK_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		tank->SetState(TANK_STATE_WALKING_LEFT);
	else if (game->IsKeyDown(DIK_UP))
		tank->SetState(TANK_STATE_WALKING_UP);
	else if (game->IsKeyDown(DIK_DOWN))
		tank->SetState(TANK_STATE_WALKING_DOWN);
//	else if (game->IsKeyDown(DIK_SPACE))
//		tank->SetState(TANK_STATE_JUMP);
	else
		tank->SetState(TANK_STATE_IDLE);
}