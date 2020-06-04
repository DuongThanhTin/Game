#pragma once
#include "Item.h"
#include "define.h"

class CMoneyBagWhite : public CItem
{
public:
	CMoneyBagWhite(D3DXVECTOR2 position);
	~CMoneyBagWhite();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CMoneyBagWhite* LPMONEYBAGWHITE;
