#include "WhipUpgrade.h"



CWhipUpgrade::CWhipUpgrade(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	AddAnimation(801);
	id = ID_WHIPUPGRADE;
}


CWhipUpgrade::~CWhipUpgrade()
{
}

void CWhipUpgrade::GetBoundingBox(float &l, float&t, float &r, float &b) {
	l = x;
	t = y - WHIPUPGRADE_BBOX_HEIGHT;
	r = x + WHIPUPGRADE_BBOX_WIDTH;
	b = y;
}

void CWhipUpgrade::Render() {
	animations[0]->Render(x, y);
}

void CWhipUpgrade::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItem::Update(dt, coObjects);

	if (!isOnGround) {
		vy += WHIPUPGRADE_GRAVITY * dt;
	}

}