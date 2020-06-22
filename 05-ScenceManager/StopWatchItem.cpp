#include "StopWatchItem.h"

CStopWatchItem::CStopWatchItem(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;
	id = ID_STOPWATCHITEM;
	AddAnimation(ID_ANI_STOPWATCH);
}

CStopWatchItem::~CStopWatchItem()
{
}

void CStopWatchItem::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - STOPWATCH_ITEM_BBOX_HEIGHT;
	r = x + STOPWATCH_ITEM_BBOX_WIDTH;
	b = y;
}

void CStopWatchItem::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CItem::Update(dt, objects);

	if (!isOnGround)
		vy += STOPWATCH_ITEM_GRAVITY * dt;
}

void CStopWatchItem::Render() {
	animations[0]->Render(x, y);
}