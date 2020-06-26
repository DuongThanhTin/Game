#pragma once
#include "define.h"
#include "Enemy.h"
#include "GameObject.h"
#include "Hud.h"
#include "CrystalBall.h"

#define BOSS_FLYING_SPEED 0.0015f

#define BOSS_BBOX_WIDTH 42
#define	BOSS_BBOX_HEIGHT 32
#define BOSS_SPEED_X 0.02
#define BOSS_SPEED_Y 0.03

#define BOSS_STATE_SLEEP 100
#define BOSS_STATE_FLYING 200
#define BOSS_STATE_DIE 300

#define BOSS_ANI_IDLE_ 0
#define BOSS_ANI_FLYING_RIGHT 1

#define POSITION_SCENE_GAMEOVER_Y 230
#define POSITION_SIMON_GAMEOVER_Y 300

#define ID_ANI_EFFECT_BOSS 991
#define ID_SPRITE_GAMEOVER 90090

#define TIME_EFFECT_BOSS_DESTROYED 1500
#define TIME_BOSS_IDLE 1500
#define TIME_BOSS_ATTACK 1000

class CBoss : public CGameObject
{
	float falldown;
	float default_x;
	float default_y;
	int limitedLeft;
	int limitedRight;
	int delta;
	LPHUD hud;
	vector<CCrystalBall *> crystalBalls;
	static CBoss* __instance;
	bool isDestroyed = false;
	bool isIdle = false;
	int timeDestroyed;
	int timeIdle;
	int timeAttack;
	bool isGameOver = false;
public:

	CBoss(D3DXVECTOR2 position, int nx, int limitedLeft, int limitedRight);
	~CBoss();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	void Draw(D3DXVECTOR2 position);
};