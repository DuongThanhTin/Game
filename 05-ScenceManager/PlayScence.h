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

class CPlayScene: public CScene
{
protected: 
	//CMario *player;					// A play scene has to have player, right? 
	CSimon *player;
	vector<LPGAMEOBJECT> objects;
	CGameObject *obj = NULL;
	CTileSet *tileSet;
	CTileMap *tileMap;
	CViewPort *viewport;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP_SCENE(string line);
public:
	CPlayScene();
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

