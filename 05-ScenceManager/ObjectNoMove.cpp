#include "ObjectNoMove.h"
 


CObjectNoMove::CObjectNoMove()
{
	timeFire = 0;
	//state = OBJECTS_STATE_NORMAL;
}


CObjectNoMove::~CObjectNoMove()
{
}

void CObjectNoMove::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt);
	
	if (GetTickCount() - timeFire > TIME_FIRE && timeFire > 0)
	{
		timeFire = 0;
	}

}

void CObjectNoMove::Render()
{
	animation_set->at(0)->Render(x, y);

}

void CObjectNoMove::TimeFireDestroy()
{
	timeFire = GetTickCount();
	state = STATE_DESTROYED;
	//state = OBJECTS_STATE_DESTROY;
}