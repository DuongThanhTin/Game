#pragma once
#include"GameObject.h"
#include"define.h"
#include "Item.h"
#include "Utils.h"
#include "ObjectNoMove.h"

#define CANDLE_BBOX_WIDTH 12
#define CANDLE_BBOX_HEIGHT 12


class CCandle : public CObjectNoMove
{
	vector<LPGAMEOBJECT> objectsItem;
public:
	CCandle();
	CCandle(D3DXVECTOR2 position, int nextItemID);
	~CCandle();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};

typedef CCandle* LPCANDLE;

