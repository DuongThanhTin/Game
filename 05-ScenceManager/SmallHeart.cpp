#include "SmallHeart.h"



CSmallHeart::CSmallHeart(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	AddAnimation(SMALLHEART_ANI);
	id = ID_SMALLHEART;
	velocity_x = SMALLHEART_FALLING_SPEED_X_VARIATION;
}


CSmallHeart::~CSmallHeart()
{
}

void CSmallHeart::GetBoundingBox(float &l, float&t, float &r, float &b) {
	l = x;
	t = y - SMALLHEART_BBOX_HEIGHT;
	r = x + SMALLHEART_BBOX_WIDTH;
	b = y;
}

void CSmallHeart::Render() {
	animations[0]->Render(x, y);
}

void CSmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CItem::Update(dt, coObjects);

	if (!isOnGround) {
		vy += SMALLHEART_GRAVITY*dt ;
		vx += velocity_x*dt;
		if (vx >= SMALLHEART_FALLING_SPEED_X || vx <= -SMALLHEART_FALLING_SPEED_X)
			velocity_x *= -1; // đổi chiều
	}
}