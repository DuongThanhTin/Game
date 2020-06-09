#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include "Game.h"
#include "Textures.h"
#include "Sprites.h"
#include "GameObject.h"
#include "define.h"
#include "Text.h"

class CHud
{
	static CHud* __instance;
	LPDIRECT3DTEXTURE9 texBackground;
	LPTEXT textHud;
	int scoreHud;
	int scoreSubWeaponHud;
	int numLifeHud;
	int timeHud;
	int idSubWeapon;
public:
	CHud();
	~CHud();
	void Draw(D3DXVECTOR2 position);
	void Render();
	void Update(DWORD dt);
	static CHud* GetInstance();
	int GetScoreHud() { return scoreHud; }
	int GetScoreSubWeaponHud() { return scoreSubWeaponHud; }
	int GetNumLifeHud() { return numLifeHud; }
	int GetTimeHud() { return timeHud; }
	int GetIdSubWeapon() { return idSubWeapon; }
	void IncreaseScoreSubWeaponLargeHeart() { scoreSubWeaponHud = scoreSubWeaponHud + 5; }
	void IncreaseScoreSubWeaponSmallHeart() { scoreSubWeaponHud = scoreSubWeaponHud + 1; }
	void SetScoreHub(int scoreHud) { this->scoreHud = scoreHud; }
	void SetScoreSubWeaponHub(int scoreSubWeaponHud) { this->scoreSubWeaponHud = scoreSubWeaponHud; }
	void SetNumLifeHub(int numLifeHud) { this->numLifeHud = numLifeHud; }
	void SetItem(int idSubWeapon) { this->idSubWeapon = idSubWeapon; }
};

typedef CHud* LPHUD;
