#pragma once
#include "GameObject.h"
#include "Game.h"
#include "define.h"
#include "Heart.h"
#include "ListItem.h"
#include "WhipUpgrade.h" 
#include "Brick.h"

#define WEAPON_STATE_NORMAL 0

class CWeapon : public CGameObject
{
	DWORD timeAppearItem;
public:
	vector<LPGAMEOBJECT> objectsItem;
	CWeapon();
	~CWeapon();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	void DestroyObject();
};

typedef CWeapon *LPWEAPON;
 
