#pragma once
#include "define.h"
#include "Enemy.h"
#include "Brick.h"

#define SPEARKNIGHT_WALKING_SPEED 0.03f
#define SPEARKNIGHT_GRAVITY 0.002f

#define SPEARKNIGHT_BBOX_WIDTH 16
#define	SPEARKNIGHT_BBOX_HEIGHT 30

#define SPEARKNIGHT_STATE_WALKING 100

#define SPEARKNIGHT_ANI_WALKING_LEFT 0
#define SPEARKNIGHT_ANI_WALKING_RIGHT 1

class CSpearKnight : public CEnemy
{
	float limitedRight, limitedLeft;

public:
	CSpearKnight();
	CSpearKnight(D3DXVECTOR2 position, int nextItemID, float limitedLeft, float limitedRight);
	~CSpearKnight();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
};



