#pragma once
#include"Item.h"
#include"define.h"
 
#define HEART_GRAVITY			0.0005f
#define HEART_BBOX_WIDTH		13
#define HEART_BBOX_HEIGHT		10

class CHeart : public CItem
{
public:
	CHeart(D3DXVECTOR2 position);
	~CHeart();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CHeart* LPHEART;
