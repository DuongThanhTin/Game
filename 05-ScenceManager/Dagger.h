#pragma once
#include"Weapon.h"
#include"define.h"

#define DAGGER_FLY_SPEED		0.2f
#define DAGGER_BBOX_WIDTH		13
#define DAGGER_BBOX_HEIGHT		10

class CDagger : public CWeapon
{
public:
	CDagger(D3DXVECTOR2 position, int nx);
	~CDagger();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CDagger* LPDAGGER;
