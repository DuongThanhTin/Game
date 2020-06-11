#include "CrownItem.h"



CCrownItem::CCrownItem(D3DXVECTOR2 position, int crownUp)
{
	this->x = position.x;
	this->y = position.y;
	AddAnimation(ANI_CROWN);
	id = ID_CROWN;
	this->crownUp_Y = crownUp;
}


CCrownItem::~CCrownItem()
{
}

void CCrownItem::GetBoundingBox(float &l, float&t, float &r, float &b) {
	l = x;
	t = y - CROWN_BBOX_HEIGHT;
	r = x + CROWN_BBOX_WIDTH;
	b = y;
}

void CCrownItem::Render() {
	animations[0]->Render(x, y);
}

void CCrownItem::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

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
		x += min_tx*dx + nx*0.1f;
		y += min_ty * dy + ny * 0.1f;

		
	}

	if (isActive)
	{
		y -= CROWN_UP_SPEED*dt;
	}

	if (y < crownUp_Y)
	{
		y = crownUp_Y;
	}


	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	coEvents.clear();
}