#pragma once
#include "GameObject.h"
#include "define.h"

#define HIDEBRICK_BBOX_WIDTH  16
#define HIDEBRICK_BBOX_HEIGHT 16

class CHideBrick : public CGameObject
{
	int width;
	int height;
public:
	CHideBrick();
	CHideBrick(D3DXVECTOR2 position, int width, int height);
	~CHideBrick();
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void BeDamaged();
};