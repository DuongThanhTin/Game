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
	this->healthEnemy = 1;
}

void CBat::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	//left = top = right = bottom = 0.0f;

	if (!isDestroy)
	{
		left = x;
		top = y - BAT_BBOX_HEIGHT;
		right = x + BAT_BBOX_WIDTH;
		bottom = y;
	}
	else
	{
		left = top = right = bottom = 0;
	}
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CEnemy::Update(dt, coObjects);
	//if (isInGrid != true)
		//return;
	//DebugOut(L"Bat %d\n", int(timeStopWatch));

	if (state == ENEMY_STATE_DESTROY)
	{
		vy = 0;
	}
	else if (isActive)
	{

		if (timeStopWatch == 0)
		{
			isStopFrame = false;
			vx += nx*BAT_FLYING_SPEED;
			y += 0.5;
			if (y >= falldown)
			{
				y = falldown;
			}
			//DebugOut(L"Bat\n");

		}
		else
		{
			isStopFrame = true;
			vx = 0;
			vy = 0;
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
		
		if (isStopFrame)
		{
			animation_set->at(ani)->RenderFrame(x, y);
		}
		else
		{
			animation_set->at(ani)->Render(x, y);
		}
	}
	else
	{
		ani = 3;
		animation_set->at(ani)->Render(x, y);
	}

	RenderBoundingBox();
}

