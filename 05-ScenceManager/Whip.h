#pragma once
#include"define.h"
#include"GameObject.h"
#include"Game.h"
#include"Textures.h"
#include"Weapon.h"


#define WHIP_BBOX_WIDTH_01		25
#define WHIP_BBOX_HEIGHT_01		8
#define WHIP_BBOX_WIDTH_02		25
#define WHIP_BBOX_HEIGHT_02		8
#define WHIP_BBOX_WIDTH_03		40
#define WHIP_BBOX_HEIGHT_03		8

#define WHIP_ANI_RIGHT_01	0
#define WHIP_ANI_LEFT_01	1
#define WHIP_ANI_RIGHT_02	2
#define WHIP_ANI_LEFT_02	3
#define WHIP_ANI_RIGHT_03	4
#define WHIP_ANI_LEFT_03	5


class CWhip : public CWeapon
{
private:
	int level;
	int GetAnimation();
public:
	CWhip();
	~CWhip();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects, D3DXVECTOR2 position, int playerNx);
	void Upgrade();
};

typedef CWhip *LPWHIP;

