#pragma once
#include"Item.h"
#include"define.h"


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
