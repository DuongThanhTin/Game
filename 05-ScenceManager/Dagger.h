#pragma once
#include"Item.h"
#include"define.h"

#define DAGGER_GRAVITY			0.0005f
#define DAGGER_BBOX_WIDTH		13
#define DAGGER_BBOX_HEIGHT		10

class CDagger : public CItem
{
public:
	CDagger(D3DXVECTOR2 position);
	~CDagger();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CDagger* LPDAGGER;
