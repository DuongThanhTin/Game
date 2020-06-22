#include "Raven.h"


CRaven::CRaven()
{

}

CRaven::~CRaven()
{
}

CRaven::CRaven(D3DXVECTOR2 position, int nextItemID, float falldown, int area_id)
{
	x = position.x;
	y = position.y;
	//this->nx = nx;
	//this->falldown = falldown;
	isActive = false;
	id = ID_RAVEN;
	SetState(RAVEN_STATE_SLEEP);
	AddAnimation(ANI_DESTROY);
	vx = 0;
	this->nextItemID = nextItemID;
	//areaactive_enemy = area_id;
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
		if (start_untouchable != 0)
		{
			vx = 0.01;
			Untouchable();
		}
		else
		{
			if (timeStopWatch == 0)
			{
				vx = -RAVEN_FLYING_SPEED_X;
				vy = 0.075;
				y += vy;
			}
			else
			{
				vx = vy = 0;
			}
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
			ani = RAVEN_ANI_FLYING_LEFT;
		}

		animation_set->at(ani)->Render(x, y);
	}
	else
	{
		animations[0]->Render(x, y);
	}
	RenderBoundingBox();
}

