#pragma once
#include "define.h"
#include "Enemy.h"
#include "Brick.h"

#define FLEAMAN_WALKING_SPEED 0.05f
#define FLEAMAN_GRAVITY 0.002f

#define FLEAMAN_BBOX_WIDTH 16
#define	FLEAMAN_BBOX_HEIGHT 16

#define FLEAMAN_STATE_IDLE 100
#define FLEAMAN_STATE_JUMP 200
#define FLEAMAN_STATE_WALKING 300

#define FLEAMAN_ANI_WALKING_LEFT 0
#define FLEAMAN_ANI_WALKING_RIGHT 1

class CFleaman : public CEnemy
{
	float limitedRight, limitedLeft;
	bool isOnGroundEnemy = false;
public:
	CFleaman();
	CFleaman(D3DXVECTOR2 position, int nextItemID, float limitedLeft, float limitedRight);
	~CFleaman();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
};



