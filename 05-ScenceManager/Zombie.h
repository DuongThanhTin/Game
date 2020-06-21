#pragma once
#include "Enemy.h"
#include "define.h"

#define ZOMBIE_WALKING_SPEED 0.05f;

#define ZOMBIE_BBOX_WIDTH 16
#define	ZOMBIE_BBOX_HEIGHT 26

#define ZOMBIE_STATE_WALKING 100
#define ZOMBIE_STATE_DIE 200

#define ZOMBIE_GRAVITY			0.002f
#define ZOMBIE_ANI_WALKING_LEFT 0
#define ZOMBIE_ANI_WALKING_RIGHT 1
#define ZOMBIE_ANI_DIE 2


class CZombie : public CEnemy
{
	float limitedRight, limitedLeft;

public:
	CZombie();
	CZombie(D3DXVECTOR2 position, int nextItemID, float limitedLeft, float limitedRight);
	~CZombie();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
};

