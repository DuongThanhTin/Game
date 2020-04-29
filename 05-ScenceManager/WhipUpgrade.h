#pragma once
#include"Item.h"
#include"define.h"

#define WHIPUPGRADE_GRAVITY			0.0005f
#define WHIPUPGRADE_BBOX_WIDTH		17
#define WHIPUPGRADE_BBOX_HEIGHT		15

class CWhipUpgrade : public CItem
{
public:
	CWhipUpgrade(D3DXVECTOR2 position);
	~CWhipUpgrade();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CWhipUpgrade* LPWHIPUPGRADE;
