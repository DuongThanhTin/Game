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
#define OBJECT_TYPE_BRIDGE	8
#define OBJECT_TYPE_STAIR	9
#define OBJECT_TYPE_AREAACTIVE 10
#define OBJECT_TYPE_CANDLE 11
#define OBJECT_TYPE_SPEARKNIGHT	40
#define OBJECT_TYPE_BAT	41
#define OBJECT_TYPE_AREASWITCHCAM	90

#define OBJECT_TYPE_PORTAL	50
#define OBJECT_TYPE_WHIP 90
#define OBJECT_TYPE_DAGGER 91
#define OBJECT_TYPE_BOOMERANG 92

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

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex, flipimage, { x,y });
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
		int frame_time = atoi(tokens[i + 1].c_str());
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
			DebugOut(L"[ERROR] SIMON object was created before!\n");
			return;
		}

		obj = new CSimon();
		player = (CSimon*)obj;
		DebugOut(L"[INFO] Player object created!\n");
		obj->SetPosition(x, y);
		break;
	case OBJECT_TYPE_SPEARKNIGHT:
	{
		int itemId = atoi(tokens[4].c_str());
		float limitedLeft = atoi(tokens[5].c_str());
		float limitedRight = atoi(tokens[6].c_str());
		obj = new CSpearKnight({ x,y }, itemId, limitedLeft, limitedRight);
		break;
	}
	case OBJECT_TYPE_BAT:
	{
		int itemId = atoi(tokens[4].c_str());
		float falldown = atoi(tokens[5].c_str());
		int area_id = atoi(tokens[6].c_str());
		DebugOut(L"CBAT %d\n", area_id);
		obj = new CBat({ x,y }, 1, itemId, falldown, area_id);
		break;
	}
	case OBJECT_TYPE_BRIDGE:
	{
		float limitedLeft1 = atof(tokens[4].c_str());
		float limitedRight1 = atof(tokens[5].c_str());
		DebugOut(L"BRIDGE %d %d", limitedLeft1, limitedRight1);
		obj = new CBridge({x, y}, limitedLeft1, limitedRight1);
		break;
	}

	case OBJECT_TYPE_BRICK:
	{
		int width = atoi(tokens[4].c_str());
		int height = atoi(tokens[5].c_str());
		obj = new CBrick({ x,y + height + MAP_HUD }, width, height);
		DebugOut(L"Brick");
		break;
	}

	case OBJECT_TYPE_TORCH:
	{
		int height = atoi(tokens[5].c_str());
		int value = atoi(tokens[6].c_str());
		obj = new CTorch({ x,y + height + MAP_HUD }, value);
		DebugOut(L"Torch %d\n", value);
		break;
	}

	case OBJECT_TYPE_STAIR:
	{
		int width = atoi(tokens[4].c_str());
		int height = atoi(tokens[5].c_str());
		int nx = atoi(tokens[6].c_str());
		int ny = atoi(tokens[7].c_str());
		int longStair = atoi(tokens[8].c_str());
		obj = new CStair({ x,y + height + MAP_HUD }, width, height, longStair, nx, ny);
		//DebugOut(L"Torch %d\n", value);
		break;
	}

	case OBJECT_TYPE_AREAACTIVE:
	{
		int width = atoi(tokens[4].c_str());
		int height = atoi(tokens[5].c_str());
		int specEnemyActive = atoi(tokens[6].c_str());
		obj = new CAreaActive({ x,y + height + MAP_HUD }, width, height, specEnemyActive);
		break;
	}

	case OBJECT_TYPE_CANDLE:
	{
		int height = atoi(tokens[5].c_str());
		int value = atoi(tokens[6].c_str());
		obj = new CCandle({ x,y + height + MAP_HUD }, value);
		DebugOut(L"Candle %d\n", value);
		break;
	}

	case OBJECT_TYPE_AREASWITCHCAM:
	{
		int width = atoi(tokens[4].c_str());
		int height = atoi(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		int player_x = atoi(tokens[7].c_str());
		int player_y = atoi(tokens[8].c_str());
		obj = new CAreaSwitchCam({ x,y + height + MAP_HUD }, width, height, scene_id, player_x, player_y);
		DebugOut(L"CAreaSwitchCam %d\n", scene_id);
		break;
	}

	//Portal
	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
		DebugOut(L"[NICE PORTAL]!\n");
		obj->SetPosition(x, y);
		break;
	}

	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);
	obj->SetAnimationSet(ani_set);
	objects.push_back(obj);
}



