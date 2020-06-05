#include "Hud.h"

CHud* CHud::__instance;
CHud * CHud::GetInstance()
{
	if (__instance == NULL) __instance = new CHud();
	return __instance;
}

CHud::CHud()
{
	this->texBackground = CTextures::GetInstance()->Get(ID_TEX_HUD);
}


CHud::~CHud()
{
}

void CHud::Draw(D3DXVECTOR2 position)
{
	CGame::GetInstance()->Draw(position.x, position.y, texBackground, 0, 0, 256, 40);
}
