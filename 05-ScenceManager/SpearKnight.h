#pragma once
#include "define.h"
#include "Enemy.h"

#define SPEARKNIGHT_WALKING_SPEED 0.02f
#define SPEARKNIGHT_GRAVITY 0.002f

#define SPEARKNIGHT_BBOX_WIDTH 16
#define	SPEARKNIGHT_BBOX_HEIGHT 30

#define SPEARKNIGHT_STATE_WALKING 100
#define SPEARKNIGHT_STATE_DIE 200

#define SPEARKNIGHT_ANI_WALKING_LEFT 0
#define SPEARKNIGHT_ANI_WALKING_RIGHT 1
#define SPEARKNIGHT_ANI_DIE 2

class CSpearKnight : public CEnemy
{

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
public:
	CSpearKnight();
	CSpearKnight(D3DXVECTOR2 position, int nextItemID);
	~CSpearKnight();
	virtual void SetState(int state);
};



