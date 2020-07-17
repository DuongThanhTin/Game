#include "Skeleton.h"



CSkeleton::CSkeleton()
{
}


CSkeleton::~CSkeleton()
{
}

CSkeleton::CSkeleton(D3DXVECTOR2 position, int nextItemID, float limitedLeft, float limitedRight, int nxSkeleton , int idSkeleton)
{
	x = position.x;
	y = position.y;
	id = ID_SKELETON;
	AddAnimation(ANI_DESTROY);
	this->limitedLeft = limitedLeft;
	this->limitedRight = limitedRight;
	nx = nxSkeleton;
	vx = SKELETON_WALKING_SPEED;
	scoreEnemy = NUM_SCORE_ENEMY_SPEARKNIGHT;
	this->nextItemID = nextItemID;
	this->healthEnemy = 3;
	isOnGround = true;
	timeAttackBone = 0;
	this->id_AISkeleton = idSkeleton;
}

void CSkeleton::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	if (!isDestroy)
	{
		left = x;
		top = y - SKELETON_BBOX_HEIGHT;
		right = x + SKELETON_BBOX_WIDTH;
		bottom = y;
	}
	else
	{
		left = top = right = bottom = 0;
	}

}
void CSkeleton::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	CEnemy::Update(dt, coObjects);
	//if (isInGrid != true)
		//return;

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


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj))
			{
				for (size_t i = 0; i < coObjects->size(); i++)
				{
					if (coObjects->at(i)->GetID() == ID_GROUND)
					{
					}
				}
			}
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
				if (timeStopWatch == 0)
				{
					isStopFrame = false;
					if (timeAttackBone == 0)
					{
						timeAttackBone = GetTickCount();
					}

					else if (GetTickCount() - timeAttackBone > TIME_ATTACK_BONE)
					{
						if(bonesOb.size()<2)
						{
							if (id_AISkeleton == 1)
							{
								bonesOb.push_back(new CBone({ x,y }, 1));
								bonesOb.push_back(new CBone({ x-10,y+10 }, 1));
							}
							else
							{
								bonesOb.push_back(new CBone({ x,y }, -1));
								bonesOb.push_back(new CBone({ x + 10,y - 10 }, -1));
							}
							
							
						}
						
					
						timeAttackBone = 0;
						vx = 0;
					}


					if (vx > 0)
					{
						vx = SKELETON_WALKING_SPEED;
					}
					else
					{
						vx = -SKELETON_WALKING_SPEED;
					}
				}
				else
				{
					isStopFrame = true;
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

		if (timeStopWatch == 0)
		{
			//Update Bone
			for (size_t i = 0; i < bonesOb.size(); i++)
			{
				
				bonesOb[i]->Update(dt, coObjects);
				coObjects->push_back(bonesOb[i]);
			}
		}

		for (size_t i = 0; i < bonesOb.size(); i++)
		{
			float ol, ot, or , ob;		// enemy bbox
			float vl, vt, vr, vb;		// viewport bbox
			CViewPort::GetInstance()->GetBoundingBox(vl, vt, vr, vb);
			bonesOb[i]->GetBoundingBox(ol, ot, or , ob);
			if (!CGame::GetInstance()->IsIntersectAABB({ long(ol),long(ot), long(or ), long(ob) }, { long(vl), long(vt), long(vr), long(vb) }))
			{
				bonesOb.erase(bonesOb.begin() + i);
				i--;
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


	for (size_t i = 0; i < bonesOb.size(); i++)
	{
		bonesOb[i]->Render();
	}
	RenderBoundingBox();
}

void CSkeleton::SetState(int state)
{
	CGameObject::SetState(state);

}