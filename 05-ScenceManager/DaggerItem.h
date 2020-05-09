#pragma once
#include"Item.h"
#include"define.h"

#define DAGGERITEM_GRAVITY			0.0005f
#define DAGGERITEM_BBOX_WIDTH		13
#define DAGGERITEM_BBOX_HEIGHT		10

class CDaggerItem : public CItem
{
public:
	CDaggerItem(D3DXVECTOR2 position);
	~CDaggerItem();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CDaggerItem* LPDAGGERITEM;
