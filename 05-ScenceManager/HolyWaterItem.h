#pragma once
#include"Item.h"
#include"define.h"

#define HOLYWATERITEM_GRAVITY			0.0005f
#define HOLYWATERITEM_BBOX_WIDTH		15
#define HOLYWATERITEM_BBOX_HEIGHT		15

class CHolyWaterItem : public CItem
{
public:
	CHolyWaterItem(D3DXVECTOR2 position);
	~CHolyWaterItem();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CHolyWaterItem* LPHOLYWATERITEM;


