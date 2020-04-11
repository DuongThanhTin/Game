#include "Heart.h"



CHeart::CHeart(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	AddAnimation(701);
	id = ID_HEART;
}


CHeart::~CHeart()
{
}



void CHeart::GetBoundingBox(float &l, float&t, float &r, float &b) {
	l = x;
	t = y - HEART_BBOX_HEIGHT;
	r = x + HEART_BBOX_WIDTH;
	b = y;
}

void CHeart::Render() {
	animations[0]->Render(x, y);
}

void CHeart::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItem::Update(dt, coObjects);

	if (!isOnGround)
		vy += HEART_GRAVITY * dt;

}