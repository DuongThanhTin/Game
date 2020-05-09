#include "ObjectNoMove.h"
 


CObjectNoMove::CObjectNoMove()
{
	timeFire = 0;
	state = OBJECTS_STATE_NORMAL;
}


CObjectNoMove::~CObjectNoMove()
{
}

void CObjectNoMove::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt);
	for (int i = 0;i < coObjects->size();i++) {
		float wl, wt, wr, wb;		// weapon object bbox
		float ol, ot, or , ob;		// object bbox
		GetBoundingBox(wl, wt, wr, wb);
		coObjects->at(i)->GetBoundingBox(ol, ot, or , ob);
		if (CGame::GetInstance()->IsIntersect({ long(wl),long(wt), long(wr), long(wb) }, { long(ol), long(ot), long(or ), long(ob) })) {		
			if (GetTickCount() - timeFire > TIME_FIRE && timeFire > 0)
			{
				timeFire = 0;
				float x, y;
				coObjects->at(i)->GetPosition(x, y);
				switch (GetNextItemID())
				{
				case ID_HEART:
					CListItem::GetInstance()->ListItem.push_back(new CHeart({ x,y -10  }));
					break;
				case ID_WHIPUPGRADE:
					CListItem::GetInstance()->ListItem.push_back(new CWhipUpgrade({ x,y - 20 }));
					break;
				case ID_DAGGERITEM:
					CListItem::GetInstance()->ListItem.push_back(new CDaggerItem({ x,y - 20 }));
					break;
				case ID_MONEYBAG:
					CListItem::GetInstance()->ListItem.push_back(new CMoneyBag({ x,y }));
					break;
				case ID_BOOMERANGITEM:
					CListItem::GetInstance()->ListItem.push_back(new CBoomerangItem({ x,y }));
					break;
				case ID_SMALLHEART:
					CListItem::GetInstance()->ListItem.push_back(new CSmallHeart({ x,y -10}));
					break;
				default:
					break;
				}
				state = STATE_DESTROYED;
			}
		}
	}
}

void CObjectNoMove::Render()
{
	if (state == OBJECTS_STATE_DESTROY)
	{
		animation_set->at(OBJECTS_STATE_DESTROY)->Render(x, y);
	}
	else
	{
		animation_set->at(OBJECTS_STATE_NORMAL)->Render(x, y);
	}

}


void CObjectNoMove::TimeFireDestroy()
{
	timeFire = GetTickCount();
	state = OBJECTS_STATE_DESTROY;
}