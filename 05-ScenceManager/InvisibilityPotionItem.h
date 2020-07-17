#pragma once
#include"Item.h"
#include"define.h"

#define INVIPOTION_BBOX_WIDTH 12 
#define INVIPOTION_BBOX_HEIGHT 17

class CInvisibilityPotionItem : public CItem
{
public:
	CInvisibilityPotionItem(D3DXVECTOR2 position);
	~CInvisibilityPotionItem();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

