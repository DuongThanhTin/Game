#include "StopWatch.h"

CStopWatch::CStopWatch()
{
	//x = position.x;
	//y = position.y-15;
	id = ID_STOPWATCH;
	//AddAnimation(ID_ANI_STOPWATCH);
}

CStopWatch::~CStopWatch()
{
}

void CStopWatch::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - STOPWATCH_ITEM_BBOX_HEIGHT;
	r = x + STOPWATCH_ITEM_BBOX_WIDTH;
	b = y;
}

void CStopWatch::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CWeapon::Update(dt, objects);
	DebugOut(L"%d\n", timeLock);
	timeLock = GetTickCount();
}

void CStopWatch::Render() {
	animations[0]->Render(x, y);
}