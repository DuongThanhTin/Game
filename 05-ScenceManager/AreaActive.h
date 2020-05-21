#pragma once
#include "Brick.h"
#include "define.h"

class CAreaActive : public CBrick
{
	int width;
	int height;
public:
	CAreaActive();
	~CAreaActive();
	CAreaActive(D3DXVECTOR2 position, int width, int height);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
};


