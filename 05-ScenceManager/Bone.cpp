#include "Bone.h"




CBone::CBone(D3DXVECTOR2 position, int nx)
{
	x = position.x;
	y = position.y;
	this->nx = nx;
	this->nxSkeleton = nx;
	id = ID_BONE;
	vx = nx * BONE_SPEED_X;
	timefly = GetTickCount();
	AddAnimation(ID_ANI_BONE_LEFT);
	AddAnimation(ID_ANI_BONE_RIGHT);
}

CBone::~CBone()
{
}

void CBone::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - BONE_BBOX_HEIGHT;
	r = x + BONE_BBOX_WIDTH;
	b = y;
	if (state == ENEMY_STATE_DESTROY)
		l = t = r = b = 0;
}

void CBone::Render()
{
	int ani;
	if (nxSkeleton == 1)
	{
		ani = 0;
	}
	else
		ani = 1;
	animations[ani]->Render(x, y);
}

void CBone::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CEnemy::Update(dt, coObjects);

	for (auto iter : *coObjects)
	{
		if (iter->GetID() == ID_SIMON)
		{
			float sl, st, sr, sb;		// simon object bbox
			float ol, ot, or , ob;		// object bbox
			iter->GetBoundingBox(sl, st, sr, sb);
			GetBoundingBox(ol, ot, or , ob);
			if (CGame::GetInstance()->IsIntersectAABB({ long(sl),long(st), long(sr), long(sb) }, { long(ol), long(ot), long(or ), long(ob) })) {
				iter->BeHurted();
			}
		}
	}


	if (GetTickCount() - timefly > TIME_BONE_FLY)
	{
		vy += BONE_GRAVITY;
		y += vy*dt;

		if (nxSkeleton == 1)
		{
			x += vx*dt;
		}
		else
		{
			x += vx*dt *2;
		}

	}
	else if (timefly >0)
	{
		y -= BONE_THROW_SPEED_Y*dt;
		y -= vy*dt;
		if (nxSkeleton == 1)
		{
			x += vx*dt;
		}
		else
		{
			x += vx*dt*2;
		}
	}
}