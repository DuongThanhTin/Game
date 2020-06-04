#include "MoneyBagBlue.h"



CMoneyBagBlue::CMoneyBagBlue(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	AddAnimation(708);
	id = ID_MONEYBAGBLUE;
}


CMoneyBagBlue::~CMoneyBagBlue()
{
}

void CMoneyBagBlue::GetBoundingBox(float &l, float&t, float &r, float &b) {
	l = x;
	t = y - MONEYBAG_BBOX_HEIGHT;
	r = x + MONEYBAG_BBOX_WIDTH;
	b = y;
}

void CMoneyBagBlue::Render() {
	animations[0]->Render(x, y);
}

void CMoneyBagBlue::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItem::Update(dt, coObjects);

	if (!isOnGround) {
		vy += MONEYBAG_GRAVITY * dt;
	}

}