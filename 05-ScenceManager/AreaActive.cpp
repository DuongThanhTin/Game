#include "AreaActive.h"



CAreaActive::CAreaActive() {

	id = ID_GROUND;
}

CAreaActive::CAreaActive(D3DXVECTOR2 position, int width, int height)
{
	this->width = width;
	this->height = height;
	this->x = position.x;
	this->y = position.y;
	id = ID_AREAACTIVE;
}

CAreaActive::~CAreaActive() {

}
void CAreaActive::Render()
{
	RenderBoundingBox();
}

void CAreaActive::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y - height;
	r = x + width;
	b = y;
}