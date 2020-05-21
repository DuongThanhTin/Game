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

CBat::CBat(D3DXVECTOR2 position,int nx, int nextItemID)
{
	x = position.x;
	y = position.y;
	this->nx = nx;
	id = ID_BAT;
	SetState(BAT_STATE_SLEEP);
	AddAnimation(ANI_DESTROY);
	nx = -1;
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

	// Simple fall down
	if (state == ENEMY_STATE_DESTROY)
	{
		vy = 0;
	}

}

void CBat::Render()
{
	if (state != ENEMY_STATE_DESTROY)
	{
		/*int ani = SPEARKNIGHT_ANI_WALKING_LEFT;
		if (vx > 0)
			ani = SPEARKNIGHT_ANI_WALKING_RIGHT;
		else
			ani = SPEARKNIGHT_ANI_WALKING_LEFT;

		animation_set->at(ani)->Render(x, y);*/
		int ani = 0;
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