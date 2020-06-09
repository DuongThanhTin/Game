#pragma once
#include"define.h"
#include"GameObject.h"
#include"Game.h"
#include"Textures.h"
#include"Weapon.h"

#define WHIP_BBOX_WIDTH_00		25
#define WHIP_BBOX_HEIGHT_00		8
#define WHIP_BBOX_WIDTH_01		27
#define WHIP_BBOX_HEIGHT_01		8
#define WHIP_BBOX_WIDTH_02		36
#define WHIP_BBOX_HEIGHT_02		8

#define WHIP_ANI_RIGHT_00	111
#define WHIP_ANI_LEFT_00	112
#define WHIP_ANI_RIGHT_01	121
#define WHIP_ANI_LEFT_01	122
#define WHIP_ANI_RIGHT_02	131
#define WHIP_ANI_LEFT_02	132



class CWhip : public CWeapon
{
private:
	int level;
	static CWhip* __instance;
public:
	CWhip();
	~CWhip();
	static CWhip* GetInstance();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	int GetAnimation();
	int GetLevel() { return level; }
	void SetLevel(int level) { this->level = level; }
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects, D3DXVECTOR2 position, int playerNx);
	void Upgrade();
};

typedef CWhip *LPWHIP;

