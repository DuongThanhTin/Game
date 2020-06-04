#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include "Simon.h"
#include "Game.h"
#include "Goomba.h"
#include "Portal.h"
#include "ListItem.h"

CSimon* CSimon::__instance;
CSimon::CSimon() {
	id = ID_SIMON;
	untouchable = 0;
	transformtime = 0;
	jumpStart = 0;
	attackStart = 0;
	attackSubStart = 0;
	untouchableStart = 0;
	subWeaponID = 0;
	isOnGround = false;
	isOnStair = false;
	isLockUpdate = false;
	isSwitchCam = false;
	eatItemStart = 0;
	collidingStair = NULL;
	whipSwitchSceneLevel = CWhip::GetInstance();
	whip = new CWhip();
	whip->SetLevel(whipSwitchSceneLevel->GetLevel());
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
	CListItem * listItem = CListItem::GetInstance();
	
	D3DXVECTOR2 position;
	// Simple fall down
	if (!isOnStair)
	{
		vy += SIMON_GRAVITY*dt;
	}
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	//Collide Object
	//Collision with wall
	vector<LPGAMEOBJECT> wallObjects;
	for (int i = 0;i < coObjects->size();i++) {
		if (coObjects->at(i)->GetID() == ID_GROUND||
			coObjects->at(i)->GetID() == ID_BRIDGE )
			wallObjects.push_back(coObjects->at(i));
	}

	//Collision with items
	vector<LPGAMEOBJECT> itemObjects;
	for (int i = 0;i < listItem->ListItem.size();i++) {
		if (listItem->ListItem[i]->GetID() == ID_HEART ||
			listItem->ListItem[i]->GetID() == ID_SMALLHEART ||
			listItem->ListItem[i]->GetID() == ID_WHIPUPGRADE ||
			listItem->ListItem[i]->GetID() == ID_DAGGERITEM ||
			listItem->ListItem[i]->GetID() == ID_MONEYBAG ||
			listItem->ListItem[i]->GetID() == ID_BOOMERANGITEM ||
			listItem->ListItem[i]->GetID() == ID_AXEITEM ||
			listItem->ListItem[i]->GetID() == ID_MONEYBAGWHITE ||
			listItem->ListItem[i]->GetID() == ID_MONEYBAGBLUE)
			itemObjects.push_back(listItem->ListItem[i]);
	}

	//Collision with Enemy
	vector<LPGAMEOBJECT> enemyObjects;
	for (int i = 0;i < coObjects->size();i++) {
		if (coObjects->at(i)->GetID() == ID_SPEARKNIGHT||
			coObjects->at(i)->GetID() == ID_BAT)
			enemyObjects.push_back(coObjects->at(i));
	}

	//Collide Object
	vector<LPGAMEOBJECT> Objects;
	for (int i = 0;i < coObjects->size();i++) {
		Objects.push_back(coObjects->at(i));
	}

	// turn off collision when die 
	if (state != SIMON_STATE_DIE) {

		//Collision wall
		if (!isOnStair)
		{
			CalcPotentialCollisions(&wallObjects, coEvents);
		}

		//Coliision Object no see
		for (auto iter : Objects)
		{
			float sl, st, sr, sb;		// simon object bbox
			float ol, ot, or , ob;		// object bbox
			GetBoundingBox(sl, st, sr, sb);
			iter->GetBoundingBox(ol, ot, or , ob);
			if (CGame::GetInstance()->IsIntersectAABB({ long(sl),long(st), long(sr), long(sb) }, { long(ol), long(ot), long(or ), long(ob) })) {
				switch (iter->GetID()) {
				case ID_STAIR:
					collidingStair = dynamic_cast<CStair*>(iter);
					break;
				case ID_AREAACTIVE:
					for (auto iter2 : enemyObjects)
					{
						CAreaActive *area = dynamic_cast<CAreaActive*>(iter);

						if (iter2->GetID() == ID_BAT)
						{
							if (area->GetspecEnemyActive() == iter2->GetAreaActiveEnemy())
							{
								iter2->isActive = true;
							}
						}
					}
					break;

				case ID_AREASWITCHCAM:
				{
					CAreaSwitchCam *areaswitchcam = dynamic_cast<CAreaSwitchCam*>(iter);
					if (dynamic_cast<CAreaSwitchCam*>(iter))
					{
						switch (areaswitchcam->GetSceneID())
						{
						case SCENE_2:
							isSwitchCam = true;
							SetPosition(areaswitchcam->GetPlayerX(), y);
						case SCENE_3:
							//isSwitchCam = true;
							SetPosition(areaswitchcam->GetPlayerX(), y - areaswitchcam->GetPlayerY());
						default:
							break;
						}
					}
				}
				default:
					break;
				}	
			}	

		}

		//Collision SubWeapon
		for (auto iter : subWeapon)
		{
			float sl, st, sr, sb;		// simon object bbox
			float wl, wt, wr , wb;		// object bbox
			GetBoundingBox(sl, st, sr, sb);
			iter->GetBoundingBox(wl, wt, wr , wb);
			if (CGame::GetInstance()->IsIntersectAABB({ long(sl),long(st), long(sr), long(sb) }, { long(wl), long(wt), long(wr ), long(wb) })) {
				switch (iter->GetID()) {
				case ID_BOOMERANG:
					iter->SetState(STATE_DESTROYED);
					break;
				default:
					break;
				}
			}
		}


		//Collision Item
		for (auto iter : itemObjects) {
			float sl, st, sr, sb;		// simon object bbox
			float ol, ot, or , ob;		// object bbox
			GetBoundingBox(sl, st, sr, sb);
			iter->GetBoundingBox(ol, ot, or , ob);
			if (CGame::GetInstance()->IsIntersectAABB({ long(sl),long(st), long(sr), long(sb) }, { long(ol), long(ot), long(or ), long(ob) })) {
				switch (iter->GetID()) {
				case ID_HEART:
					DebugOut(L"Collsion Heart\n");
					break;
				case ID_WHIPUPGRADE:
					StartEatItem();
					UpgradeWhip();
					DebugOut(L"Collsion Whip Upgrade\n");
					break;
				case ID_DAGGERITEM:
					StartEatItem();
					SetSubWeapon(ID_DAGGER);
					DebugOut(L"Collsion Dagger\n");
					break;
				case ID_MONEYBAG:
					DebugOut(L"Collsion Moneybag\n");
					break;
				case ID_BOOMERANGITEM:
					StartEatItem();
					SetSubWeapon(ID_BOOMERANG);
					DebugOut(L"Collsion BOOMERANGITEM\n");
					break;
				case ID_SMALLHEART:
					DebugOut(L"Collsion SmallHeart\n");
				case ID_AXEITEM:
					DebugOut(L"Collsion SmallHeart\n");
				case ID_MONEYBAGWHITE:
					DebugOut(L"Collsion SmallHeart\n");
				case ID_MONEYBAGBLUE:
					DebugOut(L"Collsion SmallHeart\n");
				default:
					break;
				}
				iter->SetState(STATE_DESTROYED);
			}
		}

		//Collision Enemy
		for (auto iter : enemyObjects) {
			float sl, st, sr, sb;		// simon object bbox
			float ol, ot, or , ob;		// enemy bbox
			GetBoundingBox(sl, st, sr, sb);
			iter->GetBoundingBox(ol, ot, or , ob);
			if (CGame::GetInstance()->IsIntersectAABB({ long(sl),long(st), long(sr), long(sb) }, { long(ol), long(ot), long(or ), long(ob) })) {
				if (iter->state != ENEMY_STATE_DESTROY)
				{
					StartUntouchable();
					iter->TimeFireDestroy();
				}
			}
		}
	}

	CViewPort* viewport = CViewPort::GetInstance();
	
	//Enemy Out of Camera
	for (size_t i = 0; i < enemyObjects.size(); i++)
	{
		float ol, ot, or , ob;		// enemy bbox
		float vl, vt, vr, vb;		// viewport bbox
		float sl, st, sr, sb;		//simon bbox
		enemyObjects[i]->GetBoundingBox(ol, ot, or , ob);
		viewport->GetBoundingBox(vl, vt, vr, vb);
		GetBoundingBox(sl, st, sr, sb);
		if (!CGame::GetInstance()->IsIntersectAABB({ long(ol),long(ot), long(or ), long(ob) }, { long(vl), long(vt), long(vr), long(vb) }))
		{
			enemyObjects.erase(enemyObjects.begin() + i);
			i--;
		}
		else if (!CGame::GetInstance()->IsIntersectAABB({ long(sl),long(st), long(sr), long(sb) }, { long(vl), long(vt), long(vr), long(vb) }))
		{
			if (y > vr)
			{
				//Reset(460, 80);
			}
		}
		
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

		if (nx != 0) vx = 0;

		if (ny < 0) {
			vy = 0;

			if (!isOnGround)
			{
				isOnGround = true;
			}
		}

		else y += dy;

		//On Bridge
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i]; 
			if (dynamic_cast<CBridge*>(e->obj))
			{
				CBridge* bridge = dynamic_cast<CBridge *>(e->obj);
				if (e->ny != 0)
				{
					x += bridge->vx*2*dt;
				}
			}
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				if (!(e->ny && e->nx) && vy > 0)
				{
					
				}
			}
		}
	}
	
	// clean up collision events
	for (auto iter : coEvents) delete iter;
	coEvents.clear();

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	// update jump state
	if (isOnGround == true) {
		jumpStart = 0;
	}

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchableStart > SIMON_UNTOUCHABLE_TIME)
	{
		untouchableStart = 0;
		untouchable = 0;
		
	}
	
	// transform simon
	if (GetTickCount() - eatItemStart > SIMON_EATITEM_TIME)
	{
		UnLockUpdate();
		transformtime = 0;
		eatItemStart = 0;
	}
	else if (transformtime > 0)
	{
		vx = 0;
		vy = 0;
	}

	// update attack state and whip
	UpdateWhip(dt, coObjects);

	//Update attack subweapon
	UpdateSubWeapon(dt, coObjects);

	//Update on Stair
	UpdateOnStair();
}

