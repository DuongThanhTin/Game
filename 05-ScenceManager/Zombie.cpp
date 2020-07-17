#include "Zombie.h"



CZombie::CZombie()
{ 
	id = ID_ZOMBIE;
	SetState(ZOMBIE_STATE_WALKING);
}

CZombie::~CZombie()
{
}

CZombie::CZombie(D3DXVECTOR2 position, int nextItemID, float limitedLeft, float limitedRight)
{
	x = position.x;
	y = position.y;
	this->limitedLeft = limitedLeft;
	this->limitedRight = limitedRight;
	id = ID_ZOMBIE;
	SetState(ZOMBIE_STATE_WALKING);
	AddAnimation(ANI_DESTROY);
	nx = -1;
	scoreEnemy = NUM_SCORE_ENEMY_SPEARKNIGHT;
	this->nextItemID = nextItemID;
	this->healthEnemy = 1;
}

void CZombie::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	if (!isDestroy)
	{
		left = x;
		top = y - ZOMBIE_BBOX_HEIGHT;
		right = x + ZOMBIE_BBOX_WIDTH;
		bottom = y;
	}
	else
	{
		left = top = right = bottom = 0;
	}
}

void CZombie::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CEnemy::Update(dt, coObjects);
	if (!isInGrid)
		return;

	// Simple fall down
	vy += ZOMBIE_GRAVITY*dt;

	if (ny < 0) {
		vy = 0;

		if (!isOnGround)
		{
			isOnGround = true;
		}
	}

	if (timeStopWatch == 0)
	{
		isStopFrame = false;
		if (vx > 0)
		{
			vx = ZOMBIE_WALKING_SPEED;
		}
		else
		{
			vx = -ZOMBIE_WALKING_SPEED;
		}
	}
	else
	{
		isStopFrame = true;
		vx = vy = 0;
	}

	if (vx < 0 && x < limitedLeft) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > limitedRight) {
		vx = -vx;
	}

}

void CZombie::Render()
{
	if (state != ENEMY_STATE_DESTROY)
	{
		int ani = ZOMBIE_ANI_WALKING_LEFT;
		if (vx > 0)
			ani = ZOMBIE_ANI_WALKING_RIGHT;
		else
			ani = ZOMBIE_ANI_WALKING_LEFT;

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
		animations[0]->Render(x, y);
	}

	

	RenderBoundingBox();
}

void CZombie::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ZOMBIE_STATE_WALKING:
		vx = ZOMBIE_WALKING_SPEED;
	}

}