#pragma once
#include"Weapon.h"
#include"define.h"
#include"Simon.h"

#define BOOMERANG_FLY_SPEED		0.15f
#define BOOMERANG_BBOX_WIDTH		20
#define BOOMERANG_BBOX_HEIGHT		15
#define TIME_FLY 450

class CBoomerang : public CWeapon
{
	DWORD timefly;
	bool isFlyReturn;
	
public:
	CBoomerang(D3DXVECTOR2 position, int nx);
	~CBoomerang();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CBoomerang* LPBOOMERANG;
