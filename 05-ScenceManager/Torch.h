#pragma once
#include"GameObject.h"
#include"define.h"
#include "Item.h"
#include "Utils.h"
#include "ObjectNoMove.h"

#define TORCH_BBOX_WIDTH 18
#define TORCH_BBOX_HEIGHT 30
 

class CTorch : public CObjectNoMove
{
	vector<LPGAMEOBJECT> objectsItem;
public:
	CTorch();
	CTorch(D3DXVECTOR2 position, int nextItemID);
	~CTorch();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};

typedef CTorch* LPTORCH;

