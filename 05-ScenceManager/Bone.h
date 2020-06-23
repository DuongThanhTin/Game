#pragma once
#include "Enemy.h"

#define BONE_BBOX_WIDTH	7
#define BONE_BBOX_HEIGHT	6

#define BONE_SPEED_X		0.03f
#define BONE_GRAVITY  0.01f//0.14f
#define BONE_FLY_SPEED			0.1f
#define BONE_THROW_SPEED_Y	0.14f
#define TIME_BONE_FLY 350

class CBone : public CEnemy
{
	DWORD timefly;
	int nxSkeleton;
public:
	CBone(D3DXVECTOR2 position, int nx);
	~CBone();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};