void CSimon::Render()
{
	//State http://gameprogrammingpatterns.com/state.html
	int ani;

	if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	else if (state == SIMON_STATE_ATTACK) {
		if (nx > 0)
			ani = SIMON_ANI_ATTACK_RIGHT;
		else
			ani = SIMON_ANI_ATTACK_LEFT;
	}

	else if (state == SIMON_STATE_ATTACK_SUBWEAPON) {
		if (nx > 0)
			ani = SIMON_ANI_ATTACK_RIGHT;
		else
			ani = SIMON_ANI_ATTACK_LEFT;
	}

	else if (state == SIMON_STATE_JUMP) {
		if (vy < 0) //!isOnGround
		{ 
			if (nx > 0)
				ani = SIMON_ANI_SIT_RIGHT;
			else
				ani = SIMON_ANI_SIT_LEFT;
		}
		else {
			if (nx > 0)
				ani = SIMON_ANI_IDLE_RIGHT;
			else
				ani = SIMON_ANI_IDLE_LEFT;
		}
	}
	else if (state == SIMON_STATE_SIT) {
		if (nx > 0)
			ani = SIMON_ANI_SIT_RIGHT;
		else
			ani = SIMON_ANI_SIT_LEFT;
	}
	else if (state == SIMON_STATE_SIT_ATTACK) {
		if (nx > 0)
			ani = SIMON_ANI_SIT_ATTACK_RIGHT;
		else
			ani = SIMON_ANI_SIT_ATTACK_LEFT;
	}
	else if(state== SIMON_STATE_WALKING_RIGHT){
		ani = SIMON_ANI_WALKING_RIGHT;
	}
	else if (state == SIMON_STATE_WALKING_LEFT) {
		ani = SIMON_ANI_WALKING_LEFT;
	}

	//On Stair
	else if (state == SIMON_STATE_IDLE_STAIR) { //Idle On Stair
		if (nx > 0)
		{
			if (ny > 0)
				ani = SIMON_ANI_STAIR_GOUP_IDLE_RIGHT;
			else
				ani = SIMON_ANI_STAIR_GODOWN_IDLE_RIGHT;
		}
		else
		{
			if (ny > 0)
				ani = SIMON_ANI_STAIR_GOUP_IDLE_LEFT;
			else
				ani = SIMON_ANI_STAIR_GODOWN_IDLE_LEFT;
		}
	}
	else if (state == SIMON_STATE_GOUP_STAIR) {
		if (nx > 0)
			ani = SIMON_ANI_STAIR_GOUP_RIGHT;
		else 
			ani = SIMON_ANI_STAIR_GOUP_LEFT;
	}
	else if (state == SIMON_STATE_GODOWN_STAIR) {
		if (nx > 0)
			ani = SIMON_ANI_STAIR_GODOWN_RIGHT;
		else
			ani = SIMON_ANI_STAIR_GODOWN_LEFT;
	}
	else if (state == SIMON_STATE_ATTACK_ON_STAIR) { //Attack On Stair
		if (nx > 0)
		{
			if (ny > 0)
				ani = SIMON_ANI_STAIR_GOUP_ATTACK_RIGHT;
			else
				ani = SIMON_ANI_STAIR_GODOWN_ATTACK_RIGHT;
		}
		else
		{
			if (ny > 0)
				ani = SIMON_ANI_STAIR_GOUP_ATTACK_LEFT;
			else
				ani = SIMON_ANI_STAIR_GODOWN_ATTACK_LEFT;;
		}
	}

	else {
		if (nx > 0)
			ani = SIMON_ANI_IDLE_RIGHT;
		else
			ani = SIMON_ANI_IDLE_LEFT;
	}

	//Transform simon
	if (eatItemStart > 0) {
		if (nx > 0)
			ani = SIMON_ANI_EATITEM_RIGHT;
		else
			ani = SIMON_ANI_EATITEM_LEFT;
	}

	int alpha = 255;
	if (untouchableStart > 0)
	{
		alpha = 128;
		if (nx > 0)
			ani = SIMON_ANI_DEFLECT_RIGHT;
		else
			ani = SIMON_ANI_DEFLECT_LEFT;
	}
	animation_set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox();
	if (attackStart)
		whip->Render();

	for (auto iter : subWeapon)
		iter->Render();
}

