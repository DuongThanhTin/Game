#include "Brick.h"


CBrick::CBrick() {

	id = ID_GROUND;
}

CBrick::CBrick(D3DXVECTOR2 position, int width, int height)
{
	this->width = width;
	this->height = height;
	this->x = position.x;
	this->y = position.y;
	id = ID_GROUND;
}

CBrick::~CBrick() {

}
void CBrick::Render()
{
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y - height;
	r = x + width;
	b = y ;
}