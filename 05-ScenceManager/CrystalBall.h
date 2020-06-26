#pragma once
#include "Item.h"

#define CRYSTALBALL_ITEM_GRAVITY				0.0005f
#define CRYSTALBALL_ITEM_BBOX_WIDTH			15
#define CRYSTALBALL_ITEM_BBOX_HEIGHT			15

class CCrystalBall : public CItem
{
public:
	CCrystalBall(D3DXVECTOR2 position);
	~CCrystalBall();
	void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *ojects);
};