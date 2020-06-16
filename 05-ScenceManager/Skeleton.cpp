#include "Skeleton.h"



CSkeleton::CSkeleton()
{
}


CSkeleton::~CSkeleton()
{
}

CSkeleton::CSkeleton(D3DXVECTOR2 position, int nextItemID, float limitedLeft, float limitedRight, int nxSkeleton)
{
	x = position.x;
	y = position.y;
	id = ID_SKELETON;
	AddAnimation(ANI_DESTROY);
	nx = nxSkeleton;
	scoreEnemy = NUM_SCORE_ENEMY_SPEARKNIGHT;
	this->nextItemID = nextItemID;
//	this->healthEnemy = 3;
	isOnGround = true;
}

void CSkeleton::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y - SKELETON_BBOX_HEIGHT;
	right = x + SKELETON_BBOX_WIDTH;
	bottom = y;

}
void CSkeleton::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
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
					if (coObjects->at(i)->GetID() == ID_GROUND)
					{
						if (e->ny != 0 && isActive && isOnGround)
						{
							//this->vx *= -1;
							isActive = false;
						//	state = FLEAMAN_STATE_WALKING;
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

void CSkeleton::Render()
{
	if (state != ENEMY_STATE_DESTROY)
	{
		int ani = SKELETON_ANI_WALKING_RIGHT;
		if (nx > 0)
		{
			ani = SKELETON_ANI_WALKING_RIGHT;
		}
		else
		{
			ani = SKELETON_ANI_WALKING_LEFT;
		}
		animation_set->at(ani)->Render(x, y);
	}
	else
	{
		animations[0]->Render(x, y);
	}


	RenderBoundingBox();
}

void CSkeleton::SetState(int state)
{
	CGameObject::SetState(state);

}