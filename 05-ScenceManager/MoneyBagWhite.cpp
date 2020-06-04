#include "MoneyBagWhite.h"



CMoneyBagWhite::CMoneyBagWhite(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	AddAnimation(707);
	id = ID_MONEYBAGWHITE;
}


CMoneyBagWhite::~CMoneyBagWhite()
{
}

void CMoneyBagWhite::GetBoundingBox(float &l, float&t, float &r, float &b) {
	l = x;
	t = y - MONEYBAG_BBOX_HEIGHT;
	r = x + MONEYBAG_BBOX_WIDTH;
	b = y;
}

void CMoneyBagWhite::Render() {
	animations[0]->Render(x, y);
}

void CMoneyBagWhite::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItem::Update(dt, coObjects);

	if (!isOnGround) {
		vy += MONEYBAG_GRAVITY * dt;
	}

}