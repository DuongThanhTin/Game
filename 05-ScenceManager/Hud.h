#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include "Game.h"
#include "Textures.h"
#include "Simon.h"
#include "Sprites.h"
#include "define.h"

class CHud
{
	static CHud* __instance;
	LPDIRECT3DTEXTURE9 texBackground;
public:
	CHud();
	~CHud();
	void Draw(D3DXVECTOR2 position);
	static CHud* GetInstance();
};

typedef CHud* LPHUD;