//MAP
void CPlayScene::_ParseSection_MAP_SCENE(string line)
{
	DebugOut(L"[MAP]");
	vector<string> tokens = split(line);
	if (tokens.size() < 1) return;
	wstring path = ToWSTR(tokens[0]);
	DebugOut(L"[INFO] Done loading scene resources %s\n", path.c_str());
	tileSet->LoadFromFile(path.c_str());
	DebugOut(L"[DONE1] Done loading tileSet\n");
	tileMap->LoadFromFile(path.c_str());
	DebugOut(L"[DONE2] Done loading tileMap\n");
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
			section = SCENE_SECTION_OBJECTS; continue;
		}
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
	if (player == NULL) return;
	if (player->GetLockUpdate() > 0)
	{
		objects[0]->Update(dt, &coObjects);
		return;
	}

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
	viewport->Update(playerPosition, 0, tileMap->GetLimitedViewPort());


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
			float sl, st, sr, sb;		// simon bbox
			iter->GetBoundingBox(pl, pt, pr, pb);
			player->GetBoundingBox(sl, st, sr, sb);
			if (CGame::GetInstance()->IsIntersectAABB({ long(pl),long(pt), long(pr), long(pb) }, { long(sl), long(st), long(sr), long(sb) })) {
				if (iter->GetID() == ID_PORTAL) {
					CPortal* portal = dynamic_cast<CPortal *>(iter);
					DebugOut(L"TEST SWITCH SCENE %d\n", portal->GetSceneId());
					switch (portal->GetSceneId())
					{
					case SCENE_1:
						DebugOut(L"TEST SCENE 1!\n");
						ScenePortal(SCENE_1, 0, 0);
						break;
					case SCENE_2:
 						DebugOut(L"TEST SCENE 2!!\n");
						ScenePortal(SCENE_2, CAMERA_SWITCHSCENE2_X, CAMERA_SWITCHSCENE2_Y);
						break;
					case SCENE_3:
						DebugOut(L"TEST SCENE 3!!\n");
						ScenePortal(SCENE_3, 0, 0);
						break;
					default:
						break;
					}
				}
			}

			if (iter->GetID() == ID_PORTAL) {
				CPortal* portal = dynamic_cast<CPortal *>(iter);
				float x, y;
				player->GetPosition(x, y);
				switch (portal->GetSceneId())
				{
				//SCENE 1 have NEXT SCENE 2, case is: "NEXT SCENE"
				case SCENE_2://NEXT SCENE
					viewport->Update(playerPosition, 0, tileMap->GetLimitedViewPort());
					break;
				case SCENE_3: 
					DebugOut(L"SCENE 2\n");
					if (y > SCENE2_SIMON_SWITCH_Y && !player->GetSwitchCam())
					{
						ChangeView(playerPosition, { x,y }, { x,CAMERA_SWITCHSCENE2_Y }, CAMERA_SCENE2_X);
					}
					else if (y < SCENE2_SIMON_SWITCH_Y && player->GetSwitchCam())
					{
						ChangeView(playerPosition, { x,y }, { x,CAMERA_SWITCH_SCENE2_1_Y }, 0);
					}
					else
						ChangeView(playerPosition, { x,y }, { x,CAMERA_SWITCHSCENE2_Y }, CAMERA_SCENE2_X);
					break;
				case SCENE_4:
					if (y > SCENE3_SIMON_SWITCH_Y)
					{
						ChangeView(playerPosition, { x,y }, { x,CAMERA_SWITCHSCENE2_Y }, 0);
					}
					else
					{
						ChangeView(playerPosition, { x,y }, { x,CAMERA_SWITCH_SCENE2_1_Y }, 0);
					}
					
					break;
				default:
				
					break;
				}
			}
		}
	}

}

void CPlayScene::ChangeView(D3DXVECTOR2 playerPosition, D3DXVECTOR2 setPlayerPosition, D3DXVECTOR2 cameraPosition, int cameraStart)
{
	player->SetPosition(setPlayerPosition.x, setPlayerPosition.y);
	viewport->SetPosition({ cameraPosition.x, cameraPosition.y });
	viewport->Update(playerPosition, cameraStart, tileMap->GetLimitedViewPort());
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

	//viewport->Render();
	//Render Simon
	objects[0]->Render();
}

