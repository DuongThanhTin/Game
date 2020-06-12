#pragma once
#include "GameObject.h"
#include "Utils.h"

#define ROCK_GRAVITY 0.0003f
#define ANI_ROCK 796
#define NUMBER_ROCK 4

#define ROCK_VX_1	0.04f
#define ROCK_VX_2	0.03f
#define ROCK_VX_3	-0.035f
#define ROCK_VX_4	-0.045f

#define ROCK_VY_1	-0.095f
#define ROCK_VY_2	-0.085f
#define ROCK_VY_3	-0.055f
#define ROCK_VY_4	-0.025f


class CRock : public CGameObject
{
	float *rock_x, *rock_y, *rock_vx, *rock_vy;
public:
	int number;
	CRock(D3DXVECTOR2 position, int hidebrick_id);
	~CRock();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};