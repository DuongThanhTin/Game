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
	aniAttackSubWeaponRender = 0;
	invisibleStart = 0;
	subWeaponRender = 0;
	subWeaponID = 0;
	eatItemStart = 0;
	score = 0; //Score
	scoreSubWeapon = 5; //scoreSubWeapon
	numLife = 3; //Num Life
	health = 16; //Health Simon
	isOnGround = false;
	isOnStair = false;
	isLockUpdate = false;
	isSwitchCam = false;
	brickCollidSimon = NULL;
	collidingStair = NULL;
	//Whip
	whipSwitchSceneLevel = CWhip::GetInstance();
	whip = new CWhip();
	whip->SetLevel(whipSwitchSceneLevel->GetLevel());
	//Hud
	hudSwitchScene = CHud::GetInstance(); //Hud này để lưu các giá trị của hud chính sau đó set lại các giả trị cho Hud chính khi load lại map
	hud = new CHud();
	hud->SetScoreHub(hudSwitchScene->GetScoreHud()); // SET SCORE ON HUD
	hud->SetTimeHud(hudSwitchScene->GetTimeHud()); //SET TIME ON HUD
	hud->SetScoreSubWeaponHub(hudSwitchScene->GetScoreSubWeaponHud()); //SET SCORESUBWEAPON ON HUD
	hud->SetNumLifeHub(hudSwitchScene->GetNumLifeHud()); // SET NUM LIFE ON HUD
	hud->SetHealthSimon(hudSwitchScene->GetHealthSimon()); //SET HEALTH SIMON ON HUD
	//hud->SetHealthBoss(hudSwitchScene->GetHealthBoss()); //SET HEALTH BOSS ON HUD

	if (hudSwitchScene->GetIdSubWeapon() != 0) //SET SUBWEAPON WHEN LOAD NEW SCENE
	{
		switch (hudSwitchScene->GetIdSubWeapon())
		{
		case ID_BOOMERANGITEM:
			SetSubWeapon(ID_BOOMERANG); //SIMON ATTACK SUBWEAPON
			hud->SetItem(ID_BOOMERANGITEM); //SUBWEAPON ON HUD
			break;
		case ID_AXEITEM:
			SetSubWeapon(ID_AXE);
			hud->SetItem(ID_AXEITEM);
			break;
		case ID_DAGGERITEM:
			SetSubWeapon(ID_DAGGER);
			hud->SetItem(ID_DAGGERITEM);
			break;
		case ID_HOLYWATERITEM:
			SetSubWeapon(ID_HOLYWATER);
			hud->SetItem(ID_HOLYWATERITEM);
			break;
		case ID_STOPWATCHITEM:
			SetSubWeapon(ID_STOPWATCH);
			hud->SetItem(ID_STOPWATCHITEM);
			break;
		default:
			break;
		}
	}
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
		if (jumpStart > 0)
		{
			vy += SIMON_GRAVITY*dt;
			isFalling = false;
		}
		else
		{
			if (vy > 0)
			{
				isFalling = true;
				vy = SIMON_FALLING_SPEED;
				
			}
			else
			{
				vy += SIMON_GRAVITY*dt;
				isFalling = false;
			}
		}
	}


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	//Collide Object
	//Collision with wall
	vector<LPGAMEOBJECT> wallObjects;
	for (int i = 0;i < coObjects->size();i++) {
		if (coObjects->at(i)->GetID() == ID_GROUND ||
			coObjects->at(i)->GetID() == ID_BRIDGE ||
			coObjects->at(i)->GetID() == ID_HIDEBRICK )
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
			listItem->ListItem[i]->GetID() == ID_MONEYBAGBLUE ||
			listItem->ListItem[i]->GetID() == ID_HOLYWATERITEM||
			listItem->ListItem[i]->GetID() == ID_STOPWATCHITEM)
			itemObjects.push_back(listItem->ListItem[i]);
	}

	//Collision with Enemy
	vector<LPGAMEOBJECT> enemyObjects;
	for (int i = 0;i < coObjects->size();i++) {
		if (coObjects->at(i)->GetID() == ID_SPEARKNIGHT ||
			coObjects->at(i)->GetID() == ID_BAT||
			coObjects->at(i)->GetID() == ID_ZOMBIE ||
			coObjects->at(i)->GetID() == ID_FLEAMAN || 
			coObjects->at(i)->GetID() == ID_SKELETON || 
			coObjects->at(i)->GetID() == ID_GHOST ||
			coObjects->at(i)->GetID() == ID_BONE ||
			coObjects->at(i)->GetID() == ID_BOSS ||
			coObjects->at(i)->GetID() == ID_RAVEN)
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
						else if (iter2->GetID() == ID_BOSS)
						{
							iter2->isActive = true;
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
		
		//Crown
		for (size_t i = 0; i < Objects.size(); i++)
		{
			float sl, st, sr, sb;		// simon object bbox
			float ol, ot, or , ob;		// object bbox
			GetBoundingBox(sl, st, sr, sb);
			Objects[i]->GetBoundingBox(ol, ot, or , ob);
			if (Objects[i]->GetID() == ID_CROWN)
			{
				if (CGame::GetInstance()->IsIntersectAABB({ long(sl),long(st), long(sr), long(sb) }, { long(ol), long(ot), long(or ), long(ob) })) {
					IncreaseScore(SCORE_CROWN);
					SetScoreItem(SCORE_CROWN);
					AppearScore(SCORE_CROWN, (ol + or ) / 2, (ot + ob) / 2);
					Objects[i]->SetState(STATE_DESTROYED);
					Objects.erase(Objects.begin() + i);
					i--;
				}
				
				
				if (sl > ol + DISTANCE_CROWN_APPEAR)
				{
					Objects[i]->isActive = true;
				}
			
			}
		}
			

		//Collision SubWeapon
		for (auto iter : subWeapon)
		{
			float sl, st, sr, sb;		// simon object bbox
			float wl, wt, wr, wb;		// object bbox
			GetBoundingBox(sl, st, sr, sb);
			iter->GetBoundingBox(wl, wt, wr, wb);
			if (CGame::GetInstance()->IsIntersectAABB({ long(sl),long(st), long(sr), long(sb) }, { long(wl), long(wt), long(wr), long(wb) })) {
				switch (iter->GetID()) {
				case ID_BOOMERANG:
					iter->SetState(STATE_DESTROYED);
					break;
				case ID_AXE:
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
					IncreaseScoreSubWeapon(SCORESUB_LARGEHEART);
					DebugOut(L"Collsion LargeHeart %d\n", hudSwitchScene->GetScoreSubWeaponHud());
					break;
				case ID_SMALLHEART:
					IncreaseScoreSubWeapon(SCORESUB_SMALLHEART);
					DebugOut(L"Collsion SmallHeart %d\n", hudSwitchScene->GetScoreSubWeaponHud());
					break;
				case ID_WHIPUPGRADE:
					StartEatItem();
					UpgradeWhip();
					DebugOut(L"Collsion Whip Upgrade\n");
					break;
				case ID_DAGGERITEM:
					StartEatItem();
					SetSubWeapon(ID_DAGGER);
					SetItemWeaponHud(ID_DAGGERITEM);
					DebugOut(L"Collsion Dagger\n");
					break;
				case ID_BOOMERANGITEM:
					StartEatItem();
					SetSubWeapon(ID_BOOMERANG);
					SetItemWeaponHud(ID_BOOMERANGITEM);
					DebugOut(L"Collsion BOOMERANGITEM\n");
					break;
				case ID_AXEITEM:
					SetSubWeapon(ID_AXE);
					SetItemWeaponHud(ID_AXEITEM);
					DebugOut(L"Collsion AXE\n");
					break;
				case ID_HOLYWATERITEM:
					SetSubWeapon(ID_HOLYWATER);
					SetItemWeaponHud(ID_HOLYWATERITEM);
					DebugOut(L"Collsion ID_HOLYWATERITEM\n");
					break;
				case ID_STOPWATCHITEM:
					SetSubWeapon(ID_STOPWATCH);
					SetItemWeaponHud(ID_STOPWATCHITEM);
					DebugOut(L"Collsion ID_STOPWATCH\n");
					break;
				case ID_MONEYBAG:
					IncreaseScore(SCORE_MONEYBAGRED);
					AppearScore(SCORE_MONEYBAGRED, (ol + or ) / 2, (ot + ob) / 2);
					SetScoreItem(SCORE_MONEYBAGRED);
					DebugOut(L"Collsion Moneybag\n");
					break;
				case ID_MONEYBAGWHITE:
					IncreaseScore(SCORE_MONEYBAGWHITE);
					AppearScore(SCORE_MONEYBAGWHITE, (ol + or ) / 2, (ot + ob) / 2);
					SetScoreItem(SCORE_MONEYBAGWHITE);
					DebugOut(L"Collsion ID_MONEYBAGWHITE\n");
					break;
				case ID_MONEYBAGBLUE:
					IncreaseScore(SCORE_MONEYBAGBLUE);
					SetScoreItem(SCORE_MONEYBAGBLUE);
					AppearScore(SCORE_MONEYBAGBLUE, (ol + or ) / 2, (ot + ob) / 2 );
					DebugOut(L"Collsion ID_MONEYBAGBLUE\n");
					break;

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
					if (invisibleStart == 0)
					{
						if(iter->GetID() == ID_BAT)
						{			
							IncreaseScore(SCORE_BAT);
							BeHurted();
							iter->TimeFireDestroy();
						}
						else if (iter->GetID() == ID_ZOMBIE)
						{
							IncreaseScore(SCORE_BAT);
							BeHurted();
							iter->TimeFireDestroy();
						}
						else
						{
							BeHurted();
						}
					}
				}
			}
		}
	}

	//Active ENemy
	for (auto iter : enemyObjects) {
		if (iter->GetID() == ID_BOSS)
		{
			hud->SetHealthBoss(iter->healthEnemy); // UPDATE HEALTH ON HUD
		}

		float sl, st, sr, sb;		// simon object bbox
		float ol, ot, or , ob;		// enemy bbox
		GetBoundingBox(sl, st, sr, sb);

		if (iter->GetID() == ID_FLEAMAN)
		{
			iter->GetBoundingBox(ol, ot, or , ob);
			if (sl - or <= 100)
			{
				iter->isActive = true;
			}
		}

		else if (iter->GetID() == ID_GHOST)
		{
			iter->GetBoundingBox(ol, ot, or , ob);
			float x, y;
			GetPosition(x, y);
			if (x < 600)
			{
				iter->isActive = true;
			}
		}

		else if (iter->GetID() == ID_RAVEN)
		{
			iter->GetBoundingBox(ol, ot, or , ob);
			if (ol - sr <= 60 && st - ot <= 120)
			{
				float x, y;
				GetPosition(x, y);
				iter->isActive = true;
			}
		}

		else if (iter->GetID() == ID_SKELETON)
		{
			iter->GetBoundingBox(ol, ot, or , ob);
			if (sl - or <= 60 && st - ot <= 120) 
			{
				float x, y;
				GetPosition(x, y);
				iter->isActive = true;
			}
			else if (ol - sr <= 60 && ob - sb <= 30)
			{
				iter->isActive = true;
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

		//if (nx != 0) vx = 0;

		if (ny < 0) {
			vy = 0;
			if (!isOnGround)
			{
				isOnGround = true;
				
			}
		}

		//On Bridge
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBridge*>(e->obj))
			{
				CBridge* bridge = dynamic_cast<CBridge *>(e->obj);
				if (e->ny != 0)
				{
					x += bridge->vx * 2 * dt;

				}
			}
			else if (dynamic_cast<CHideBrick*>(e->obj))
			{
				if (e->ny != 0 || e->nx != 0)
				{
					vx = 0;
				}
			}
			
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				if (e->ny<0 && e->nx !=0) //trên xuống
				{
					vy = 0;
				}
				else if (e->ny>0) //dưới lên
				{
					y += dy;
					x += 0;
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
		isFalling = false;
	}

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchableStart > SIMON_UNTOUCHABLE_TIME)
	{
		untouchableStart = 0;
	}
	else if (untouchable > 0)
	{
		attackStart = 0;
		attackSubStart = 0;
	}

	if (GetTickCount() - invisibleStart > SIMON_INVISIBLE_TIME && invisibleStart > 0 && untouchableStart == 0)
	{
		invisibleStart = 0;
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
		attackStart = 0;
		attackSubStart = 0;
	}


	// update attack state and whip
	UpdateWhip(dt, coObjects);

	//Update attack subweapon
	UpdateSubWeapon(dt, coObjects);

	//Update on Stair
	UpdateOnStair();
	
	//Update on Hud
	UpdateOnHud(dt);
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
	else if (state == SIMON_STATE_WALKING_RIGHT) {
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

	else if (state == SIMON_STATE_COLLISION_ENEMY)
	{
		if (nx > 0)
			ani = SIMON_ANI_DEFLECT_RIGHT;
		else
			ani = SIMON_ANI_DEFLECT_LEFT;
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

	int alpha= 255;
	if (invisibleStart > 0)
	{
		alpha = 150;
	}

	if (untouchableStart > 0)
	{
		alpha = rand() % 255;
	}
	//DebugOut(L"ALPHA %d \n", alpha);
	animation_set->at(ani)->Render(x, y, alpha);
	
	RenderBoundingBox();
	if (attackStart)
	{
		whip->Render();
	}
	
	for (auto iter : subWeapon)
		iter->Render();
	/*if (isattacksub)
	{
		for (auto iter : subWeapon)
			iter->Render();
	}*/


	hud->Draw({ 0, 40 });

	DrawAppearScore();
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
		attackStart = 0;
		break;
	case SIMON_STATE_COLLISION_ENEMY:
		attackStart = 0;
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

void CSimon::BeHurted()
{
	if (untouchableStart > 0)
		return;

	untouchableStart = GetTickCount();
	invisibleStart = GetTickCount();
	DecreaseHealth();
	hudSwitchScene->DecreaseHealth();
	if (!isOnStair)
	{
		SetSpeed(-nx * SIMON_DAMAGED_DEFLECT_SPEED_X, -SIMON_DAMAGED_DEFLECT_SPEED_Y);
		isOnGround = false;
		state = SIMON_STATE_COLLISION_ENEMY;
	}
}

void CSimon::SetSubWeapon(int subWeaponID)
{
	this->subWeaponID = subWeaponID;
	DebugOut(L"SUB WEAPON : %d\n", subWeaponID);
	switch (subWeaponID)
	{
	case ID_BOOMERANG:
		hud->SetItem(ID_BOOMERANGITEM);
		hudSwitchScene->SetItem(ID_BOOMERANGITEM);
		break;
	case ID_DAGGER:
		hud->SetItem(ID_DAGGERITEM);
		hudSwitchScene->SetItem(ID_DAGGERITEM);
		break;
	case ID_AXE:
		hud->SetItem(ID_AXEITEM);
		hudSwitchScene->SetItem(ID_AXEITEM);
		break;
	case ID_HOLYWATER:
		hud->SetItem(ID_HOLYWATERITEM);
		hudSwitchScene->SetItem(ID_HOLYWATERITEM);
		break;
	case ID_STOPWATCH:
		hud->SetItem(ID_STOPWATCHITEM);
		hudSwitchScene->SetItem(ID_STOPWATCHITEM);
		break;
	default:
		break;
	}
}

void CSimon::UpdateOnHud(DWORD dt)
{
	//Hud
	SetScore(hudSwitchScene->GetScoreHud());
	SetNumLife(hudSwitchScene->GetNumLifeHud());
	hud->SetNumLifeHub(GetNumLife());
	hud->SetScoreHub(hudSwitchScene->GetScoreHud()); // UPDATE SCORE ON HUD
	hud->SetScoreSubWeaponHub(hudSwitchScene->GetScoreSubWeaponHud()); // UPDATE SCORE SUBWEAPON ON HUD
	
	if (GetState() == SIMON_STATE_DIE)
	{
		SetHealthSimon(NUM_HEALTH);
		hud->SetHealthSimon(NUM_HEALTH);
		hudSwitchScene->SetHealthSimon(NUM_HEALTH);
		//Boss
		hud->SetHealthBoss(NUM_HEALTH);
	}
	else
	{
		hud->SetHealthSimon(hudSwitchScene->GetHealthSimon()); // UPDATE HEALTH ON HUD
		
	}
	hud->SetNumLifeHub(hudSwitchScene->GetNumLifeHud()); // UPDATE NUM LIFE ON HUD 
	hud->Update(dt);
}

void CSimon::UpdateWhip(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	if (GetTickCount() - attackStart <= SIMON_ATTACK_TIME && !isAttackJump)
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
				whip_X = x + 7;
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
		ResetAnimation();
		whip->ResetAnimation();
		if (state == SIMON_STATE_SIT_ATTACK)
		{
			state = SIMON_STATE_SIT;
		}
		else if (isOnStair)
		{
			state = SIMON_STATE_IDLE_STAIR;
		}
		else
			state = SIMON_STATE_IDLE;
	}

}

void CSimon::UpdateSubWeapon(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CViewPort* viewport = CViewPort::GetInstance();
	if (GetTickCount() - attackSubStart <= SIMON_ATTACK_SUB_TIME)
	{
		;
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

	
	if (isAttackStopWatch)
	{
		for (auto iter : *objects)
		{
			switch (iter->GetID())
			{
			case ID_SPEARKNIGHT:
			case ID_SKELETON:
			case ID_FLEAMAN:
			case ID_RAVEN:
			case ID_BONE:
			case ID_GHOST:
			case ID_ZOMBIE:
			case ID_BOSS:
			case ID_BAT:
				iter->StartStopWatch();
				break;
			default:
				break;
			}
		}

		if (timeStopWatch == 0)
		{
			isAttackStopWatch = false;
		}
		
	}

	for (size_t i = 0; i < subWeapon.size(); i++)
	{
		float swl, swt, swr, swb;
		float vl, vt, vr, vb;
		subWeapon[i]->GetBoundingBox(swl, swt, swr, swb);
		viewport->GetBoundingBox(vl, vt, vr, vb);
		if (!CGame::GetInstance()->IsIntersectAABB({ long(swl), long(swt), long(swr), long(swb) }, { long(vl), long(vt), long(vr), long(vb) }))//Kiểm tra vũ khí ra ngoài camera
		{
			if (subWeapon[i]->GetID() == ID_AXE ||
				subWeapon[i]->GetID() == ID_HOLYWATER)
			{
				if (swt > vb || swr > vr)
				{
					isattacksub = false;
					subWeapon.erase(subWeapon.begin() + i);
					i--;
				}
			}
			else
			{
				isattacksub = false;
				subWeapon.erase(subWeapon.begin() + i);
				i--;
			}
		}
		else if (subWeapon[i]->GetState() == STATE_DESTROYED)
		{
			isattacksub = false;
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

	//if (isFalling)
		//return;

	//Reset Animation Whip
	//ResetAnimation();
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

	if (isAttackStopWatch)
		return;



	for (auto iter : subWeapon)
	{
		if (iter->state != STATE_DESTROYED)
			return;
	}


	//Reset Animation Whip
	//ResetAnimation();
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
			subWeapon.push_back(new CDagger({ x, y + WEAPON_SIMON_SIT_ATTACK }, nx));
			break;
		case ID_BOOMERANG:
			if (nx > 0)
				subWeapon.push_back(new CBoomerang({ x + BOOMERANG_SIMON_RANGE_X_RIGHT, y + WEAPON_SIMON_SIT_ATTACK }, nx));
			else
				subWeapon.push_back(new CBoomerang({ x - BOOMERANG_SIMON_RANGE_X_LEFT, y + WEAPON_SIMON_SIT_ATTACK }, nx));
			break;
		case ID_AXE:
			if (nx > 0)
				subWeapon.push_back(new CAxe({ x + BOOMERANG_SIMON_RANGE_X_RIGHT, y + WEAPON_SIMON_SIT_ATTACK }, nx));
			else
				subWeapon.push_back(new CAxe({ x - BOOMERANG_SIMON_RANGE_X_LEFT, y + WEAPON_SIMON_SIT_ATTACK }, nx));
			break;
		case ID_HOLYWATER:
			if (nx > 0)
				subWeapon.push_back(new CHolyWater({ x + BOOMERANG_SIMON_RANGE_X_RIGHT, y + WEAPON_SIMON_SIT_ATTACK }, nx));
			else
				subWeapon.push_back(new CHolyWater({ x - BOOMERANG_SIMON_RANGE_X_LEFT, y + WEAPON_SIMON_SIT_ATTACK }, nx));
			break;
		case ID_STOPWATCH:
			isAttackStopWatch = true;
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
				subWeapon.push_back(new CBoomerang({ x + BOOMERANG_SIMON_RANGE_X_RIGHT, y }, nx));
			else
				subWeapon.push_back(new CBoomerang({ x - BOOMERANG_SIMON_RANGE_X_LEFT, y }, nx));
			break;
		case ID_AXE:
			if (nx > 0)
				subWeapon.push_back(new CAxe({ x + BOOMERANG_SIMON_RANGE_X_RIGHT, y }, nx));
			else
				subWeapon.push_back(new CAxe({ x - BOOMERANG_SIMON_RANGE_X_LEFT, y }, nx));
			break;
		case ID_HOLYWATER:
			if (nx > 0)
				subWeapon.push_back(new CHolyWater({ x + BOOMERANG_SIMON_RANGE_X_RIGHT, y }, nx));
			else
				subWeapon.push_back(new CHolyWater({ x - BOOMERANG_SIMON_RANGE_X_LEFT, y }, nx));
			break;
		case ID_STOPWATCH:
			isAttackStopWatch = true;
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

void CSimon::Reset(int x, int y)
{
	SetPosition(x, y);
	SetSpeed(0, 0);
	DebugOut(L"[DONE] RESET\n");
}

void CSimon::UpgradeWhip()
{
	whip->Upgrade();
	whipSwitchSceneLevel->Upgrade();
	DebugOut(L"[DONE] Upgrade\n");
}

int CSimon::GetAnimationSubWeapon()
{
	int anisub = 0;
	if (state == SIMON_STATE_ATTACK) {
		if (nx > 0)
			anisub = SIMON_ANI_ATTACK_RIGHT;
		else
			anisub = SIMON_ANI_ATTACK_LEFT;
	}
	else if (state == SIMON_STATE_SIT) {
		if (nx > 0)
			anisub = SIMON_ANI_SIT_RIGHT;
		else
			anisub = SIMON_ANI_SIT_LEFT;
	}
	else if (state == SIMON_STATE_SIT_ATTACK) {
		if (nx > 0)
			anisub = SIMON_ANI_SIT_ATTACK_RIGHT;
		else
			anisub = SIMON_ANI_SIT_ATTACK_LEFT;
	}
	else if (state == SIMON_STATE_ATTACK_ON_STAIR) { //Attack On Stair
		if (nx > 0)
		{
			if (ny > 0)
				anisub = SIMON_ANI_STAIR_GOUP_ATTACK_RIGHT;
			else
				anisub = SIMON_ANI_STAIR_GODOWN_ATTACK_RIGHT;
		}
		else
		{
			if (ny > 0)
				anisub = SIMON_ANI_STAIR_GOUP_ATTACK_LEFT;
			else
				anisub = SIMON_ANI_STAIR_GODOWN_ATTACK_LEFT;;
		}
	}

	return anisub;
}

void CSimon::SetItemWeaponHud(int itemID)
{
	hud->SetItem(itemID);
	hudSwitchScene->SetItem(itemID);
}

void CSimon::IncreaseScore(int scoreEnemy)
{
	hudSwitchScene->IncreaseScoreHud(scoreEnemy);
}

void CSimon::IncreaseScoreSubWeapon(int score)
{
	hudSwitchScene->IncreaseScoreSubWeapon(score);
}

void CSimon::DrawAppearScore()
{
	if (scoreItems.size() > 0)
	{

		if (timeAppearScore == 0)
		{
			timeAppearScore = GetTickCount();
		}

		else if (GetTickCount() - timeAppearScore > TIME_APPAEAR_SCORE)
		{

			timeAppearScore = 0;
			scoreItems.clear();
		}

		for (auto iter : scoreItems)
		{
			scoreItem_1->Render(iter[0], iter[1]);
			scoreItem_2->Render(iter[0] + 4, iter[1]);
			switch (GetScoreItem())
			{
			case SCORE_MONEYBAGBLUE:
				scoreItem_1->Render(iter[0], iter[1]);
				scoreItem_2->Render(iter[0] + 4, iter[1]);
				break;
			case SCORE_MONEYBAGRED:
				scoreItem_1->Render(iter[0], iter[1]);
				scoreItem_2->Render(iter[0] + 8, iter[1]);
				break;
			case SCORE_MONEYBAGWHITE:
				scoreItem_1->Render(iter[0], iter[1]);
				scoreItem_2->Render(iter[0] + 4, iter[1]);
				break;
			case SCORE_CROWN:
				scoreItem_1->Render(iter[0], iter[1]);
				scoreItem_2->Render(iter[0] + 8, iter[1]);
				break;
			default:
				break;
			}
		}
	}
}

void CSimon::AppearScore(int appearscore, float x, float y)
{
	scoreItems.push_back({x+5,y });
	switch (appearscore)
	{
	case SCORE_MONEYBAGBLUE:
		scoreItem_1 = CAnimations::GetInstance()->Get(ID_ANI_SCORE_40);
		scoreItem_2 = CAnimations::GetInstance()->Get(ID_ANI_SCORE_00);
		break;
	case SCORE_MONEYBAGRED:
		scoreItem_1 = CAnimations::GetInstance()->Get(ID_ANI_SCORE_10);
		scoreItem_2 = CAnimations::GetInstance()->Get(ID_ANI_SCORE_00);
		break;
	case SCORE_MONEYBAGWHITE:
		scoreItem_1 = CAnimations::GetInstance()->Get(ID_ANI_SCORE_70);
		scoreItem_2 = CAnimations::GetInstance()->Get(ID_ANI_SCORE_00);
		break;
	case SCORE_CROWN:
		scoreItem_1 = CAnimations::GetInstance()->Get(ID_ANI_SCORE_20);
		scoreItem_2 = CAnimations::GetInstance()->Get(ID_ANI_SCORE_00);
		break;
	default:
		break;
	}
}

void CSimon::ResetGame(int scene_id, float view_x, float view_y)
{
	CViewPort * viewport = CViewPort::GetInstance();
	CGame *game = CGame::GetInstance();
	game->SwitchScene(scene_id);
	viewport->SetPosition({ view_x,view_y });
}

CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}