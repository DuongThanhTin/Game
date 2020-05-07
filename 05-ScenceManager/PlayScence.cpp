#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
 

using namespace std;



CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
}
/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_INFO_OBJECTS 1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAP_URL	7


#define OBJECT_TYPE_SIMON	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_WHIP	4
#define OBJECT_TYPE_ZOMBIE	5
#define OBJECT_TYPE_TORCH	6
#define OBJECT_TYPE_HEART	7
#define OBJECT_TYPE_SPEARKNIGHT	40

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024

void CPlayScene::Loadinfo_OBJECTS(LPCWSTR path)
{
	ifstream f;
	f.open(path);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
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
		}
	}
	f.close();
}

void CPlayScene::_ParseSection_INFO_OBJECTS(string line)
{
	DebugOut(L"[INFO_OBJECTS]");
	vector<string> tokens = split(line);
	if (tokens.size() < 1) return;
	wstring path = ToWSTR(tokens[0]);

	DebugOut(L"[INFO] INFO_OBJECTS path: %s\n", path.c_str());
	Loadinfo_OBJECTS(path.c_str());
}

//TEXTURES
void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

//SPRITES
void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	/*if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());*/

	if (tokens.size() < 10) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());
	int flipimage = atoi(tokens[7].c_str());
	float x = atoi(tokens[9].c_str());
	float y = atoi(tokens[11].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID, flipimage);
		return; 
	}
	else {
		DebugOut(L"[OK] %d, %d \n", texID, flipimage);
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex,flipimage, { x,y });
}

//ANIMATIONS
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

//ANIMATIONS_SETS
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

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	DebugOut(L"[NICE OBJECTS]!\n");
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int ani_set_id = atoi(tokens[3].c_str());
	
	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	switch (object_type)
	{
	case OBJECT_TYPE_SIMON:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CSimon();
		player = (CSimon*)obj;
		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_SPEARKNIGHT:
		obj = new CSpearKnight();
		break;
	case OBJECT_TYPE_PORTAL:
		{	
			float r = atof(tokens[4].c_str());
			float b = atof(tokens[5].c_str());
			int scene_id = atoi(tokens[6].c_str());
			obj = new CPortal(x, y, r, b, scene_id);
			DebugOut(L"[NICE]!\n");
		}
		break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);
	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}

void CPlayScene::LoadMapSceneObjects(LPCWSTR path)
{
	ifstream file(path);
	json j = json::parse(file);
	LPANIMATION_SET ani_set;

	for (auto i : j["layers"])
	{
		if (i["name"] == "brick") {	// brick objects
			for (auto iter : i["objects"])
			{
				float x = iter["x"].get<float>();
				float y = iter["y"].get<float>();
				int width = iter["width"].get<int>();
				int height = iter["height"].get<int>();
				obj = new CBrick({ x,y + height + MAP_HUD }, width, height);
				objects.push_back(obj);
			}
		}
		else if (i["name"] == "torch") {	// torch objects
			for (auto iter : i["objects"])
			{
				float x = float(iter["x"]);
				float y = float(iter["y"]);
				int ani = iter["properties"][1]["value"].get<int>();
				int value = iter["properties"][0]["value"].get<int>();
				CAnimationSets * animation_sets = CAnimationSets::GetInstance();
				DebugOut(L"Torch %d %d\n", ani, value);
				obj = new CTorch({ x, y + iter["height"] + MAP_HUD }, value);
				ani_set = animation_sets->Get(ani);
				obj->SetAnimationSet(ani_set);
				objects.push_back(obj);
			}
		}
		else if (i["name"] == "candle") {	// candle objects
			for (auto iter : i["objects"])
			{
				float x = float(iter["x"]);
				float y = float(iter["y"]);
				int ani = iter["properties"][1]["value"].get<int>();
				int value = iter["properties"][0]["value"].get<int>();
				CAnimationSets * animation_sets = CAnimationSets::GetInstance();
				DebugOut(L"Candle %d %d\n", ani, value);
				obj = new CTorch({ x, y + iter["height"] + MAP_HUD }, value);
				ani_set = animation_sets->Get(ani);
				obj->SetAnimationSet(ani_set);
				objects.push_back(obj);
			}
		}
	}
}

//MAP
void CPlayScene::_ParseSection_MAP_SCENE(string line)
{
	DebugOut(L"[MAP]");
	vector<string> tokens = split(line);
	if (tokens.size() < 1) return;
	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	DebugOut(L"[INFO] Done loading scene resources %s\n", path.c_str());
	tileSet->LoadFromFile(path.c_str());
	DebugOut(L"[DONE1]\n");
	tileMap->LoadFromFile(path.c_str());
	DebugOut(L"[DONE2]\n");
	LoadMapSceneObjects(path.c_str());
}


