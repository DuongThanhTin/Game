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
 
class CPlayScene: public CScene
{
protected: 
	//CMario *player;					// A play scene has to have player, right? 
	CSimon *player;

	CGameObject *obj = NULL;
	CTileSet *tileSet;
	CTileMap *tileMap;
	CViewPort *viewport;

	CListItem *listItem;

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

