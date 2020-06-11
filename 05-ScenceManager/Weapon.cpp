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
		float wl, wt, wr, wb;		// weapon object bbox
		float ol, ot, or , ob;		// object bbox
		GetBoundingBox(wl, wt, wr, wb);
		coObjects->at(i)->GetBoundingBox(ol, ot, or , ob);
		if (coObjects->at(i)->GetID() == ID_HIDEBRICK)
		{
			if (GetID() == ID_WHIP)
			{
				if (CGame::GetInstance()->IsIntersectAABB({ long(wl),long(wt), long(wr), long(wb) }, { long(ol), long(ot), long(or ), long(ob) })) {
					coObjects->at(i)->SetState(OBJECTS_STATE_DESTROY);
				}
			}

		}

		//OBJECT NO MOVE
		if (coObjects->at(i)->GetState() != OBJECTS_STATE_DESTROY) {
			if (CGame::GetInstance()->IsIntersectAABB({ long(wl),long(wt), long(wr), long(wb) }, { long(ol), long(ot), long(or ), long(ob) })) {
				switch (coObjects->at(i)->GetID())
				{
				case ID_TORCH:
				case ID_CANDLE:
					coObjects->at(i)->TimeFireDestroy();
					if (GetID() == ID_DAGGER) {
						this->SetState(STATE_DESTROYED);
					}
					break;			
				default:
					break;
				}
	
			}
		}

		//ENEMY
		if (coObjects->at(i)->GetState() == ENEMY_STATE_DESTROY) {
		}
		else
		{
			if (CGame::GetInstance()->IsIntersectAABB({ long(wl),long(wt), long(wr), long(wb) }, { long(ol), long(ot), long(or ), long(ob) })) {
				switch (coObjects->at(i)->GetID())
				{
				case ID_SPEARKNIGHT:
				case ID_ZOMBIE:
				case ID_BAT:
					if (coObjects->at(i)->GetState() != ENEMY_STATE_DESTROY)
					{
						coObjects->at(i)->BeDamagedEnemy(coObjects->at(i)->scoreEnemy);
					}
					coObjects->at(i)->TimeFireDestroy();
					
					/*if (coObjects->at(i)->GetHealthEnemy() <= 0)
					{
						if (coObjects->at(i)->GetState() != ENEMY_STATE_DESTROY)
						{
							coObjects->at(i)->BeDamagedEnemy(coObjects->at(i)->scoreEnemy);
						}
						coObjects->at(i)->TimeFireDestroy();
					}
					else
					{
						DebugOut(L" Dame %d\n", GetDamagedWeapon());
						coObjects->at(i)->SetHealthEnemy(GetDamagedWeapon() - coObjects->at(i)->GetHealthEnemy());
						DebugOut(L"Enemy Health %d\n", coObjects->at(i)->GetHealthEnemy());
					}*/

					if (GetID() == ID_DAGGER) {
						this->SetState(STATE_DESTROYED);
					}
					break;
				default:
					break;
				}

			}
		}
	}
}
void CWeapon::DamagedWeapon()
{
}


void CWeapon::Render()
{
	RenderBoundingBox();
}

void CWeapon::DestroyObject()
{
	timeAppearItem = GetTickCount();
}
