#pragma once
#include"Weapon.h"
#include"define.h"

#define BOOMERANG_FLY_SPEED		0.2f
#define BOOMERANG_BBOX_WIDTH		20
#define BOOMERANG_BBOX_HEIGHT		15

class CBoomerang : public CWeapon
{
public:
	CBoomerang(D3DXVECTOR2 position, int nx);
	~CBoomerang();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CBoomerang* LPBOOMERANG;
