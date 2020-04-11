#include "Sprites.h"
#include "Game.h"
#include "Utils.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int isFlipImage, D3DXVECTOR2 position)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
	this->isFlipImage = isFlipImage;
	this->position = position;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, int alpha)
{
	CGame * game = CGame::GetInstance();
	int xTmp = x + position.x;
	int yTmp = y + position.y - (bottom - top);

	game->Draw(xTmp, yTmp, texture, left, top, right, bottom, alpha, isFlipImage);
}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int isFlipImage , D3DXVECTOR2 position)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex, isFlipImage, position);
	sprites[id] = s;

	DebugOut(L"[INFO] sprite added: %d, %d, %d, %d, %d, %d, %d \n", id, left, top, right, bottom, isFlipImage, position);
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}

/*
	Clear all loaded textures
*/
void CSprites::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	sprites.clear();
}



