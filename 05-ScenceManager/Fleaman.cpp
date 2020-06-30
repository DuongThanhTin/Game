#include "Fleaman.h"



CFleaman::CFleaman()
{
}

CFleaman::~CFleaman()
{
}

CFleaman::CFleaman(D3DXVECTOR2 position, int nextItemID, float limitedLeft, float limitedRight)
{
	x = position.x;
	y = position.y;
	this->limitedLeft = limitedLeft;
	this->limitedRight = limitedRight;
	id = ID_FLEAMAN;
	AddAnimation(ANI_DESTROY);
	nx = 1;
	scoreEnemy = NUM_SCORE_ENEMY_SPEARKNIGHT;
	//vx = FLEAMAN_WALKING_SPEED;
	this->nextItemID = nextItemID;
	this->healthEnemy = 3;
	isOnGround = true;
}

void CFleaman::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	if (!isDestroy)
	{
		left = x;
		top = y - FLEAMAN_BBOX_HEIGHT;
		right = x + FLEAMAN_BBOX_WIDTH;
		bottom = y;
	}
	else
	{
		left = top = right = bottom = 0;
	}

}
void CFleaman::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CEnemy::Update(dt, coObjects);
	//if (isInGrid != true)
		//return;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;


	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

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
		y += min_ty*dy + ny*0.1f;

		
		if (isActive)
		{
			if (start_untouchable != 0)
			{
				vx = 0.001;
				Untouchable();
			}
			else
			{
				if (timeStopWatch == 0)
				{
					if (!isOnGroundEnemy)
					{
						vy -= 0.12f;
						isOnGroundEnemy = true;
						
					}
					else
					{
						
						vy += FLEAMAN_GRAVITY*dt;
					
					}
					
					if (nx > 0)
					{
						vx = -FLEAMAN_WALKING_SPEED;
					}
					else
					{
					
						vx = FLEAMAN_WALKING_SPEED;
					}

					
				}
				else
				{
					vx = vy = 0;
				}
			}

			if (x <= limitedLeft) {
				vx = -vx;
			}

			else if (x >= limitedRight) {
				vx = -vx;
			}
		}

	

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
							nx = -nx;
							vx -= vx;
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
		vy += 0.0006f*dt;
		

}

void CFleaman::Render()
{
	if (state != ENEMY_STATE_DESTROY)
	{
		int ani = FLEAMAN_ANI_WALKING_RIGHT;
			if (nx > 0)
				ani = FLEAMAN_ANI_WALKING_RIGHT;
			else
				ani = FLEAMAN_ANI_WALKING_LEFT;

		animation_set->at(ani)->Render(x, y);
	}
	else
	{
		animations[0]->Render(x, y);
	}


	RenderBoundingBox();
}

void CFleaman::SetState(int state)
{
	CGameObject::SetState(state);


}