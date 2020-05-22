#pragma once
#include "GameObject.h"
#include "Game.h"
#include "ListItem.h"
#include "Item.h"
#include "Heart.h"
#include "Utils.h"
#include "ListItem.h"
#include "WhipUpgrade.h" 
#include "Dagger.h" 
#include "MoneyBag.h"
#include "BoomerangItem.h"
#include "DaggerItem.h"
#include "SmallHeart.h"
#include "define.h"


#define ENEMY_STATE_IDLE	1

class CEnemy : public CGameObject
{
	DWORD timeFire;
public:
	CEnemy();
	~CEnemy();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void TimeFireDestroy();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

