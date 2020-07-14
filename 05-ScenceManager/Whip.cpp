#include "Whip.h"


CWhip::CWhip()
{
	level = 0;
	id = ID_WHIP;

	//level 0 MAGIC WHIP
	AddAnimation(WHIP_ANI_RIGHT_00);//0 
	AddAnimation(WHIP_ANI_LEFT_00);//1 

	//level 1 SHORT CHAIN
	AddAnimation(WHIP_ANI_RIGHT_01);//2 
	AddAnimation(WHIP_ANI_LEFT_01);//3 

	//level 2 LONG CHAIN
	AddAnimation(WHIP_ANI_RIGHT_02);//4 
	AddAnimation(WHIP_ANI_LEFT_02);//5 
}


CWhip::~CWhip()
{
}

int CWhip::GetAnimation() {
	int ani = 0;
	if (level == 0 && nx > 0)
		ani = 0;
	else if (level == 0 && nx < 0)
		ani = 1;
	else if (level == 1 && nx > 0)
		ani = 2;
	else if (level == 1 && nx < 0)
		ani = 3;
	else if (level == 2 && nx > 0)
		ani = 4;
	else if (level == 2 && nx < 0)
		ani = 5;
	return ani;
}

void CWhip::GetBoundingBox(float &l, float &t, float &r, float &b) {
	if (animations[GetAnimation()]->GetCurrentFrame() == 2) {
		CSound::getInstance()->play("usingwhip", false, 1);

		int width, height;
		switch (level)
		{
		case 0: 
			width = WHIP_BBOX_WIDTH_00;
			height = WHIP_BBOX_HEIGHT_00;
			break;
		case 1:  //SHORT CHAIN
			width = WHIP_BBOX_WIDTH_01;
			height = WHIP_BBOX_HEIGHT_01;
			break;
		case 2:	 //LONG CHAIN
			width = WHIP_BBOX_WIDTH_02;
			height = WHIP_BBOX_HEIGHT_02;
			break;
		}
		l = x + animations[GetAnimation()]->GetFramePosition().x;
		t = y + animations[GetAnimation()]->GetFramePosition().y - height;
		r = l + width;
		b = y + animations[GetAnimation()]->GetFramePosition().y;
	}
	else
		l = t = r = b = 0.0f;
}

void CWhip::Render()
{
	AppearHitEffect();
	animations[GetAnimation()]->Render(x, y);
	
}

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects, D3DXVECTOR2 playerPosition, int playerNx) {
	CWeapon::Update(dt, coObjects);

	this->x = playerPosition.x;
	this->y = playerPosition.y;
	this->nx = playerNx;
}

void CWhip::Upgrade()
{
	if (level < 2)
		level++;

	DebugOut(L"LEVEL %d\n", GetLevel());
}

int CWhip::GetDamageWhip()
{
	if (level == 0)
	{
		damagedWeapon = 1;
	}
	else
	{
		damagedWeapon = 2;
	}

	return damagedWeapon;
}

CWhip* CWhip::__instance;
CWhip* CWhip::GetInstance()
{
	if (__instance == NULL) __instance = new CWhip();
	return __instance;
}