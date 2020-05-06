#include "MoneyBag.h"



CMoneyBag::CMoneyBag(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	AddAnimation(704);
	id = ID_MONEYBAG;
}


CMoneyBag::~CMoneyBag()
{
}

void CMoneyBag::GetBoundingBox(float &l, float&t, float &r, float &b) {
	l = x;
	t = y - MONEYBAG_BBOX_HEIGHT;
	r = x + MONEYBAG_BBOX_WIDTH;
	b = y;
}

void CMoneyBag::Render() {
	animations[0]->Render(x, y);
}

void CMoneyBag::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItem::Update(dt, coObjects);

	if (!isOnGround) {
		vy += MONEYBAG_GRAVITY * dt;
	}

}