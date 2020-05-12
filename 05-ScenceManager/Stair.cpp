#include "Stair.h"

CStair::CStair()
{
	id = ID_STAIR;
}

CStair::CStair(D3DXVECTOR2 position, int width, int height, int nx, int ny)
{
	x = position.x;
	y = position.y;
	this->width = width;
	this->height = height;
	this->nx = nx;
	this->ny = ny;

	id = ID_STAIR;
}
CStair::~CStair()
{
}

void CStair::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - width;
	r = x + height;
	b = y;

}

void CStair::Render()
{
	RenderBoundingBox(100);
}