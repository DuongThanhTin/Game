#pragma once
#include "define.h"
#include "Enemy.h"
#include "Simon.h"

#define BAT_FLYING_SPEED 0.001f

#define BAT_BBOX_WIDTH 16
#define	BAT_BBOX_HEIGHT 16

#define BAT_STATE_SLEEP 100
#define BAT_STATE_FLYING 200


#define BAT_ANI_IDLE_ 0
#define BAT_ANI_FLYING_RIGHT 1


class CBat : public CEnemy
{
	float falldown;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
public:
	CBat();
	CBat(D3DXVECTOR2 position, int nx, int nextItemID, float falldown);
	~CBat();
	virtual void SetState(int state);
};