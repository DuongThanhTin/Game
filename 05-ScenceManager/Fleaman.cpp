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
	this->nextItemID = nextItemID;
	this->healthEnemy = 2;
	isOnGround = true;
}

void CFleaman::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y - FLEAMAN_BBOX_HEIGHT;
	right = x + FLEAMAN_BBOX_WIDTH;
	bottom = y;

}
void CFleaman::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CEnemy::Update(dt, coObjects);

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

		if (vx != 0)
		{
			isActive = false;
		}

		if (isActive)
		{
			if (start_untouchable != 0)
			{
				vx = 0.01;
				Untouchable();
			}
			else
			{
				if (vx > 0)
				{
					nx = 1;
					vx = FLEAMAN_WALKING_SPEED;
				}
				else
				{
					nx = -1;
					vx = -FLEAMAN_WALKING_SPEED;
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