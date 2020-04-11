#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

using namespace std;

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left; 
	int top;
	int right;
	int bottom;
	int isFlipImage;

	D3DXVECTOR2 position;
	LPDIRECT3DTEXTURE9 texture;
public: 
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int isFlipImage = 0, D3DXVECTOR2 position = { 0, 0 });
	
	void Draw(float x, float y, int alpha = 255);
	D3DXVECTOR2 GetPosition() { return this->position; }
};

typedef CSprite * LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int isFlipImage = 0, D3DXVECTOR2 position = { 0, 0 });
	LPSPRITE Get(int id);
	void CSprites::Clear();

	static CSprites * GetInstance();
};



