#pragma once
#include "define.h"
#include "Enemy.h"

#define BAT_FLYING_SPEED 0.02f

#define BAT_BBOX_WIDTH 16
#define	BAT_BBOX_HEIGHT 16

#define BAT_STATE_SLEEP 100
#define BAT_STATE_FLYING 200
#define BAT_STATE_DIE 300


#define BAT_ANI_WALKING_LEFT 0
#define BAT_ANI_WALKING_RIGHT 1
#define BAT_ANI_DIE 2


class CBat : public CEnemy
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
public:
	CBat();
	CBat(D3DXVECTOR2 position, int nx ,int nextItemID);
	~CBat();
	virtual void SetState(int state);
};