#include "Weapon.h"



CWeapon::CWeapon()
{
	timeAppearItem = 0;
}


CWeapon::~CWeapon()
{
}
 
void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt);
	for (int i = 0;i < coObjects->size();i++) {
		if (coObjects->at(i)->GetID() == ID_TORCH||
			coObjects->at(i)->GetID() == ID_SPEARKNIGHT || 
			coObjects->at(i)->GetID() == ID_ZOMBIE) {
			float wl, wt, wr, wb;		// weapon object bbox
			float ol, ot, or , ob;		// object bbox
			GetBoundingBox(wl, wt, wr, wb);
			coObjects->at(i)->GetBoundingBox(ol, ot, or , ob);
			if (CGame::GetInstance()->IsIntersect({ long(wl),long(wt), long(wr), long(wb) }, { long(ol), long(ot), long(or ), long(ob) })) {
				coObjects->at(i)->TimeFireDestroy();
				if (GetID() == ID_DAGGER) {
					this->SetState(STATE_DESTROYED);
				}
			}
		}
	}
	
}

void CWeapon::Render()
{
	RenderBoundingBox();
}

void CWeapon::DestroyObject()
{
	timeAppearItem = GetTickCount();
}
