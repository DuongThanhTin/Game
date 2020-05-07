#include "Zombie.h"



CZombie::CZombie()
{ 
	id = ID_ZOMBIE;
	SetState(ZOMBIE_STATE_WALKING);
}

CZombie::~CZombie()
{
}

void CZombie::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y - ZOMBIE_BBOX_HEIGHT;
	right = x + ZOMBIE_BBOX_WIDTH;
	bottom = y ;
}

void CZombie::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CEnemy::Update(dt, coObjects);

	// Simple fall down
	vy += ZOMBIE_GRAVITY*dt;

	if (ny < 0) {
		vy = 0;

		if (!isOnGround)
		{
			isOnGround = true;
		}
	}

	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}

	if (vx > 0 && x > 200) {
		x = 200; vx = -vx;
	}
}

void CZombie::Render()
{
	int ani = ZOMBIE_ANI_WALKING_LEFT;
	if (vx > 0) 
		ani = ZOMBIE_ANI_WALKING_RIGHT;
	else 
		ani = ZOMBIE_ANI_WALKING_LEFT;

	animation_set->at(ani)->Render(x, y);

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