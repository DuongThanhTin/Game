#pragma once
#include"Item.h"
#include"define.h"

#define BOOMERANGITEM_GRAVITY			0.0005f
#define BOOMERANGITEM_BBOX_WIDTH		15
#define BOOMERANGITEM_BBOX_HEIGHT		15

class CBoomerangItem : public CItem
{
public:
	CBoomerangItem(D3DXVECTOR2 position);
	~CBoomerangItem();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CBoomerangItem* LPBOOMERANGITEM;


