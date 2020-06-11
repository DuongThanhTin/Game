#include "Bat.h"


CBat::CBat()
{
	id = ID_SPEARKNIGHT;
	SetState(BAT_STATE_SLEEP);
	AddAnimation(ANI_DESTROY);
	nx = -1;
	scoreEnemy = NUM_SCORE_ENEMY_BAT;
}

CBat::~CBat()
{
}

CBat::CBat(D3DXVECTOR2 position,int nx, int nextItemID, float falldown , int area_id)
{
	x = position.x;
	y = position.y;
	this->nx = nx;
	this->falldown = falldown;
	isActive = false;
	id = ID_BAT;
	SetState(BAT_STATE_SLEEP);
	AddAnimation(ANI_DESTROY);
	vx = 0;
	this->nextItemID = nextItemID;
	areaactive_enemy = area_id;
	scoreEnemy = 200;
}

void CBat::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	//left = top = right = bottom = 0.0f;
	left = x;
	top = y - BAT_BBOX_HEIGHT;
	right = x + BAT_BBOX_WIDTH;
	bottom = y;
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CEnemy::Update(dt, coObjects);
	if (state == ENEMY_STATE_DESTROY)
	{
		vy = 0;
	}
	else if (isActive)
	{
		vx += nx*BAT_FLYING_SPEED;
		y += 0.5;
		if (y >= falldown)
		{
			y = falldown;
		}
	}

}

void CBat::Render()
{
	int ani;
	if (state != ENEMY_STATE_DESTROY)
	{
		ani = 0;
		if (isActive)
		{
			ani = BAT_ANI_FLYING_RIGHT;
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

