#include "InvisibilityPotionItem.h"



CInvisibilityPotionItem::CInvisibilityPotionItem(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	AddAnimation(ANI_INVIPOTION);
	id = ID_INVIPOTION;
}


CInvisibilityPotionItem::~CInvisibilityPotionItem()
{
}

void CInvisibilityPotionItem::GetBoundingBox(float &l, float&t, float &r, float &b) {
	l = x;
	t = y - INVIPOTION_BBOX_HEIGHT;
	r = x + INVIPOTION_BBOX_WIDTH;
	b = y;
}

void CInvisibilityPotionItem::Render() {
	animations[0]->Render(x, y);
}

void CInvisibilityPotionItem::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItem::Update(dt, coObjects);

	if (!isOnGround) {
		vy += MONEYBAG_GRAVITY * dt;
	}

}