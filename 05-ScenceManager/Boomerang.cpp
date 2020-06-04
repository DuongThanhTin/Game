#include "Boomerang.h"




CBoomerang::CBoomerang(D3DXVECTOR2 position, int nx)
{
	this->x = position.x;
	this->y = position.y - 15;
	this->nx = nx;
	vx = BOOMERANG_FLY_SPEED;
	AddAnimation(ID_ANI_BOOMERANG_LEFT); //Right
	AddAnimation(ID_ANI_BOOMERANG_RIGHT); //Left
	id = ID_BOOMERANG;
	timefly = GetTickCount();
	isFlyReturn = false;
	isDisapear = false;
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
	if (nx > 0) {
		animations[0]->Render(x, y);
	}
	else
		animations[1]->Render(x, y);

	RenderBoundingBox();
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CWeapon::Update(dt, coObjects);


	if (GetTickCount() - timefly > TIME_FLY)
	{
		vx = -nx*BOOMERANG_FLY_SPEED;
		x += vx*dt;
		isFlyReturn = true;
	}
	else if (timefly > 0)
	{
		if (nx > 0)
		{
			x += vx*dt;
		}
		else
		{
			x += -vx*dt;
		}
	}


}