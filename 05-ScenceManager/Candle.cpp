#include "Candle.h"



CCandle::CCandle()
{
}


CCandle::~CCandle()
{
}

CCandle::CCandle(D3DXVECTOR2 position, int nextItemID)
{
	x = position.x;
	y = position.y;
	id = ID_CANDLE;
	this->nextItemID = nextItemID;
}

void CCandle::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y - CANDLE_BBOX_HEIGHT;
	r = x + CANDLE_BBOX_WIDTH;
	b = y;
}