void CSimon::RenderBoundingBox(int alpha)
{
	CGameObject::RenderBoundingBox(alpha);
	whip->RenderBoundingBox(alpha);
}

void CSimon::SetState(int state)
{
	if (untouchableStart > 0)
		return;

	if (attackStart > 0)
		return;

	if (attackSubStart > 0)
		return;
	
	if (jumpStart > 0 && state != SIMON_STATE_ATTACK && state != SIMON_STATE_ATTACK_SUBWEAPON)
		return;

	if (eatItemStart > 0)
		return;

	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_IDLE_STAIR:
		isOnStair = true;
		break;
	case SIMON_STATE_ATTACK:
		break;
	case SIMON_STATE_ATTACK_SUBWEAPON:
		break;
	case SIMON_STATE_ATTACK_ON_STAIR:
		SetSpeed(0, 0);
		break;
	case SIMON_STATE_EATITEM:
		break;
	case SIMON_STATE_COLLISION_ENEMY:
		SetSpeed(-nx*SIMON_JUMP_DEFLECT_SPEED_X,-SIMON_JUMP_DEFLECT_SPEED);
		break;
	case SIMON_STATE_SIT:
		SetSpeed(0, vy);
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMON_STATE_GOUP_STAIR:
		nx = collidingStair->GetNx();
		ny = 1;
		SetSpeed(nx*SIMON_ON_STAIR_SPEED, -SIMON_ON_STAIR_SPEED);
		isOnStair = true;
		break;
	case SIMON_STATE_GODOWN_STAIR:
		nx = -collidingStair->GetNx();
		ny = -1;
		SetSpeed(nx*SIMON_ON_STAIR_SPEED, SIMON_ON_STAIR_SPEED);
		isOnStair = true;
		break;

	}
}

