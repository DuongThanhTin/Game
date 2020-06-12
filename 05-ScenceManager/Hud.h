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
	DWORD timecount;
	int scoreHud;
	int scoreSubWeaponHud;
	int numLifeHud;
	int timeHud;
	int idSubWeapon;
	int healthSimon;
	int healthBoss;
public:
	CHud();
	~CHud();
	void Draw(D3DXVECTOR2 position);
	void Render();
	void Update(DWORD dt);
	static CHud* GetInstance();
	//GET
	int GetScoreHud() { return scoreHud; }
	int GetScoreSubWeaponHud() { return scoreSubWeaponHud; }
	int GetNumLifeHud() { return numLifeHud; }
	int GetTimeHud() { return timeHud; }
	int GetIdSubWeapon() { return idSubWeapon; }
	int GetHealthSimon() { return healthSimon; }
	int GetHealthBoss() { return healthBoss; }

	//SET
	void SetScoreHub(int scoreHud) { this->scoreHud = scoreHud; }
	void SetScoreSubWeaponHub(int scoreSubWeaponHud) { this->scoreSubWeaponHud = scoreSubWeaponHud; }
	void SetNumLifeHub(int numLifeHud) { this->numLifeHud = numLifeHud; }
	void SetTimeHud(int timeHud) { this->timeHud = timeHud; }
	void SetItem(int idSubWeapon) { this->idSubWeapon = idSubWeapon; }
	void SetHealthSimon(int healthSimon) { this->healthSimon = healthSimon; }
	void SetHealthBoss(int healthBoss) { this->healthBoss = healthBoss; }
	
	//function
	void IncreaseScoreSubWeapon(int score) { scoreSubWeaponHud = scoreSubWeaponHud + score; }
	void IncreaseScoreHud(int score) { scoreHud = scoreHud + score; }
	void IncreaseHealthSimon(int health) { healthSimon = healthSimon + health; }
	void DecreaseHealth() { healthSimon = healthSimon - 2; }
};

typedef CHud* LPHUD;
