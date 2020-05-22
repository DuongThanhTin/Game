#include "Bat.h"


CBat::CBat()
{
	id = ID_SPEARKNIGHT;
	SetState(BAT_STATE_SLEEP);
	AddAnimation(ANI_DESTROY);
	nx = -1;
	
}

CBat::~CBat()
{
}

CBat::CBat(D3DXVECTOR2 position,int nx, int nextItemID, float falldown)
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
}

void CBat::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
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
		y += 1;
		if (y >= falldown)
		{
			y = falldown;
		}
	}

}

void CBat::Render()
{
	if (state != ENEMY_STATE_DESTROY)
	{
		int ani = 0;
		if (isActive)
		{
			ani = BAT_ANI_FLYING_RIGHT;
		}
		
		animation_set->at(ani)->Render(x, y);
	}
	else
	{
		animations[0]->Render(x, y);
	}


	RenderBoundingBox();
}

void CBat::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	/*case SPEARKNIGHT_STATE_WALKING:
		vx = SPEARKNIGHT_WALKING_SPEED;*/
	}

}