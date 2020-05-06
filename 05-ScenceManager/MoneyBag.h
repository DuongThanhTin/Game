#pragma once
#include"Item.h"
#include"define.h"

#define MONEYBAG_GRAVITY			0.0005f
#define MONEYBAG_BBOX_WIDTH		13
#define MONEYBAG_BBOX_HEIGHT		10

class CMoneyBag : public CItem
{
public:
	CMoneyBag(D3DXVECTOR2 position);
	~CMoneyBag();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CMoneyBag* LPMONEYBAG;
