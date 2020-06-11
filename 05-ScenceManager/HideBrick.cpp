#include "HideBrick.h"



CHideBrick::CHideBrick() {

	id = ID_HIDEBRICK;
}

CHideBrick::CHideBrick(D3DXVECTOR2 position, int width, int height)
{
	this->width = width;
	this->height = height;
	this->x = position.x;
	this->y = position.y;
	id = ID_HIDEBRICK;
	AddAnimation(790);
	AddAnimation(791);
}

CHideBrick::~CHideBrick() {

}
void CHideBrick::Render()
{
	if (state == OBJECTS_STATE_DESTROY)
	{
		animations[1]->Render(x, y);
	}
	else
		animations[0]->Render(x, y);
	RenderBoundingBox();
}

void CHideBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{

	if (state == OBJECTS_STATE_DESTROY)
	{
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
	else
	{
		l = x;
		t = y - height;
		r = x + width;
		b = y;
	}
}

void CHideBrick::BeDamaged()
{
	int ani = 0;
	if (state == OBJECTS_STATE_DESTROY)
	{
		ani = 1;
	}
	
}