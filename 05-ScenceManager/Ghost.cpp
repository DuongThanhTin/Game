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
	nx = nxGhost;
	//scoreEnemy = NUM_SCORE_ENEMY_SPEARKNIGHT;
	this->nextItemID = nextItemID;
	//	this->healthEnemy = 3;
	isOnGround = true;
}

void CGhost::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y - GHOST_BBOX_HEIGHT;
	right = x + GHOST_BBOX_WIDTH;
	bottom = y;

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
	//else
		//vy += 0.0006f*dt;


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
		animation_set->at(ani)->Render(x, y);
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