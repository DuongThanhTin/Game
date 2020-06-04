#include "Axe.h"



CAxe::CAxe(D3DXVECTOR2 position, int nx)
{
	this->x = position.x;
	this->y = position.y - 15;
	this->nx = nx;
	vy = -AXE_THROW_SPEED_Y;
	vx = AXE_FLY_SPEED;
	AddAnimation(ID_ANI_AXE_RIGHT); //Right
	AddAnimation(ID_ANI_AXE_LEFT); //Left
	id = ID_AXE;
	timefly = GetTickCount();
}


CAxe::~CAxe()
{
}

void CAxe::GetBoundingBox(float &l, float&t, float &r, float &b) {
	l = x;
	t = y - AXE_BBOX_HEIGHT;
	r = x + AXE_BBOX_WIDTH;
	b = y;
}

void CAxe::Render() {
	if (nx > 0)
		animations[0]->Render(x, y);
	else
		animations[1]->Render(x, y);

	RenderBoundingBox();
}

void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CWeapon::Update(dt, coObjects);
	
	if (GetTickCount() - timefly > TIME_AXE_FLY)
	{
		y += AXE_GRAVITY*dt;
		if (nx > 0)
			x += vx*dt;
		else
			x -= vx*dt;
		
	}
	else if (timefly >0)
	{
		y -= AXE_THROW_SPEED_Y*dt;
		if (nx > 0)
			x += vx*dt;
		else
			x -= vx*dt;
	}
	
}