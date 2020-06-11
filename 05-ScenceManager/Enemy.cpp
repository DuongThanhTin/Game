#include "Enemy.h"



CEnemy::CEnemy()
{
	timeFire = 0;
	state = ENEMY_STATE_IDLE;
}


CEnemy::~CEnemy()
{
}

void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	//Collision with wall
	vector<LPGAMEOBJECT> wallObjects;
	for (int i = 0;i < coObjects->size();i++) {
		if (coObjects->at(i)->GetID() == ID_GROUND)
			wallObjects.push_back(coObjects->at(i));
	}

	if (id != ID_BAT)
	{
		CalcPotentialCollisions(&wallObjects, coEvents);
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
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

		if (ny < 0) {
			vy = 0;

			if (!isOnGround)
			{
				isOnGround = true;
			}
		}
		else {
			y += dy;
		}
		
	

		// clean up collision events
		for (auto iter : coEvents) delete iter;
		coEvents.clear();
	}


	for (int i = 0;i < coObjects->size();i++) {
		float wl, wt, wr, wb;		// weapon object bbox
		float ol, ot, or , ob;		// object bbox
		GetBoundingBox(wl, wt, wr, wb);
		coObjects->at(i)->GetBoundingBox(ol, ot, or , ob);
		if (CGame::GetInstance()->IsIntersectAABB({ long(wl),long(wt), long(wr), long(wb) }, { long(ol), long(ot), long(or ), long(ob) })) {
		
			if (GetTickCount() - timeFire > TIME_FIRE_ENEMY && timeFire > 0)
			{
				timeFire = 0;
				float x, y;
				coObjects->at(i)->GetPosition(x, y);
				this->state = STATE_DESTROYED;
				switch (GetNextItemID())
				{
				case ID_SMALLHEART:
					CListItem::GetInstance()->ListItem.push_back(new CSmallHeart({ x,y - 10 }));
					break;
				case ID_HEART:
					CListItem::GetInstance()->ListItem.push_back(new CHeart({ x,y - 10 }));
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
				default:
					break;
				}
				this->state = STATE_DESTROYED;
			}
		}
	}

	
}

void CEnemy::BeDamagedEnemy(int scoreEnemy)
{
	DebugOut(L"qwe %d\n", scoreEnemy);
	DebugOut(L"ASD %d\n", CSimon::GetInstance()->GetScore());
	CSimon::GetInstance()->IncreaseScore(scoreEnemy);
	
	
}

void CEnemy::TimeFireDestroy()
{
	timeFire = GetTickCount();
	this->state = ENEMY_STATE_DESTROY;
	vx = 0;
}

