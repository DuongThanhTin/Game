#pragma once
#include"GameObject.h"
#include"define.h"
#include "Item.h"
#include "Heart.h"
#include "Utils.h"

#define TORCH_BBOX_WIDTH 18
#define TORCH_BBOX_HEIGHT 30

class CTorch : public CGameObject
{
	vector<LPGAMEOBJECT> objectsItem;
public:
	CTorch();
	CTorch(D3DXVECTOR2 position, int nextItemID);
	~CTorch();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CTorch* LPTORCH;

