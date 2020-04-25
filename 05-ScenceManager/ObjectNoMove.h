#pragma once
#include"GameObject.h"
#include"define.h"
#include "Item.h"
#include "Heart.h"
#include "Utils.h"
#include "ListItem.h"
 
#define OBJECTS_STATE_NORMAL 0
#define OBJECTS_STATE_DESTROY 1

class CObjectNoMove : public CGameObject
{

	DWORD timeFire;

public:
	CObjectNoMove();
	~CObjectNoMove();
	vector<LPGAMEOBJECT> objectsItem;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
	virtual void TimeFireDestroy();

};

