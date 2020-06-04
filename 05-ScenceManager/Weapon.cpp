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
			coObjects->at(i)->GetID() == ID_CANDLE ||
			coObjects->at(i)->GetID() == ID_SPEARKNIGHT ||
			coObjects->at(i)->GetID() == ID_ZOMBIE ||
			coObjects->at(i)->GetID() == ID_BAT){
			float wl, wt, wr, wb;		// weapon object bbox
			float ol, ot, or , ob;		// object bbox
			GetBoundingBox(wl, wt, wr, wb);
			coObjects->at(i)->GetBoundingBox(ol, ot, or , ob);
			if (CGame::GetInstance()->IsIntersectAABB({ long(wl),long(wt), long(wr), long(wb) }, { long(ol), long(ot), long(or ), long(ob) })) {
				coObjects->at(i)->TimeFireDestroy();
				if (GetID() == ID_DAGGER) {
					this->SetState(STATE_DESTROYED);
				}
			}
		}
	}

	/*vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	
	//Collision with wall
	vector<LPGAMEOBJECT> wallObjects;
	coEvents.clear();
	for (int i = 0;i < coObjects->size();i++) {
		if (coObjects->at(i)->GetID() == ID_GROUND ||
			coObjects->at(i)->GetID() == ID_BRIDGE)
			wallObjects.push_back(coObjects->at(i));
	}

	CalcPotentialCollisions(&wallObjects, coEvents);
	if (GetID() == ID_HOLYWATER)
	{
		if (coEvents.size() == 0)
		{
			//x += dx;
			//y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			// block 
			x += min_tx*dx + nx*0.1f;
			y += min_ty*dy + ny*0.1f;
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CBrick*>(e->obj))
				{
					CBrick* brick = dynamic_cast<CBrick *>(e->obj);
					if (e->ny != 0)
					{
						isOnGroundFire = true;
					}
				}
			}
		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		coEvents.clear();
	}*/

}

void CWeapon::Render()
{
	RenderBoundingBox();
}

void CWeapon::DestroyObject()
{
	timeAppearItem = GetTickCount();
}
