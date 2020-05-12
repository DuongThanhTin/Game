#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "Utils.h"
#include "Game.h"
#include "define.h"
 
class CViewPort
{
private:
	static CViewPort* __instance;
	D3DXVECTOR2 position;
	int width;
	int height;
public:
	CViewPort();
	CViewPort(D3DXVECTOR2 position, int width, int height);
	void SetPosition(D3DXVECTOR2 position);
	D3DXVECTOR2 GetPosition();
	D3DXVECTOR2 ConvertWorldToViewPort(D3DXVECTOR2 worldPosition);
	D3DXVECTOR2 ConvertViewPortToWorld(D3DXVECTOR2 viewportPosition);
	void Update(D3DXVECTOR2 playerPosition, int startPosition, int endPosition);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	static CViewPort* GetInstance();
	~CViewPort();
};

