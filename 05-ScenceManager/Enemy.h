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
#include "Simon.h"
#include "ViewPort.h"



class CEnemy : public CGameObject
{
	DWORD timeFire;

public:
	bool isDestroy = false;

	CEnemy();
	~CEnemy();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void TimeFireDestroy();
	virtual void BeDamagedEnemy(int scoreEnemy);
};

