#include "SpearKnight.h"



CSpearKnight::CSpearKnight()
{
	id = ID_SPEARKNIGHT;
	SetState(SPEARKNIGHT_STATE_WALKING);
}

CSpearKnight::~CSpearKnight()
{
}

void CSpearKnight::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y - SPEARKNIGHT_BBOX_HEIGHT;
	right = x + SPEARKNIGHT_BBOX_WIDTH;
	bottom = y;
}

void CSpearKnight::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	// Simple fall down
	vy += SPEARKNIGHT_GRAVITY*dt;

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
	if (state != SPEARKNIGHT_STATE_DIE)
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

		if (vx < 0 && x < 33) {
			 vx = -vx;
		}

		if (vx > 0 && x > 135) {
			x = 135; vx = -vx;
		}


		// clean up collision events
		for (auto iter : coEvents) delete iter;
		coEvents.clear();
	}
}

void CSpearKnight::Render()
{
	int ani = SPEARKNIGHT_ANI_WALKING_LEFT;
	if (vx > 0)
		ani = SPEARKNIGHT_ANI_WALKING_RIGHT;
	else
		ani = SPEARKNIGHT_ANI_WALKING_LEFT;

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CSpearKnight::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SPEARKNIGHT_STATE_WALKING:
		vx = SPEARKNIGHT_WALKING_SPEED;
	}

}