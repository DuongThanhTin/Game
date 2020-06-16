#include "Rock.h"



CRock::CRock(D3DXVECTOR2 position, int hidebrick1_id)
{
	this->x = position.x;
	this->y = position.y;
	hidebrick_id = hidebrick1_id;
	id = ID_ROCK;
	number = NUMBER_ROCK;
	rock_x = new float[number];
	rock_y = new float[number];
	rock_vx = new float[number];
	rock_vy = new float[number];

	//Vx of 4 rock member
	float num_vx[4] = { ROCK_VX_1, ROCK_VX_2, ROCK_VX_3, ROCK_VX_4 };

	//Vy of 4 rock member
	float num_vy[4] = { ROCK_VY_1, ROCK_VY_2, ROCK_VY_3, ROCK_VY_4 };
	

	for (size_t i = 0; i < number; i++)
	{
		rock_x[i] = position.x;
		rock_y[i] = position.y;
	}

	for (size_t i = 0; i < number; i++)
	{
		rock_vx[i] = num_vx[i];
		rock_vy[i] = num_vy[i];

	}
	AddAnimation(ANI_ROCK);
}


CRock::~CRock()
{
}

void CRock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	CGameObject::Update(dt, coObject);
	for (int i = 0; i < number; i++)
	{
		rock_x[i] += rock_vx[i] * dt;
		rock_y[i] += rock_vy[i] * dt;
		rock_vy[i] += ROCK_GRAVITY * dt;
	}
 
}

void CRock::Render()
{
	for (int i = 0; i < number; i++)
	{
		animations[0]->Render(rock_x[i], rock_y[i]);
	}
}
