#include "Hud.h"

CHud* CHud::__instance;
CHud * CHud::GetInstance()
{
	if (__instance == NULL) __instance = new CHud();
	return __instance;
}

CHud::CHud()
{
	textHud = CText::GetInstance();
	scoreSubWeaponHud = NUM_SCORE_SUBWEAPON;
	healthSimon = NUM_HEALTH;
	timeHud = NUM_TIME;
	timecount = GetTickCount();
}


CHud::~CHud()
{
}

void CHud::Draw(D3DXVECTOR2 position)
{
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(INFO_HUD)->Draw(position.x, position.y);
	CGame* game = CGame::GetInstance();
	
	//STAGE
	textHud->DrawStringNumber(game->GetCurrtentSceneID(), { 235, 12 }, 2);

	//SCORE
	textHud->DrawStringNumber(GetScoreHud(), { 55, 12 },6);

	//ScoreSubWeapon
	textHud->DrawStringNumber(GetScoreSubWeaponHud(), { 200,22 }, 2);
	
	//Num Life
	textHud->DrawStringNumber(GetNumLifeHud(), { 200, 32 }, 2);

	//Time
	textHud->DrawStringNumber(GetTimeHud(), { 150, 12 }, 2);

	//ITEM SUBWEAPON
	textHud->DrawSubWeapon({ 157,29 }, GetIdSubWeapon());

	//HEALTH SIMON
	textHud->DrawHealthBar({ 55,24 }, GetHealthSimon(),NUM_ID_SIMON);
	//HEALTH BOSS
	textHud->DrawHealthBar({ 55,34 }, 16, NUM_ID_BOSS);
}

void CHud::Update(DWORD dt)
{
	//SET TIME
	if (GetTickCount() - timecount > NUM_COUNT_TIME && timecount > 0)
	{
		timeHud--;
		timecount = GetTickCount();
	}
}