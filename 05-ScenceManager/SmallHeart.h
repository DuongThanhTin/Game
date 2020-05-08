#pragma once
#include"Item.h"
#include"define.h"

#define SMALLHEART_GRAVITY			0.0005f
#define SMALLHEART_BBOX_WIDTH		10
#define SMALLHEART_BBOX_HEIGHT		7

class CSmallHeart : public CItem
{
public:
	CSmallHeart(D3DXVECTOR2 position);
	~CSmallHeart();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CSmallHeart* LPSMALLHEART;
