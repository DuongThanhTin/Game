#include "Weapon.h"



CWeapon::CWeapon()
{
	timeAppearItem = 0;
	timeCollisionEnemy = 0;
	//AddAnimation(902);
}


CWeapon::~CWeapon()
{
}

void CWeapon::AppearHitEffect()
{
	if (hitEffects.size() > 0)
	{

		if (timeHitEffect == 0)
		{
			timeHitEffect = GetTickCount();
		}

		else if (GetTickCount() - timeHitEffect > TIME_HITEFFECT)
		{
			
			timeHitEffect = 0;
			hitEffects.clear();
		}

		// rendering hit effect based on the coordinate vector
		for (auto iter : hitEffects)
			hitEffect->Render(iter[0], iter[1]);
	}
}
 
void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt);
	//DebugOut(L"ASD %d \n", timeHitEffect);
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
					coObjects->at(i)->BeDamaged();
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
				{//BeDamagedEnemy: Tăng điểm
				case ID_SPEARKNIGHT:
				case ID_SKELETON:
				case ID_FLEAMAN:
				case ID_RAVEN:
				case ID_GHOST:
				{
					hitEffects.push_back({ (ol + or ) / 2, (ot + ob) / 2 });
					if (GetID() == ID_WHIP)
					{
						coObjects->at(i)->TakeDamagedEnemy(GetDamageWhip());
						DebugOut(L"Health %d\n", coObjects->at(i)->healthEnemy);
					}

					else if (GetID() == ID_DAGGER)
					{
						AppearHitEffect();
						coObjects->at(i)->TakeDamagedEnemy(1);
						DebugOut(L"Health %d\n", coObjects->at(i)->healthEnemy);
						if (timeHitEffect == 0)
						{
							this->SetState(STATE_DESTROYED);
						}
					}

					else if (GetID() == ID_BOOMERANG || GetID() == ID_AXE || GetID() == ID_HOLYWATER)
					{					
						coObjects->at(i)->TakeDamagedEnemy(GetDamageWhip());
						DebugOut(L"Health %d\n", coObjects->at(i)->healthEnemy);
					}


					if (coObjects->at(i)->healthEnemy <= 0)
					{
						coObjects->at(i)->BeDamagedEnemy(coObjects->at(i)->scoreEnemy);
					}
					
					break; 
				}
				
				case ID_ZOMBIE:
				case ID_BAT:
				{
					if (GetID() == ID_WHIP)
					{
						coObjects->at(i)->TakeDamagedEnemy(GetDamageWhip());
					}

					else if (GetID() == ID_DAGGER)
					{
						DebugOut(L"Health %d\n", coObjects->at(i)->healthEnemy);
						coObjects->at(i)->TakeDamagedEnemy(GetDamageWhip());
						this->SetState(STATE_DESTROYED);

					}

					else if (GetID() == ID_BOOMERANG || GetID() == ID_AXE || GetID() == ID_HOLYWATER)
					{
						coObjects->at(i)->TakeDamagedEnemy(GetDamageWhip());
					}

					if (coObjects->at(i)->healthEnemy <= 0)
					{
						coObjects->at(i)->BeDamagedEnemy(coObjects->at(i)->scoreEnemy);
					}
				
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
}

void CWeapon::DestroyObject()
{
	timeAppearItem = GetTickCount();
}
