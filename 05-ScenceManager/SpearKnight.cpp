#include "SpearKnight.h"



CSpearKnight::CSpearKnight()
{
	id = ID_SPEARKNIGHT;
	SetState(SPEARKNIGHT_STATE_WALKING);
	AddAnimation(ANI_DESTROY);
	nx = -1;
}

CSpearKnight::~CSpearKnight()
{
}

CSpearKnight::CSpearKnight(D3DXVECTOR2 position, int nextItemID)
{
	x = position.x;
	y = position.y;
	id = ID_SPEARKNIGHT;
	SetState(SPEARKNIGHT_STATE_WALKING);
	AddAnimation(ANI_DESTROY);
	nx = -1;
	this->nextItemID = nextItemID;
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
	CEnemy::Update(dt, coObjects);

	// Simple fall down
	if (state == ENEMY_STATE_DESTROY)
	{
		vy = 0;
	}
	else
		vy += SPEARKNIGHT_GRAVITY*dt;

	if (vx < 0 && x<33) {
		vx = -vx;
	}

	if (vx > 0 && x > 135) {
		x = 135; vx = -vx;
	}
}

void CSpearKnight::Render()
{
	if(state != ENEMY_STATE_DESTROY)
	{
		int ani = SPEARKNIGHT_ANI_WALKING_LEFT;
		if (vx > 0)
			ani = SPEARKNIGHT_ANI_WALKING_RIGHT;
		else
			ani = SPEARKNIGHT_ANI_WALKING_LEFT;

		animation_set->at(ani)->Render(x, y);
	}
	else
	{
		animations[0]->Render(x,y);
	}
	

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