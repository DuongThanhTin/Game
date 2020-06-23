#include "Boss.h"



CBoss::~CBoss()
{
}

CBoss::CBoss(D3DXVECTOR2 position, int nx, int nextItemID)
{
	x = position.x;
	y = position.y;
	AddAnimation(991);
	SetState(BOSS_STATE_SLEEP);
	id = ID_BOSS;
	this->healthEnemy = NUM_HEALTH;
	hud = CHud::GetInstance();
	timeDestroyed = 0;
}

void CBoss::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	//left = top = right = bottom = 0.0f;
	if (healthEnemy > 0)
	{
		left = x;
		top = y - BOSS_BBOX_HEIGHT;
		right = x + BOSS_BBOX_WIDTH;
		bottom = y;
	}
	else
	{
		if (timeDestroyed == 0)
		{
			left = top = right = bottom = 0;
		}
	}

}

void CBoss::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	

	if (state == ENEMY_STATE_DESTROY)
	{
		vy = 0;
	}
	else if (isActive)
	{
		if (start_untouchable != 0)
		{
			vx = 0.001;
			Untouchable();
		}
		else
		{
			if (timeStopWatch == 0)
			{
				if (healthEnemy > 0)
				{

				}
				else
				{
					if (timeDestroyed == 0 && !isDestroyed)
					{
						timeDestroyed = GetTickCount();
						isDestroyed = true;
					}

					else if (GetTickCount() - timeDestroyed > TIME_EFFECT_BOSS_DESTROYED)
					{
						this->SetState(BOSS_STATE_DIE);
						timeDestroyed = 0;
					}

				}
			}
			else
			{
				vx = vy = 0;
			}
		}
		//hud->SetHealthBoss(healthEnemy);
		//hud->Update(dt);
	}
	
}

void CBoss::Render()
{
	int ani;
	if (healthEnemy > 0)
	{
		ani = 0;
		if (isActive)
		{
			ani = BOSS_ANI_FLYING_RIGHT;
		}

		animation_set->at(ani)->Render(x, y);
	}
	else if(healthEnemy <=0)
	{
		if (state != BOSS_STATE_DIE)
		{
			animations[0]->Render(x, y);
		}
	}
	
	RenderBoundingBox();
}


CBoss* CBoss::__instance;
/*CBoss* CBoss::GetInstance()
{
	return 1;
}*/