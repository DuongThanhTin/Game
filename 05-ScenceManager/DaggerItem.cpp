#include "DaggerItem.h"



CDaggerItem::CDaggerItem(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	AddAnimation(703);
	id = ID_DAGGERITEM;
}


CDaggerItem::~CDaggerItem()
{
}

void CDaggerItem::GetBoundingBox(float &l, float&t, float &r, float &b) {
	l = x;
	t = y - DAGGERITEM_BBOX_HEIGHT;
	r = x + DAGGERITEM_BBOX_WIDTH;
	b = y;
}

void CDaggerItem::Render() {
	animations[0]->Render(x, y);
}

void CDaggerItem::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItem::Update(dt, coObjects);

	if (!isOnGround) {
		vy += DAGGERITEM_GRAVITY * dt;
	}

}
