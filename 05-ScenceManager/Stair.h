#pragma once
#include "Brick.h"
#include "define.h"

class CStair : public CBrick
{
	int width;
	int height;
	int longStair;	
public:
	CStair();
	~CStair();
	CStair(D3DXVECTOR2 position, int width, int height, int longStair, int nx, int ny);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	int GetStairLong() { return longStair; }
};

typedef CStair *LPSTAIR;
