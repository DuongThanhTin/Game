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
	
		/*CGameObject* nextItem;
		switch (GetNextItemID())
		{
		case ID_HEART:
			nextItem = new CHeart({ x, y - 20 });
			objectsItem.push_back(nextItem);
			coObjects->push_back(nextItem);
			
			break;
		default:
			break;
		}	*/
	}


	/*for (size_t i = 0; i < objectsItem.size(); i++)
	{
		if (objectsItem[i]->GetID() == ID_HEART)
		{
			coObjects->push_back(objectsItem[i]);
			objectsItem[i]->Update(dt, coObjects);
			
		}
	}*/


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