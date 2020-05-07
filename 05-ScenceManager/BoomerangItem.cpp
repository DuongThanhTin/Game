#include "BoomerangItem.h"


CBoomerangItem::CBoomerangItem(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	AddAnimation(705);
	id = ID_BOOMERANGITEM;
}


CBoomerangItem::~CBoomerangItem()
{
}

void CBoomerangItem::GetBoundingBox(float &l, float&t, float &r, float &b) {
	l = x;
	t = y - BOOMERANGITEM_BBOX_HEIGHT;
	r = x + BOOMERANGITEM_BBOX_WIDTH;
	b = y;
}

void CBoomerangItem::Render() {
	animations[0]->Render(x, y);
}

void CBoomerangItem::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItem::Update(dt, coObjects);

	if (!isOnGround) {
		vy += BOOMERANGITEM_GRAVITY * dt;
	}

}