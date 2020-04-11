#pragma once
#include "GameObject.h"

#define ITEM_DISAPPEAR_TIME 5000

class CItem : public CGameObject
{
	DWORD timeDisappear;
public:
	CItem();
	~CItem();

	void StartTimeDisappear();

	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

