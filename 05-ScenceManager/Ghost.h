#pragma once
#include "define.h"
#include "Enemy.h"
#include "Brick.h"


#define GHOST_WALKING_SPEED 0.03f
//#define SKELETON_GRAVITY 0.002f

#define GHOST_BBOX_WIDTH 16
#define	GHOST_BBOX_HEIGHT 16

#define SKELETON_STATE_IDLE 100
#define SKELETON_STATE_JUMP 200
#define SKELETON_STATE_WALKING 300

#define GHOST_ANI_WALKING_LEFT 0
#define GHOST_ANI_WALKING_RIGHT 1

class CGhost : public CEnemy
{
public:
	CGhost();
	CGhost(D3DXVECTOR2 position, int nextItemID,int nxGhost);
	~CGhost();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
};

