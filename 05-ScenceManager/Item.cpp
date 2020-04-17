#include "Item.h"



CItem::CItem()
{
	timeDisappear = 0;
}


CItem::~CItem()
{
}

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> wallObjects;
	for (int i = 1; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetID() == ID_GROUND)
			wallObjects.push_back(coObjects->at(i));

	CalcPotentialCollisions(&wallObjects, coEvents);

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
		y += min_ty * dy + ny * 0.1f;

		if (ny != 0)
		{
			vx = 0;
			vy = 0;
			isOnGround = true;
			StartTimeDisappear();
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	coEvents.clear();

	if (GetTickCount() - timeDisappear > ITEM_DISAPPEAR_TIME && timeDisappear > 0)
		SetState(STATE_DESTROYED);
}

void CItem::StartTimeDisappear() {
	timeDisappear = GetTickCount();
}

void CItem::Render() {
	animations[0]->Render(x, y);
}