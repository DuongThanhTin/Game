#pragma once
#include "Brick.h"
#include "define.h"

class CStair : public CBrick
{
	int width;
	int height;
public:
	CStair();
	~CStair();
	CStair(D3DXVECTOR2 position, int Width, int Height, int nx, int ny);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
};