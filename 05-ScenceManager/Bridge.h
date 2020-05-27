#pragma once
#include "Brick.h"
#include "define.h"
#include "GameObject.h"
#include "Simon.h"

#define BRIDGE_BBOX_WIDTH  31
#define BRIDGE_BBOX_HEIGHT 7
#define BRIDGE_STATE_MOVE 100
#define BRIDGE_ANI_MOVE 0
#define BRIDGE_SPEED 0.035f

class CBridge : public CGameObject
{
	float limitedLeft;
	float limitedRight;
	int level;
	static CBridge* __instance;
public:
	static CBridge* GetInstance();
	CBridge();
	CBridge(D3DXVECTOR2 position, float limitedLeft, float limitedRight);
	~CBridge();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CBridge *LPBRIDGE;