//LOAD
void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);
	viewport = CViewPort::GetInstance();
	listItem = CListItem::GetInstance();

	tileMap = new CTileMap();
	tileSet = new CTileSet();

	ifstream f;
	f.open(sceneFilePath);
	
	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[INFOOBJECTS]")
		{
			section = SCENE_SECTION_INFO_OBJECTS; continue;
		}
		if (line == "[OBJECTS]") { 
			section = SCENE_SECTION_OBJECTS; continue; }
		if (line == "[MAP]") {
			section = SCENE_SECTION_MAP_URL; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{
			case SCENE_SECTION_INFO_OBJECTS: _ParseSection_INFO_OBJECTS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_MAP_URL: {
				DebugOut(L"SCENE_MAP\n");
				_ParseSection_MAP_SCENE(line); break;
			}
		}
	}

	f.close();
	listItem->ListItem.clear();
	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO_DONE_LOAD] Done loading scene resources  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way
	D3DXVECTOR2 playerPosition;
	vector<LPGAMEOBJECT> coObjects;
	

	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	for (int i = 0; i < listItem->ListItem.size(); i++) // update các Item
	{
		listItem->ListItem[i]->Update(dt, &coObjects);
		
	}


	for (int i = 1; i < objects.size(); i++)
	{
		if (objects[i]->GetState() == STATE_DESTROYED)
		{
			objects.erase(objects.begin() + i);
			i--;
		}
	}

	for (size_t i = 0; i < listItem->ListItem.size(); i++)
	{
		if (listItem->ListItem[i]->GetState() == STATE_DESTROYED)
		{
			listItem->ListItem.erase(listItem->ListItem.begin() + i);
			i--;
		}
	}

	
	// Update camera to follow simon
	player->GetPosition(playerPosition.x, playerPosition.y);
	if (playerPosition.x < 0) {
		player->SetPosition(0.0f, playerPosition.y);
	}

	//Giới hạn Camera
	viewport->Update(playerPosition, 0, TILESET_WIDTH*tileMap->GetLimitedViewPort());


	//SIMON Collision with portal
	vector<LPGAMEOBJECT> portalObjects;
	for (int i = 0;i < objects.size();i++) 
	{
		if (objects[i]->GetID() == ID_PORTAL)
			portalObjects.push_back(objects[i]);
	}

	//Collisions Portal
	for (auto iter : portalObjects) {
		{
			float pl, pt, pr, pb;		// portal bbox
			float sl, st, sr , sb;		// simon bbox
			iter->GetBoundingBox(pl, pt, pr, pb);
			player->GetBoundingBox(sl, st, sr, sb);
			if (CGame::GetInstance()->IsIntersect({ long(pl),long(pt), long(pr), long(pb) }, { long(sl), long(st), long(sr), long(sb) })) {
				if (iter->GetID() == ID_PORTAL) {
					CPortal* portal = dynamic_cast<CPortal *>(iter);
					DebugOut(L"TEST SWITCH SCENE %d\n", portal->GetSceneId());
					switch (portal->GetSceneId())
					{
					case KEY_1:
						DebugOut(L"TEST SCENE 1!\n");
						ScenePortal(SCENE_1, 0, 0);
						break;
					case KEY_2:
						DebugOut(L"TEST SCENE 2!!\n");
						ScenePortal(SCENE_2, 0, 10);
						break;
					default:
						break;
					}
				}
			}
		}
	}
}

void CPlayScene::Render()
{
	//Draw Map
	tileMap->DrawMap({ 0,0 });
		
	for (int i = 1; i < objects.size(); i++) {
		objects[i]->RenderBoundingBox(100);
		objects[i]->Render();
	}

	//Draw Items
	for (int i = 0; i < listItem->ListItem.size(); i++)
	{
		listItem->ListItem[i]->Render();
	}

	//Render Simon
	objects[0]->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScene::ScenePortal(int scene_id, float view_x, float view_y)
{
	CSimon *simon = new CSimon();
	CViewPort * viewport = CViewPort::GetInstance();
	CGame *game = CGame::GetInstance();

	game->SwitchScene(scene_id);
	simon->Reset();
	viewport->SetPosition({ view_x,view_y });
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	//MARIO
	/*CMario *mario = ((CPlayScene*)scence)->player;
	switch (KeyCode)
	{
	case DIK_SPACE:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_A: // reset
		mario->SetState(MARIO_STATE_IDLE);
		mario->SetLevel(MARIO_LEVEL_BIG);
		mario->SetPosition(50.0f, 0.0f);
		mario->SetSpeed(0, 0);
		break;
	}*/

	//SIMON
	CSimon *simon = ((CPlayScene*)scence)->GetPlayer();

	switch (KeyCode)
	{
	case DIK_SPACE:
		if (simon->GetState() != SIMON_STATE_JUMP && simon->GetState() != SIMON_STATE_ATTACK)
			simon->StartJump();
		break;
	case DIK_X:
		simon->StartAttack();
		break;

	case DIK_A: // reset
		simon->Reset();
		break;

	//Switch scene with key
	case DIK_1:
		DebugOut(L"SCENE 1\n");
		OnKeySwitchScene(SCENE_1, 0, 0);
		break;

	case DIK_2:
		DebugOut(L"SCENE 2\n");
		OnKeySwitchScene(SCENE_2, 0, 10);
		break;
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();

	CSimon *simon = ((CPlayScene*)scence)->GetPlayer();
		// disable control key when Mario die 
	if (simon->GetState() == SIMON_STATE_DIE)
		return;
	if (simon->GetAttackStart() > 0 || simon->GetJumpStart() > 0)
		return;

	if (game->IsKeyDown(DIK_RIGHT))
		simon->SetState(SIMON_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		simon->SetState(SIMON_STATE_WALKING_LEFT);
	else if (game->IsKeyDown(DIK_DOWN))
		simon->SetState(SIMON_STATE_SIT);
	else
		simon->SetState(SIMON_STATE_IDLE);
}


void CPlayScenceKeyHandler::OnKeySwitchScene(int scene_id,float view_x, float view_y)
{
	CSimon *simon = ((CPlayScene*)scence)->GetPlayer();
	CViewPort * viewport = CViewPort::GetInstance();
	CGame *game = CGame::GetInstance();
	game->SwitchScene(scene_id);
	simon->Reset();
	viewport->SetPosition({ view_x,view_y });
}