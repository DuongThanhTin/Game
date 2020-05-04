#include "Dagger.h"



CDagger::CDagger(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	AddAnimation(703);
	id = ID_DAGGER;
}


CDagger::~CDagger()
{
}

void CDagger::GetBoundingBox(float &l, float&t, float &r, float &b) {
	l = x;
	t = y - DAGGER_BBOX_HEIGHT;
	r = x + DAGGER_BBOX_WIDTH;
	b = y;
}

void CDagger::Render() {
	animations[0]->Render(x, y);
}

void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItem::Update(dt, coObjects);

	if (!isOnGround) {
		vy += DAGGER_GRAVITY * dt;
	}

}