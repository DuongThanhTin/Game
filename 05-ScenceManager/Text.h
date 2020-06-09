#pragma once
#include "define.h"
#include "Game.h"
#include "Textures.h"
#include "Sprites.h"
#include "Utils.h"
#include<string>
#include <sstream>
using namespace std;

class CText
{
	static CText* __instance;
	CText();

public:
	~CText();

	static CText* GetInstance();

	void DrawStringNumber(int number, D3DXVECTOR2 position, int length);
	void DrawSubWeapon(D3DXVECTOR2 position,int info);
	void DrawHealthBar(D3DXVECTOR2 position, int health, int kind);
	int ConvertTextToNumber(char c);
};

typedef CText* LPTEXT;