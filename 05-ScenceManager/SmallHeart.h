#pragma once
#include"Item.h"
#include"define.h"

#define SMALLHEART_GRAVITY			0.0002f
#define SMALLHEART_BBOX_WIDTH		10
#define SMALLHEART_BBOX_HEIGHT		7
#define SMALLHEART_FALLING_SPEED_X  0.1f
#define SMALLHEART_FALLING_SPEED_X_VARIATION	0.0007f
#define SMALLHEART_ANI 702

class CSmallHeart : public CItem
{
	float velocity_x; // Thay đổi vx
public:
	CSmallHeart(D3DXVECTOR2 position);
	~CSmallHeart();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CSmallHeart* LPSMALLHEART;
