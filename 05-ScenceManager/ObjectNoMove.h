#pragma once
#include"GameObject.h"
#include"define.h"
#include "Item.h"
#include "Heart.h"
#include "Utils.h"
#include "ListItem.h"
#include "WhipUpgrade.h" 
#include "DaggerItem.h" 
#include "MoneyBag.h"
#include "BoomerangItem.h"
#include "SmallHeart.h"
#include "AxeItem.h"
#include "MoneyBagWhite.h"
#include "MoneyBagBlue.h"
#include "HolyWaterItem.h"
#include "StopWatchItem.h"


class CObjectNoMove : public CGameObject
{

	DWORD timeFire;

public:
	CObjectNoMove();
	~CObjectNoMove();
	
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
	virtual void TimeFireDestroy();
};