void CSimon::SetSubWeapon(int subWeaponID)
{
	this->subWeaponID = subWeaponID;
	DebugOut(L"SUB WEAPON : %d\n", subWeaponID);
}

void CSimon::UpdateWhip(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	if (GetTickCount() - attackStart <= SIMON_ATTACK_TIME)
	{
		float whip_X, whip_Y;
		if (state == SIMON_STATE_SIT_ATTACK) 
		{
			whip_Y = y + WEAPON_SIMON_SIT_ATTACK;
		}
		else
			whip_Y = y;
		
		if (state == SIMON_STATE_ATTACK_ON_STAIR)
		{
			if (nx < 0 && ny < 0)
			{
				whip_X = x + 3; //Modify location Whip Simon GoDown attack Left
			}
			else if (nx > 0 && ny > 0)
			{
				whip_X = x;
			}
			else if (nx > 0 && ny < 0)
			{
				whip_X = x;
			}
			else if (nx < 0 && ny > 0)
			{
				whip_X = x+7;
			}
		}
		else
		{
			whip_X = x;
		}
		whip->Update(dt, objects, { whip_X, whip_Y }, nx);
	}
	else if (attackStart > 0)
	{
		
		attackStart = 0;
		if (state == SIMON_STATE_SIT_ATTACK)
		{
			state = SIMON_STATE_SIT;
		}
		else if (isOnStair)
			state = SIMON_STATE_IDLE_STAIR;
		else
			state = SIMON_STATE_IDLE;
	}
}

