#pragma once
#include "GameObject.h"
#include "define.h"
#include "Rock.h"

#define HIDEBRICK_BBOX_WIDTH  16
#define HIDEBRICK_BBOX_HEIGHT 16
#define HIDEBRICK_APPEAR 790
#define HIDEBRICK_BLACK 791

class CHideBrick : public CGameObject
{
	int width;
	int height;
	int hidebrick_id;
public:
	bool isShowEffectRock;
	CHideBrick();
	CHideBrick(D3DXVECTOR2 position, int width, int height, int rock_id);
	~CHideBrick();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void BeDamaged();
	virtual int IsShowEffectRock() { return isShowEffectRock; }
	static CHideBrick* __instance;
	static CHideBrick* GetInstance();
};