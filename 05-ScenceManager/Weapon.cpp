#include "Weapon.h"



CWeapon::CWeapon()
{
	timeFire = 0;
}


CWeapon::~CWeapon()
{
}
 
void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt);
	for (int i = 0;i < coObjects->size();i++) {
		if (coObjects->at(i)->GetID() == ID_TORCH) {
			float wl, wt, wr, wb;		// weapon object bbox
			float ol, ot, or , ob;		// object bbox
			GetBoundingBox(wl, wt, wr, wb);
			coObjects->at(i)->GetBoundingBox(ol, ot, or , ob);
			if (CGame::GetInstance()->IsIntersect({ long(wl),long(wt), long(wr), long(wb) }, { long(ol), long(ot), long(or ), long(ob) })) {
				//coObjects->at(i)->TimeFireDestroy();
					float x, y;
					coObjects->at(i)->GetPosition(x, y);
					switch (coObjects->at(i)->GetNextItemID())
					{
					case ID_HEART:
						CListItem::GetInstance()->ListItem.push_back(new CHeart({ x,y - 20 }));
						break;
					default:
						break;
					}
				coObjects->at(i)->SetState(STATE_DESTROYED);
			}
		}
	}
}
