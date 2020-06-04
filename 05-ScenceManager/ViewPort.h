#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "Utils.h"
#include "Game.h"
#include "define.h"
#include "GameObject.h" 

#define CAMERA_HEIGHT 200
#define CAMERA_WIDTH 272

class CViewPort : public CGameObject
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
	void Render();
	static CViewPort* GetInstance();
	~CViewPort();
};

