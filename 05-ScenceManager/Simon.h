#pragma once
#include "GameObject.h"
#include "define.h"
#include "Weapon.h"
#include "Whip.h"
#include "ViewPort.h"
#include "Dagger.h"
#include "Boomerang.h"
#include "Stair.h"
#include "Bridge.h"
#include "AreaActive.h"
#include "Bat.h"
#include "AreaSwitchCam.h"
#include "Axe.h"
#include "HolyWater.h"

#define SIMON_WALKING_SPEED		0.055f 

#define SIMON_JUMP_SPEED_Y		0.18f//0.38f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_JUMP_DEFLECT_SPEED_X 0.05f
#define SIMON_GRAVITY			0.0004f//0.0015f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f
#define SIMON_ON_STAIR_SPEED			0.02f

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
#define SIMON_STATE_GOUP_STAIR		1000
#define SIMON_STATE_GODOWN_STAIR	1100
#define SIMON_STATE_ATTACK_GOUP_STAIR	1200
#define SIMON_STATE_ATTACK_GODOWN_STAIR	1300
#define SIMON_STATE_ATTACK_ON_STAIR 1400
#define SIMON_STATE_COLLISION_ENEMY	1600
#define SIMON_STATE_IDLE_STAIR 1700


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
#define SIMON_ANI_STAIR_GOUP_LEFT	12
#define SIMON_ANI_STAIR_GOUP_RIGHT	13
#define SIMON_ANI_STAIR_GOUP_ATTACK_LEFT	14
#define SIMON_ANI_STAIR_GOUP_ATTACK_RIGHT	15
#define SIMON_ANI_STAIR_GODOWN_LEFT	16
#define SIMON_ANI_STAIR_GODOWN_RIGHT	17
#define SIMON_ANI_STAIR_GODOWN_ATTACK_LEFT	18
#define SIMON_ANI_STAIR_GODOWN_ATTACK_RIGHT	19
#define SIMON_ANI_STAIR_GOUP_IDLE_LEFT	20
#define SIMON_ANI_STAIR_GOUP_IDLE_RIGHT	21
#define SIMON_ANI_STAIR_GODOWN_IDLE_LEFT	22
#define SIMON_ANI_STAIR_GODOWN_IDLE_RIGHT	23
#define SIMON_ANI_DEFLECT_LEFT	24
#define SIMON_ANI_DEFLECT_RIGHT	25


#define SIMON_ANI_DIE				99


#define SIMON_BBOX_WIDTH  15
#define SIMON_BBOX_HEIGHT 30
#define SIMON_BBOX_SIT_HEIGHT 23

#define SIMON_UNTOUCHABLE_TIME 350

#define SIMON_ATTACK_TIME			330
#define SIMON_ATTACK_SUB_TIME		330
#define SIMON_JUMP_TIME				450
#define SIMON_EATITEM_TIME			500



class CSimon : public CGameObject
{
	static CSimon* __instance;
	int untouchable;
	int transformtime;

	bool isOnGround;


	float start_x, start_y;

	DWORD untouchableStart;
	DWORD attackStart;
	DWORD attackSubStart;
	DWORD jumpStart;
	DWORD eatItemStart;
	DWORD aniAttackSubWeaponRender;
	DWORD subWeaponRender;

	LPWHIP whip;
	LPWHIP whipSwitchSceneLevel; //Giữ level whip khi chuyển scene
	LPSTAIR collidingStair; //Xét điểm đầu và điểm cuối của cầu thang

	vector<CWeapon*> subWeapon;
	int subWeaponID;
	int whiplevel;

public:
	bool isOnStair;
	bool isLockUpdate = false;
	bool isSwitchCam;
	CSimon();
	static CSimon* GetInstance();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void RenderBoundingBox(int alpha = 255);

	void SetState(int state);
	void SetSubWeapon(int subWeaponID);
	int GetSubWeapon() { return subWeaponID; }

	void UpdateWhip(DWORD dt, vector<LPGAMEOBJECT>* objects);
	void UpdateSubWeapon(DWORD dt, vector<LPGAMEOBJECT>* objects);
	void UpdateOnStair();

	void StartUntouchable();
	void StartAttack();
	void StartAttackSub();
	void StartJump();
	void StartEatItem();

	bool IsOnStair() { return isOnStair; }
	CStair* GetCollidingStair() { return collidingStair; }

	DWORD GetAttackStart() { return attackStart; }
	DWORD GetJumpStart() { return jumpStart; }
	DWORD GetAttackStartSub() { return attackSubStart; }

	void Reset(int x,int y);
	void UpgradeWhip();
	int GetLockUpdate() { return isLockUpdate; }
	void LockUpdate() { isLockUpdate = true; }
	void UnLockUpdate() { isLockUpdate = false; }
	int GetSwitchCam() { return isSwitchCam; }
	int GetAnimationSubWeapon();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};