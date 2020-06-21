#pragma once
#include "Weapon.h"
#include "define.h"
#include "Brick.h"

#define HOLYWATER_BBOX_WIDTH		20
#define HOLYWATER_BBOX_HEIGHT		15
#define HOLYWATER_GRAVITY 0.0005f //0.004f
#define HOLYWATER_FLY_SPEED			0.07f
#define HOLYWATER_THROW_SPEED_Y	0.07f
#define TIME_HOLYWATER_FLY 200
#define TIME_HOLYWATER_FIRE 2000
#define HOLYWATER_SIMON_RANGE_X_RIGHT 15
#define HOLYWATER_SIMON_RANGE_X_LEFT 20

class CHolyWater : public CWeapon
{
	DWORD timefly;
	DWORD timeHolyWaterFire;

	
public:
	bool isDisapear;
	CHolyWater(D3DXVECTOR2 position, int nx);
	~CHolyWater();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CHolyWater* LPHOLYWATER;


