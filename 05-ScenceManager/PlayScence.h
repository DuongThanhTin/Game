#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Simon.h"
#include "Whip.h"
#include "Zombie.h"
#include "Torch.h"
#include "Heart.h"
#include "Weapon.h"
#include "TileMap.h"
#include "ObjectNoMove.h"
#include "ListItem.h"
#include "Whip.h" 
#include "SpearKnight.h"
#include "Candle.h"
#include "Bat.h"
#include "AreaActive.h"
#include "Bridge.h"
#include "AreaSwitchCam.h"
#include "Hud.h"
#include "HideBrick.h"
#include "CrownItem.h"
#include "Rock.h"
#include "Fleaman.h"
#include "Skeleton.h"
#include "Fleaman.h"
#include "Ghost.h"
#include "Raven.h"
#include "Grid.h"

class CPlayScene: public CScene
{
protected: 
	//CMario *player;					// A play scene has to have player, right? 
	CSimon *player;
	CSimon *playersub;

	CGameObject *obj = NULL;
	CTileSet *tileSet;
	CTileMap *tileMap;
	CViewPort *viewport;
	CListItem *listItem;
	CHideBrick *hidebrick;
	CGrid *grid;
	LPHUD hud;

	int start_x = 0;
	int start_y = 180;

	void Loadinfo_OBJECTS(LPCWSTR path);
	void _ParseSection_INFO_OBJECTS_GENERAL(string line);
	void _ParseSection_INFO_OBJECTS(string line);
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP_SCENE(string line);
public:
	vector<LPGAMEOBJECT> objects;
	CPlayScene();
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual void ScenePortal(int scene_id, float view_x, float view_y);
	virtual void ChangeView(D3DXVECTOR2 playerPosition, D3DXVECTOR2 setPlayerPosition, D3DXVECTOR2 cameraPosition, int cameraStart);
	CSimon * GetPlayer() { return player; }

	friend class CPlayScenceKeyHandler;
};


class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	virtual void OnKeySwitchScene(int scene_id, float view_x, float view_y);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

