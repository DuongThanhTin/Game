#include "Dagger.h"



CDagger::CDagger(D3DXVECTOR2 position, int nx)
{
	this->x = position.x;
	this->y = position.y;
	this->nx = nx;
	AddAnimation(703);
	AddAnimation(1001);
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
	int ani;
	if (nx > 0) {
		animations[0]->Render(x, y);
	}
	else
		animations[1]->Render(x, y);
}

void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CWeapon::Update(dt, coObjects);
	if (nx > 0)
		x += DAGGER_FLY_SPEED*dt;
	else
		x -= DAGGER_FLY_SPEED*dt;
}