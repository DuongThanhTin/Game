#pragma once
#include "Item.h"
#include "define.h"

class CMoneyBagBlue : public CItem
{
public:
	CMoneyBagBlue(D3DXVECTOR2 position);
	~CMoneyBagBlue();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CMoneyBagBlue* LPMONEYBAGBLUE;
