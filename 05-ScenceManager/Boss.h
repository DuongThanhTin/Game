#pragma once
#include "define.h"
#include "Enemy.h"
#include "GameObject.h"
#include "Hud.h"

#define BOSS_FLYING_SPEED 0.0015f

#define BOSS_BBOX_WIDTH 42
#define	BOSS_BBOX_HEIGHT 32

#define BOSS_STATE_SLEEP 100
#define BOSS_STATE_FLYING 200
#define BOSS_STATE_DIE 300

#define BOSS_ANI_IDLE_ 0
#define BOSS_ANI_FLYING_RIGHT 1

#define TIME_EFFECT_BOSS_DESTROYED 1500
class CBoss : public CGameObject
{
	float falldown;
	LPHUD hud;
	static CBoss* __instance;

	bool isDestroyed = false;
	int timeDestroyed;
public:
	//static CBoss* GetInstance();
	CBoss(D3DXVECTOR2 position, int nx, int nextItemID);
	~CBoss();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
};