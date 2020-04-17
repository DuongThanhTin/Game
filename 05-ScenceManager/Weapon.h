#pragma once
#include "GameObject.h"
#include "Game.h"
#include "define.h"
#include "Heart.h"

class CWeapon : public CGameObject
{

public:
	vector<LPGAMEOBJECT> objectsItem;
	CWeapon();
	~CWeapon();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CWeapon *LPWEAPON;
 
