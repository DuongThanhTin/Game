#include "Boomerang.h"




CBoomerang::CBoomerang(D3DXVECTOR2 position, int nx)
{
	this->x = position.x;
	this->y = position.y - 15;
	this->nx = nx;
	vx = BOOMERANG_FLY_SPEED;
	AddAnimation(1011);
	AddAnimation(1012);
	id = ID_BOOMERANG;
}


CBoomerang::~CBoomerang()
{
}

void CBoomerang::GetBoundingBox(float &l, float&t, float &r, float &b) {
	l = x;
	t = y - BOOMERANG_BBOX_HEIGHT;
	r = x + BOOMERANG_BBOX_WIDTH;
	b = y;
}

void CBoomerang::Render() {
	int ani;
	if (nx > 0) {
		animations[0]->Render(x, y);
	}
	else
		animations[1]->Render(x, y);
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CWeapon::Update(dt, coObjects);
	if (nx > 0)
		x += vx*dt;
	else
		x -= vx*dt;
}