/*
Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetID()==ID_SIMON)
		{
			;
		}
		else
			delete objects[i];
	}

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScene::ScenePortal(int scene_id, float view_x, float view_y)
{
	CViewPort * viewport = CViewPort::GetInstance();
	CGame *game = CGame::GetInstance();
	game->SwitchScene(scene_id);
	viewport->SetPosition({ view_x,view_y });
}


void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	CGame *game = CGame::GetInstance();
	//SIMON
	CSimon *simon = ((CPlayScene*)scence)->GetPlayer();
	if (simon->GetLockUpdate() > 0 )
		return;
	
	if (simon->GetState() == SIMON_STATE_EATITEM)
		return;

	switch (KeyCode)
	{
	case DIK_SPACE:
		if (simon->GetState() != SIMON_STATE_JUMP && simon->GetState() != SIMON_STATE_ATTACK && simon->GetState() != SIMON_STATE_ATTACK_SUBWEAPON && !(simon->IsOnStair()))
			simon->StartJump();
		break;
	case DIK_X:
		if (simon->IsOnStair() && (game->IsKeyDown(DIK_UP) || game->IsKeyDown(DIK_DOWN) || game->IsKeyDown(DIK_LEFT) || game->IsKeyDown(DIK_RIGHT)))
			return;

		simon->StartAttack();
		break;
	case DIK_C:
		if (simon->IsOnStair() && (game->IsKeyDown(DIK_UP) || game->IsKeyDown(DIK_DOWN) || game->IsKeyDown(DIK_LEFT) || game->IsKeyDown(DIK_RIGHT)))
			return;
		simon->StartAttackSub();
		break;

	case DIK_A: // reset
		simon->Reset(START_X, START_Y);
		break;

		//Switch scene with key
	case DIK_1:
		DebugOut(L"SCENE 1\n");
		OnKeySwitchScene(SCENE_1, 0, 0);
		break;

	case DIK_2:
		DebugOut(L"SCENE 2\n");
		OnKeySwitchScene(SCENE_2, CAMERA_SWITCHSCENE2_X, CAMERA_SWITCHSCENE2_X);
		break;
	case DIK_3:
		DebugOut(L"SCENE 3\n");
		OnKeySwitchScene(SCENE_3, 0, 0);
		break;
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	CSimon *simon = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_DOWN:
	case DIK_UP:
	case DIK_LEFT:
	case DIK_RIGHT:
		if (simon->IsOnStair())
		{
			simon->SetSpeed(0, 0);
		}
		break;
	default:
		break;
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CSimon *simon = ((CPlayScene*)scence)->GetPlayer();

	// disable control key when Simon die 
	if (simon->GetState() == SIMON_STATE_DIE)
		return;
	if (simon->GetAttackStart() > 0 || simon->GetJumpStart() > 0 || simon->GetAttackStartSub() > 0)
		return;

	if (simon->IsOnStair())
		simon->SetState(SIMON_STATE_IDLE_STAIR);
	else
		simon->SetState(SIMON_STATE_IDLE);

	if ( game->IsKeyDown(DIK_UP) && (game->IsKeyDown(DIK_LEFT)|| game->IsKeyDown(DIK_RIGHT)))
	{
		simon->SetSpeed(0, 0);
		return;
	}


	// KEY DOWN
	if (game->IsKeyDown(DIK_DOWN))
	{
		if (simon->IsOnStair())
		{
			simon->SetState(SIMON_STATE_GODOWN_STAIR);
		}
		else if (simon->GetCollidingStair())
		{
			if (simon->GetCollidingStair()->GetNy() < 0 && ((simon->GetCollidingStair()->x - STAIR_SETBBOX_LEFT <= simon->x) && (simon->x <= simon->GetCollidingStair()->x + STAIR_SETBBOX_RIGHT)) && (simon->GetCollidingStair()->y + STAIR_ANCHOR_SIMON >= simon->y))//Top
			{
				float x, y;
				simon->GetPosition(x, y);
				simon->SetPosition(simon->GetCollidingStair()->x - (SIMON_BBOX_WIDTH - STAIR_ANCHOR_SIMON) / 2, y + STAIR_ANCHOR_SIMON); //Neo điểm Simon để xuống cầu thang 
				simon->SetState(SIMON_STATE_GODOWN_STAIR);
			}
			else
				simon->SetState(SIMON_STATE_SIT);
		}
		else
			simon->SetState(SIMON_STATE_SIT);
	}

	// KEY UP
	if (game->IsKeyDown(DIK_UP))
	{
		if (simon->IsOnStair())
		{
			simon->SetState(SIMON_STATE_GOUP_STAIR);
		}
		else if (simon->GetCollidingStair())
		{
			if (simon->GetCollidingStair()->GetNy() > 0 && ((simon->GetCollidingStair()->x - STAIR_SETBBOX_LEFT <= simon->x) && (simon->x <= simon->GetCollidingStair()->x + STAIR_SETBBOX_RIGHT)) && (simon->GetCollidingStair()->y + STAIR_ANCHOR_SIMON >= simon->y))//Bottom
			{
				float x, y;
				simon->GetPosition(x, y);
				simon->SetPosition(simon->GetCollidingStair()->x + 2, y); //Neo điểm Simon để lên cầu thang 
				simon->SetState(SIMON_STATE_GOUP_STAIR);
			}
		}
	}
	//KEY RIGHT
	if (game->IsKeyDown(DIK_RIGHT))
		if (simon->IsOnStair())
			if (simon->GetCollidingStair()->GetNx() > 0)
				simon->SetState(SIMON_STATE_GOUP_STAIR);
			else
				simon->SetState(SIMON_STATE_GODOWN_STAIR);
		else
			simon->SetState(SIMON_STATE_WALKING_RIGHT);

	//KEY LEFT
	if (game->IsKeyDown(DIK_LEFT))
		if (simon->IsOnStair())
			if (simon->GetCollidingStair()->GetNx() < 0)
				simon->SetState(SIMON_STATE_GOUP_STAIR);
			else
				simon->SetState(SIMON_STATE_GODOWN_STAIR);
		else
			simon->SetState(SIMON_STATE_WALKING_LEFT);
}


void CPlayScenceKeyHandler::OnKeySwitchScene(int scene_id, float view_x, float view_y)
{
	CViewPort * viewport = CViewPort::GetInstance();
	CGame *game = CGame::GetInstance();
	game->SwitchScene(scene_id);
	viewport->SetPosition({ view_x,view_y });
}