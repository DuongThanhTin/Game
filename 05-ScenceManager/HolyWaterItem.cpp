#include "HolyWaterItem.h"



CHolyWaterItem::CHolyWaterItem(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	AddAnimation(710);
	id = ID_HOLYWATERITEM;
}


CHolyWaterItem::~CHolyWaterItem()
{
}

void CHolyWaterItem::GetBoundingBox(float &l, float&t, float &r, float &b) {
	l = x;
	t = y - HOLYWATERITEM_BBOX_HEIGHT;
	r = x + HOLYWATERITEM_BBOX_WIDTH;
	b = y;
}

void CHolyWaterItem::Render() {
	animations[0]->Render(x, y);
}

void CHolyWaterItem::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItem::Update(dt, coObjects);

	if (!isOnGround) {
		vy += HOLYWATERITEM_GRAVITY * dt;
	}

}