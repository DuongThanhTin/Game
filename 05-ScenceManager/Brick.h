#pragma once
#include "GameObject.h"
#include "define.h"
  
#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject
{
	int width;
	int height;
public:
	CBrick();
	CBrick(D3DXVECTOR2 position, int width, int height);
	~CBrick();
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};