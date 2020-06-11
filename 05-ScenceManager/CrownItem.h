#pragma once
#include "Item.h"
#include "define.h"
#include "GameObject.h"


#define CROWN_BBOX_WIDTH		17
#define CROWN_BBOX_HEIGHT		17
#define CROWN_UP_SPEED	0.03
#define ANI_CROWN 795

class CCrownItem : public CGameObject
{
	int crownUp_Y;
public:
	CCrownItem(D3DXVECTOR2 position, int crownUp);
	~CCrownItem();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

