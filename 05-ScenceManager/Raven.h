#pragma once
#include "define.h"
#include "Enemy.h"
#include "Brick.h"

#define RAVEN_FLYING_SPEED_X 0.075f

#define RAVEN_BBOX_WIDTH 16
#define	RAVEN_BBOX_HEIGHT 16

#define RAVEN_STATE_SLEEP 100
#define RAVEN_STATE_FLYING 200

#define RAVEN_FLYING_FALLDOWN 0.075

#define RAVEN_ANI_IDLE_ 0
#define RAVEN_ANI_FLYING_RIGHT 1
#define RAVEN_ANI_FLYING_LEFT 2


class CRaven : public CEnemy
{
	int falldown;
public:
	CRaven();
	CRaven(D3DXVECTOR2 position,int nextItemID, float falldown, int area_id);
	~CRaven();
	//virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
};