void CSimon::UpdateSubWeapon(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CViewPort* viewport = CViewPort::GetInstance();
	if (GetTickCount() - attackSubStart <= SIMON_ATTACK_SUB_TIME)
	{
		DebugOut(L"ATTACK SUB WEAPON");
	}
	else if (attackSubStart > 0)
	{
		attackSubStart = 0;
		if (state == SIMON_STATE_SIT_ATTACK)
		{
			state = SIMON_STATE_SIT;
		}
		else if (isOnStair)
			state = SIMON_STATE_IDLE_STAIR;
		else
			state = SIMON_STATE_IDLE;
	}
	//Update SubWeapon
	for (auto iter : subWeapon) {
		iter->Update(dt, objects);
	}
	
	for (size_t i = 0; i < subWeapon.size(); i++)
	{
		float swl, swt, swr, swb;
		float vl, vt, vr, vb;
		subWeapon[i]->GetBoundingBox(swl, swt, swr, swb);
		viewport->GetBoundingBox(vl, vt, vr, vb);
		if (!CGame::GetInstance()->IsIntersectAABB({ long(swl), long(swt), long(swr), long(swb) }, { long(vl), long(vt), long(vr), long(vb) }))//Kiểm tra vũ khí ra ngoài camera
		{
			subWeapon.erase(subWeapon.begin() + i);
			i--;
		}
		else if (subWeapon[i]->GetState() == STATE_DESTROYED)
		{
			subWeapon.erase(subWeapon.begin() + i);
			i--;
		}
	}

}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == SIMON_STATE_SIT || state == SIMON_STATE_SIT_ATTACK)
	{
		left = x;
		top = y - SIMON_BBOX_SIT_HEIGHT;
		right = x + SIMON_BBOX_WIDTH;
		bottom = y;
	}
	else 
	{
		left = x;
		top = y - SIMON_BBOX_HEIGHT;
		right = x + SIMON_BBOX_WIDTH;
		bottom = y;
	}
}

void CSimon::StartUntouchable()
{
	SetState(SIMON_STATE_COLLISION_ENEMY);
	untouchable = 1;
	untouchableStart = GetTickCount();
}

