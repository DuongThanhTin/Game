#include "Whip.h"


CWhip::CWhip()
{
	level = 0;
	id = ID_WHIP;

	AddAnimation(111);
	AddAnimation(112);
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
	return ani;
}

void CWhip::GetBoundingBox(float &l, float &t, float &r, float &b) {
	if (animations[GetAnimation()]->GetCurrentFrame() == 2) {
		int width, height;
		switch (level)
		{
		case 0:
			width = WHIP_BBOX_WIDTH_01;
			height = WHIP_BBOX_HEIGHT_01;
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
	animations[GetAnimation()]->Render(x, y);
	RenderBoundingBox();
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
}