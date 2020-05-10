#pragma once
#include "GameObject.h"
#include "define.h"
#include "Weapon.h"
#include "Whip.h"
#include "ViewPort.h"
#include "Dagger.h"

#define SIMON_WALKING_SPEED		0.055f 

#define SIMON_JUMP_SPEED_Y		0.45f
#define SIMON_JUMP_DEFLECT_SPEED 0.1f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f


#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_ATTACK			500
#define SIMON_STATE_SIT				600
#define SIMON_STATE_SIT_ATTACK		700
#define SIMON_STATE_ATTACK_SUBWEAPON	800
#define SIMON_STATE_EATITEM		    900

#define SIMON_ANI_IDLE_RIGHT		0
#define SIMON_ANI_IDLE_LEFT			1
#define SIMON_ANI_WALKING_RIGHT		2
#define SIMON_ANI_WALKING_LEFT		3
#define SIMON_ANI_ATTACK_RIGHT		4
#define SIMON_ANI_ATTACK_LEFT		5
#define SIMON_ANI_SIT_RIGHT			6
#define SIMON_ANI_SIT_LEFT			7
#define SIMON_ANI_SIT_ATTACK_RIGHT	8
#define SIMON_ANI_SIT_ATTACK_LEFT	9
#define SIMON_ANI_EATITEM_RIGHT		10
#define SIMON_ANI_EATITEM_LEFT		11

#define SIMON_ANI_DIE				99


#define SIMON_BBOX_WIDTH  15
#define SIMON_BBOX_HEIGHT 30
#define SIMON_BBOX_SIT_HEIGHT 23

#define SIMON_UNTOUCHABLE_TIME 3000

#define SIMON_ATTACK_TIME			350
#define SIMON_ATTACK_SUB_TIME		350
#define SIMON_JUMP_TIME				450
#define SIMON_EATITEM_TIME			500


class CSimon : public CGameObject
{
	
	int untouchable;
	int transformtime;
	bool isOnGround;

	float start_x, start_y;

	DWORD untouchableStart;
	DWORD attackStart;
	DWORD attackStartSub;
	DWORD jumpStart;
	DWORD eatitemStart;

	LPWHIP whip;
	vector<CWeapon*> subWeapon;
	int subWeaponID;

public:
	CSimon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void RenderBoundingBox(int alpha = 255);
	int GetSubWeapon() { return subWeaponID; }
	bool isOnGroundFloor() { return isOnGround; };
	void SetState(int state);
	void SetSubWeapon(int subWeaponID);
	void UpdateWhip(DWORD dt, vector<LPGAMEOBJECT>* objects);
	void UpdateSubWeapon(DWORD dt, vector<LPGAMEOBJECT>* objects);

	void StartUntouchable();
	void StartAttack();
	void StartAttackSub();
	void StartJump();
	void StartEatItem();

	DWORD GetAttackStart() { return attackStart; }
	DWORD GetJumpStart() { return jumpStart; }
	DWORD GetAttackStartSub() { return attackStartSub; }

	void Reset();
	void UpgradeWhip();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};