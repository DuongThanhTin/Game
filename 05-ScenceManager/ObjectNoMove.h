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

#define OBJECTS_STATE_NORMAL 0
#define OBJECTS_STATE_DESTROY 1

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