void CSimon::StartAttack() {
	if (attackStart > 0)
		return;

	if (attackSubStart > 0) {
		return;
	}

	if (state != SIMON_STATE_JUMP)
		vx = 0;

	//Reset Animation Whip
	ResetAnimation();
	whip->ResetAnimation();
	
	if (state == SIMON_STATE_SIT)
		SetState(SIMON_STATE_SIT_ATTACK);
	else if (isOnStair)
	{
		state = SIMON_STATE_ATTACK_ON_STAIR;
	}
	else
		SetState(SIMON_STATE_ATTACK);
	attackStart = GetTickCount();


}

void CSimon::StartAttackSub() {
	if (attackStart > 0)
		return;
	if (attackSubStart > 0) {
		return;
	}
	if (state != SIMON_STATE_JUMP)
		vx = 0;

	if (subWeaponID == 0)
		return;

	for (auto iter : subWeapon)
	{
		if (iter->state != STATE_DESTROYED)
			return;
	}


	//Reset Animation Whip
	ResetAnimation();
	whip->ResetAnimation();


	if (state == SIMON_STATE_SIT)
		SetState(SIMON_STATE_SIT_ATTACK);
	else if (isOnStair)
	{
		state = SIMON_STATE_ATTACK_ON_STAIR;
	}
	else
		SetState(SIMON_STATE_ATTACK);

	attackSubStart = GetTickCount();
	
	if (state == SIMON_STATE_SIT_ATTACK)
	{
		switch (subWeaponID)
		{
		case ID_DAGGER:
			subWeapon.push_back(new CDagger({ x, y+ WEAPON_SIMON_SIT_ATTACK }, nx));
			break;
		case ID_BOOMERANG:
			if (nx > 0)
				subWeapon.push_back(new CBoomerang({ x + BOOMERANG_SIMON_RANGE_X_RIGHT, y + WEAPON_SIMON_SIT_ATTACK }, nx));
			else
				subWeapon.push_back(new CBoomerang({ x - BOOMERANG_SIMON_RANGE_X_LEFT, y + WEAPON_SIMON_SIT_ATTACK }, nx));
			break;
		default:
			break;
		}
	}
	else
	{
		switch (subWeaponID)
		{
		case ID_DAGGER:
			subWeapon.push_back(new CDagger({ x, y }, nx));
			break;
		case ID_BOOMERANG:
			if (nx > 0)
				subWeapon.push_back(new CBoomerang({ x + BOOMERANG_SIMON_RANGE_X_RIGHT, y  }, nx));
			else
				subWeapon.push_back(new CBoomerang({ x - BOOMERANG_SIMON_RANGE_X_LEFT, y }, nx));
			break;
			break;
		default:
			break;
		}
	}


}

void CSimon::UpdateOnStair()
{
	if (isOnStair)
	{
		float sx, sy;
		collidingStair->GetPosition(sx, sy);
		if ((collidingStair->GetNy() > 0 && (y <= sy - collidingStair->GetStairLong() || y >= sy)) || //Stair Bottom
			(collidingStair->GetNy() < 0 && (y <= sy || y >= sy + collidingStair->GetStairLong()))) //Stair Top
		{
			isOnStair = false;

		}
		else if (vx == 0 && vy == 0 && attackStart != 0 && attackSubStart != 0)
		{
			state = SIMON_STATE_IDLE_STAIR;
		}
	}
}

void CSimon::StartJump()
{
	SetState(SIMON_STATE_JUMP);
	isOnGround = false;
	jumpStart = GetTickCount();
}

void CSimon::StartEatItem()
{
	SetState(SIMON_STATE_EATITEM);
	transformtime = 1;
	eatItemStart = GetTickCount();
	LockUpdate();
}

void CSimon::Reset(int x,int y)
{
	SetPosition(x , y);
	SetSpeed(0, 0);
	DebugOut(L"[DONE] RESET\n");
}

void CSimon::UpgradeWhip()
{
	whip->Upgrade();
	whipSwitchSceneLevel->Upgrade();
	DebugOut(L"[DONE] Upgrade\n");
}

CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}
