#include "HideBrick.h"



CHideBrick::CHideBrick() {

	id = ID_HIDEBRICK;
}

CHideBrick::CHideBrick(D3DXVECTOR2 position, int width, int height, int hidebrick_id)
{
	this->width = width;
	this->height = height;
	this->hidebrick_id = hidebrick_id;
	this->x = position.x;
	this->y = position.y;
	id = ID_HIDEBRICK;
	AddAnimation(HIDEBRICK_APPEAR);
	AddAnimation(HIDEBRICK_BLACK);
	isShowEffectRock = false;
}

CHideBrick::~CHideBrick() {

}
void CHideBrick::Render()
{

	if (state == OBJECTS_STATE_DESTROY)
	{
		animations[1]->Render(x, y);
	}
	else
		animations[0]->Render(x, y);
	RenderBoundingBox();
}

void CHideBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{

	if (state == OBJECTS_STATE_DESTROY)
	{
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
	else
	{
		l = x;
		t = y - height;
		r = x + width;
		b = y;
	}
}
void CHideBrick::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (isShowEffectRock)
	{
		for (size_t i = 0; i < coObjects->size(); i++)
		{

			if (coObjects->at(i)->GetID() == ID_ROCK && hidebrick_id == coObjects->at(i)->GetHideBrickId())
			{
				coObjects->at(i)->Update(dt, coObjects);
				//break;
			}
		}
	}
}

void CHideBrick::BeDamaged()
{
	isShowEffectRock = true;
	
}

CHideBrick* CHideBrick::__instance = NULL;
CHideBrick* CHideBrick::GetInstance()
{
	if (__instance == NULL) __instance = new CHideBrick();
	return __instance;
}