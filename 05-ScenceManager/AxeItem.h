#pragma once
#include"Item.h"
#include"define.h"

#define AXEITEM_GRAVITY			0.0005f
#define AXEITEM_BBOX_WIDTH		15
#define AXEITEM_BBOX_HEIGHT		15

class CAxeItem : public CItem
{
public:
	CAxeItem(D3DXVECTOR2 position);
	~CAxeItem();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CAxeItem* LPAXEITEM;


