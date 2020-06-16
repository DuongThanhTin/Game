#pragma once
#include "define.h"
#include "Enemy.h"
#include "Brick.h"


class CGhost : public CEnemy
{
public:
	CGhost();
	CGhost(D3DXVECTOR2 position, int nextItemID, float limitedLeft, float limitedRight);
	~CGhost();
	/*virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();*/
};

