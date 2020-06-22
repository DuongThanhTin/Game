#include "Ghost.h"



CGhost::CGhost()
{
}


CGhost::~CGhost()
{
}

CGhost::CGhost(D3DXVECTOR2 position, int nextItemID,int nxGhost)
{
	x = position.x;
	y = position.y;
	id = ID_GHOST;
	AddAnimation(ANI_DESTROY);
	nx = -1;
	this->originY = y;
	delta = 0;
	scoreEnemy = NUM_SCORE_ENEMY_SPEARKNIGHT;
	this->nextItemID = nextItemID;
	this->healthEnemy = 3;
	isOnGround = true;
}

void CGhost::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (isActive)
	{
		left = x;
		top = y - GHOST_BBOX_HEIGHT;
		right = x + GHOST_BBOX_WIDTH;
		bottom = y;
	}
	else
	{
		left = top = right = bottom = 0;
	}

}
void CGhost::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CEnemy::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;


	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);

	//Simon

	float ol, ot, or , ob;		// enemy bbox
	GetBoundingBox(ol, ot, or , ob);



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

		/*if (isActive)
		{
		vy -= 0.3f;
		vx += 0.001f;
		}

		if (y < 300)
		{
		vy += 0.0006f*dt;
		}*/

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj))
			{
				for (size_t i = 0; i < coObjects->size(); i++)
				{
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
	else if (isActive)
	{
		if (timeStopWatch == 0)
		{
			
			if (start_untouchable != 0)
			{
				vx = 0.00001;
				Untouchable();
			}
			else
			{
				vx += nx*GHOST_WALKING_SPEED;
				delta += 3;
				y = sin(delta * 3.14 / 180) * 12 + originY;
			}
		}
		else
		{
			vx = 0;
			vy = 0;
		}
	}


}

void CGhost::Render()
{
	if (state != ENEMY_STATE_DESTROY)
	{
		int ani = GHOST_ANI_WALKING_RIGHT;
		if (nx > 0)
		{
			ani = GHOST_ANI_WALKING_RIGHT;
		}
		else
		{
			ani = GHOST_ANI_WALKING_LEFT;
		}
		
		if (isActive)
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

void CGhost::SetState(int state)
{
	CGameObject::SetState(state);

}