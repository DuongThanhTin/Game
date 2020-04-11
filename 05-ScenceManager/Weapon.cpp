#include "Weapon.h"



CWeapon::CWeapon()
{
}


CWeapon::~CWeapon()
{
}

void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt);
	for (int i = 0;i < coObjects->size();i++) {
		if (coObjects->at(i)->GetID() == ID_TORCH) {
			float wl, wt, wr, wb;		// weapon object bbox
			float ol, ot, or , ob;		// object bbox
			GetBoundingBox(wl, wt, wr, wb);
			coObjects->at(i)->GetBoundingBox(ol, ot, or , ob);
			if (CGame::GetInstance()->IsIntersect({ long(wl),long(wt), long(wr), long(wb) }, { long(ol), long(ot), long(or ), long(ob) })) {
				DebugOut(L"COllision");
				float a, b;
				bool bb = false;
				coObjects->at(i)->GetPosition(a, b);
				CGameObject *nextItem;

				switch (coObjects->at(i)->GetNextItemID()) {
				case ID_HEART:
					nextItem = new CHeart({ 150,150 });
					DebugOut(L"Done a b %d %d:\n",a ,b);
					break;
				default:
					nextItem = NULL;
					break;
				}
				//if (nextItem)
				//coObjects->push_back(nextItem);

				//coObjects->at(i)->SetState(STATE_DESTROYED);
				this->SetState(STATE_DESTROYED);

			}

		}

	}
}
