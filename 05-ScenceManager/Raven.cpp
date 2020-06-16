#include "Raven.h"


CRaven::CRaven()
{

}

CRaven::~CRaven()
{
}

CRaven::CRaven(D3DXVECTOR2 position, int nx, int nextItemID, float falldown, int area_id)
{
	x = position.x;
	y = position.y;
	this->nx = nx;
	this->falldown = falldown;
	isActive = false;
	id = ID_RAVEN;
	//SetState(BAT_STATE_SLEEP);
	AddAnimation(ANI_DESTROY);
	vx = 0;
	this->nextItemID = nextItemID;
	areaactive_enemy = area_id;
	scoreEnemy = 200;
	this->healthEnemy = 1;
}

void CRaven::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	//left = top = right = bottom = 0.0f;
	left = x;
	top = y - RAVEN_BBOX_HEIGHT;
	right = x + RAVEN_BBOX_WIDTH;
	bottom = y;
}

void CRaven::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CEnemy::Update(dt, coObjects);
	if (state == ENEMY_STATE_DESTROY)
	{
		vy = 0;
	}
	else if (isActive)
	{
		vx += nx*RAVEN_FLYING_SPEED;
		y += 0.5;
		if (y >= falldown)
		{
			y = falldown;
		}
	}

}

void CRaven::Render()
{
	int ani;
	if (state != ENEMY_STATE_DESTROY)
	{
		ani = 0;
		if (isActive)
		{
			ani = RAVEN_ANI_FLYING_RIGHT;
		}

		animation_set->at(ani)->Render(x, y);
	}
	else
	{
		ani = 3;
		animation_set->at(ani)->Render(x, y);
	}

	RenderBoundingBox();
}

