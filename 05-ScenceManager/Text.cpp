#include "Text.h"

CText* CText::__instance;

CText::CText()
{

}

CText::~CText()
{
}

CText * CText::GetInstance()
{
	if (__instance == NULL) __instance = new CText();
	return __instance;
}

void CText::DrawStringText(char * s, D3DXVECTOR2 position, int length)
{
	for (int i = 0; i < strlen(s); i++)
	{
		CSprites::GetInstance()->Get(INFO_TEXT_HUD + ConvertTextToNumber(s[i]))->Draw(position.x, position.y);
		position.x += 7;
	}
}
void CText::DrawStringNumber(int number, D3DXVECTOR2 position, int length)
{
	string str = to_string(number);
	for (int i = 1; i < length ; i++)
	{
		CSprites::GetInstance()->Get(INFO_TEXT_HUD)->Draw(position.x, position.y);
		position.x += 7;
	}

	//Đếm có bao nhiêu chữ số
	for (int i = 0; i < str.size(); i++)
	{
		CSprites::GetInstance()->Get(INFO_TEXT_HUD + ConvertTextToNumber(str[i]))->Draw(position.x, position.y);
		position.x += 7;
	}
}

void CText::DrawSubWeapon(D3DXVECTOR2 position, int info)
{
	switch (info)
	{
	case ID_BOOMERANGITEM:
		CSprites::GetInstance()->Get(INFO_WEAPON_BOOMERANG)->Draw(position.x, position.y);
		break;
	case ID_AXEITEM:
		CSprites::GetInstance()->Get(INFO_WEAPON_AXE)->Draw(position.x, position.y);
		break;
	case ID_DAGGERITEM:
		CSprites::GetInstance()->Get(INFO_WEAPON_DAGGER)->Draw(position.x, position.y-2);
		break;
	case ID_HOLYWATERITEM:
		CSprites::GetInstance()->Get(INFO_WEAPON_HOLYWATER)->Draw(position.x, position.y);
		break;
	default:
		break;
	}
}

int CText::ConvertTextToNumber(char c)
{
	return c - '0'; //Mã ASCII kí tự ‘0’ thì biểu diễn số là 48
}