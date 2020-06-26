#include "CrystalBall.h"



CCrystalBall::CCrystalBall(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;
	id = ID_CRYSTALBALL;
	AddAnimation(995);
}

CCrystalBall::~CCrystalBall()
{
}

void CCrystalBall::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - CRYSTALBALL_ITEM_BBOX_HEIGHT;
	r = x + CRYSTALBALL_ITEM_BBOX_WIDTH;
	b = y;
}

void CCrystalBall::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CItem::Update(dt, objects);

	if (!isOnGround)
		vy += CRYSTALBALL_ITEM_GRAVITY * dt;
}

void CCrystalBall::Render() {
	animations[0]->Render(x, y);
}