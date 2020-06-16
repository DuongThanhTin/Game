#pragma once
#include"Weapon.h"
#include"define.h"
#include"Simon.h"

#define AXE_BBOX_WIDTH		20
#define AXE_BBOX_HEIGHT		15
#define AXE_GRAVITY  0.015f//0.14f
#define AXE_FLY_SPEED			0.1f
#define AXE_THROW_SPEED_Y	0.14f
#define TIME_AXE_FLY 350
#define AXE_SIMON_RANGE_X_RIGHT 15
#define AXE_SIMON_RANGE_X_LEFT 20

class CAxe : public CWeapon
{
	DWORD timefly;
	bool isFlyReturn;

public:
	bool isDisapear;
	CAxe(D3DXVECTOR2 position, int nx);
	~CAxe();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CAxe* LPAXE;
