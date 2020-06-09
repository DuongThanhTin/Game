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
	scoreSubWeaponHud = 5;
	timeHud = 300;
	
}


CHud::~CHud()
{
}

void CHud::Draw(D3DXVECTOR2 position)
{
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(INFO_HUD)->Draw(position.x, position.y);
	CGame* game = CGame::GetInstance();
	
	
	//SCORE
	textHud->DrawStringNumber(GetScoreHud(), { 55, 12 },6);

	//STAGE
	textHud->DrawStringNumber(game->GetCurrtentSceneID(), { 235, 12 },2);

	//ScoreSubWeapon
	textHud->DrawStringNumber(GetScoreSubWeaponHud(), { 200,22 }, 2);
	
	//Num Life
	textHud->DrawStringNumber(GetNumLifeHud(), { 200, 32 }, 2);

	//Time
	textHud->DrawStringNumber(GetTimeHud(), { 150, 12 }, 2);

	//ITEM SUBWEAPON
	textHud->DrawSubWeapon({ 157,29 }, GetIdSubWeapon());
}

void CHud::Update(DWORD dt)
{
	//timeHud--;
}