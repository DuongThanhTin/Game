#include "HolyWater.h"



CHolyWater::CHolyWater(D3DXVECTOR2 position, int nx)
{
	this->x = position.x;
	this->y = position.y - 15;
	this->nx = nx;
	vy = HOLYWATER_THROW_SPEED_Y;
	vx = HOLYWATER_FLY_SPEED;
	AddAnimation(ID_HOLYWATER_RIGHT); //Right
	AddAnimation(ID_HOLYWATER_LEFT); //Left
	AddAnimation(ID_HOLYWATER_FIRE); //Left
	id = ID_HOLYWATER;
	isOnGroundFire = false;
	timeHolyWaterFire = 0;
	timefly = GetTickCount();
	this->damagedWeapon = 1;
}


CHolyWater::~CHolyWater()
{
}

void CHolyWater::GetBoundingBox(float &l, float&t, float &r, float &b) {
	l = x;
	t = y - HOLYWATER_BBOX_HEIGHT;
	r = x + HOLYWATER_BBOX_WIDTH;
	b = y;
}

void CHolyWater::Render() {
	if (isOnGround)
	{
		animations[2]->Render(x, y);
	}
	else
	{
		if (nx > 0)
			animations[0]->Render(x, y);
		else
			animations[1]->Render(x, y);
	}

	RenderBoundingBox();
}

void CHolyWater::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CWeapon::Update(dt, coObjects);
	if (GetTickCount() - timeHolyWaterFire >= TIME_HOLYWATER_FIRE && timeHolyWaterFire > 0)
		SetState(STATE_DESTROYED);

	if (!isOnGround)
	{
		if (GetTickCount() - timefly > TIME_HOLYWATER_FLY)
		{
			vy += HOLYWATER_GRAVITY*dt;
			y += vy*dt;
			if (nx > 0)
				x += vx*dt;
			else
				x -= vx*dt;
		}
		else if (timefly >0)
		{
			
			y -= HOLYWATER_THROW_SPEED_Y*dt;
			if (nx > 0)
				x += vx*dt;
			else
				x -= vx*dt;
		}

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		vector<LPGAMEOBJECT> wallObjects;
		for (int i = 1; i < coObjects->size(); i++)
			if (coObjects->at(i)->GetID() == ID_GROUND)
				wallObjects.push_back(coObjects->at(i));

		CalcPotentialCollisions(&wallObjects, coEvents);

		// No collision occured, proceed normally
		if (coEvents.size() != 0)
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			// block 
			y += min_ty * dy + ny * 0.1f;

			if (ny != 0)
			{
				vx = 0;
				vy = 0;
				isOnGround = true;
				timeHolyWaterFire = GetTickCount();
			}
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		coEvents.clear();
	}
}
