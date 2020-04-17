#include "Zombie.h"



CZombie::CZombie()
{
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
	CGameObject::Update(dt, coObjects);

	// Simple fall down
	vy += ZOMBIE_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	//Collision with wall
	vector<LPGAMEOBJECT> wallObjects;
	for (int i = 0;i < coObjects->size();i++) {
		if (coObjects->at(i)->GetID() == ID_GROUND)
			wallObjects.push_back(coObjects->at(i));
	}
	// turn off collision when die 
	if (state != ZOMBIE_STATE_DIE)
		CalcPotentialCollisions(&wallObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block 
		x += min_tx*dx + nx*0.1f;
		y += min_ty*dy + ny*0.1f;

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


		// clean up collision events
		for (auto iter : coEvents) delete iter;
		coEvents.clear();
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