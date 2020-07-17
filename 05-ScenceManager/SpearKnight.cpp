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

CSpearKnight::CSpearKnight(D3DXVECTOR2 position, int nextItemID, float limitedLeft, float limitedRight)
{
	x = position.x;
	y = position.y;
	this->limitedLeft = limitedLeft;
	this->limitedRight = limitedRight;
	id = ID_SPEARKNIGHT;
	SetState(SPEARKNIGHT_STATE_WALKING);
	AddAnimation(ANI_DESTROY);
	nx = -1;
	scoreEnemy = NUM_SCORE_ENEMY_SPEARKNIGHT;
	this->nextItemID = nextItemID;
	this->healthEnemy = 3;
}

void CSpearKnight::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (!isDestroy)
	{
		left = x;
		top = y - SPEARKNIGHT_BBOX_HEIGHT;
		right = x + SPEARKNIGHT_BBOX_WIDTH;
		bottom = y;
	}
	else
	{
		left = top = right = bottom = 0;
	}



}
void CSpearKnight::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
	CEnemy::Update(dt, coObjects);
	//if (isInGrid != true)
		//return;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	if (start_untouchable != 0)
	{
		vx = 0.01;
		Untouchable();
	}
	else
	{
		if (timeStopWatch == 0)
		{
			isStopFrame = false;
			if (vx > 0)
			{
				vx = SPEARKNIGHT_WALKING_SPEED;
			}
			else
			{
				vx = -SPEARKNIGHT_WALKING_SPEED;
			}
		}
		else
		{
			isStopFrame = true;
			vx = 0;
			vy = 0;
		}

		
	}

	
	


	if (x <= limitedLeft) {
		vx = -vx;
	}

	else if (x >= limitedRight) {
		vx = -vx;
	}

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
		//x += min_tx*dx + nx*0.1f;
		y += min_ty*dy + ny*0.1f;



		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj))
			{
				for (size_t i = 0; i < coObjects->size(); i++)
				{
					if (coObjects->at(i)->GetID() == ID_GROUND)
					{
						if (e->nx != 0)
						{
							this->vx *= -1;
						}
					}
				}
			}
		}


		// clean up collision events
		for (auto iter : coEvents) delete iter;
		coEvents.clear();
	}

	// Simple fall down
	if (state == ENEMY_STATE_DESTROY)
	{
		vy = 0;
	}
	else
		vy += SPEARKNIGHT_GRAVITY*dt;


}

void CSpearKnight::Render()
{
	if (state != ENEMY_STATE_DESTROY)
	{
		int ani = SPEARKNIGHT_ANI_WALKING_LEFT;
		if (vx > 0)
			ani = SPEARKNIGHT_ANI_WALKING_RIGHT;
		else
			ani = SPEARKNIGHT_ANI_WALKING_LEFT;

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

void CSpearKnight::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SPEARKNIGHT_STATE_WALKING:
		vx = SPEARKNIGHT_WALKING_SPEED;
	}

}