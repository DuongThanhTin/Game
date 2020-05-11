#include "Boomerang.h"




CBoomerang::CBoomerang(D3DXVECTOR2 position, int nx)
{
	this->x = position.x;
	this->y = position.y - 15;
	this->nx = nx;
	vx = BOOMERANG_FLY_SPEED;
	AddAnimation(1011); //Right
	AddAnimation(1012); //Left
	id = ID_BOOMERANG;
	timefly = GetTickCount();
	isFlyReturn = false;
}


CBoomerang::~CBoomerang()
{
}

void CBoomerang::GetBoundingBox(float &l, float&t, float &r, float &b) {
	l = x;
	t = y - BOOMERANG_BBOX_HEIGHT;
	r = x + BOOMERANG_BBOX_WIDTH;
	b = y;
}

void CBoomerang::Render() {
	if (nx > 0) {
		animations[0]->Render(x, y);
	}
	else
		animations[1]->Render(x, y);

	RenderBoundingBox();
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CWeapon::Update(dt, coObjects);
	if (GetTickCount() - timefly > TIME_FLY)
	{
		vx = -nx*BOOMERANG_FLY_SPEED;
		x += vx*dt;
		isFlyReturn = true;
	}
	else if (timefly > 0)
	{
		if (nx > 0)
		{
			x += vx*dt;
		}
		else
		{
			x += -vx*dt;
		}
	}


	if (isFlyReturn)
	{
		float sl, st, sr, sb;		// simon object bbox
		float bl, bt, br, bb;		// bomerang bbox
		GetBoundingBox(bl, bt, br, bb);
		//CSimon::GetInstance()->GetBoundingBox(sl, st, sr, sb);
		/*if (CGame::GetInstance()->IsIntersect({ long(bl),long(bt), long(br), long(bb) }, { long(sl), long(st), long(sr), long(sb) }))
		{
			DebugOut(L"SAD12");
			state = STATE_DESTROYED;
		}*/
	}
}