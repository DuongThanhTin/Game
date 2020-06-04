#include "AxeItem.h"



CAxeItem::CAxeItem(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	AddAnimation(706);
	id = ID_AXEITEM;
}


CAxeItem::~CAxeItem()
{
}

void CAxeItem::GetBoundingBox(float &l, float&t, float &r, float &b) {
	l = x;
	t = y - AXEITEM_BBOX_HEIGHT;
	r = x + AXEITEM_BBOX_WIDTH;
	b = y;
}

void CAxeItem::Render() {
	animations[0]->Render(x, y);
}

void CAxeItem::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItem::Update(dt, coObjects);

	if (!isOnGround) {
		vy += AXEITEM_GRAVITY * dt;
	}

}