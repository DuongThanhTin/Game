#include "Boss.h"



CBoss::~CBoss()
{
}

CBoss::CBoss(D3DXVECTOR2 position, int nx, int limitedLeft, int limitedRight)
{
	x = position.x;
	y = position.y;
	this->default_x = x;
	this->default_y = y;
	this->limitedLeft = limitedLeft;
	this->limitedRight = limitedRight;
	nx = 1;
	AddAnimation(ID_ANI_EFFECT_BOSS);
	SetState(BOSS_STATE_SLEEP);
	id = ID_BOSS;
	delta = 0;
	this->healthEnemy = NUM_HEALTH;
	timeDestroyed = 0;
	timeIdle = 0;
	timeAttack = 0;

}

void CBoss::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	if (isActive)
	{
		if (!isDestroyed)
		{
			left = x;
			top = y - BOSS_BBOX_HEIGHT;
			right = x + BOSS_BBOX_WIDTH;
			bottom = y;
		}
	}
	else
	{
		left = top = right = bottom = 0;
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
					if (vx > 0)
					{
						//delta là mật độ lên xuống
						//số nhân ở sau là độ dài xuống
						vx += nx*0.005;
						x += vx;
						delta += 3;
						y = sin(delta * 3.14 / 180) * 36 + default_y*2 + 0.001*dt;
					}
					else
					{
						vx -= nx*0.005;
						x += vx;
						delta += 3;
						y = sin(delta * 3.14 / 180) * 36 + default_y*2 + 0.001*dt;
					}

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
						if (crystalBalls.size() < 1 && !isGameOver)
						{
							crystalBalls.push_back(new CCrystalBall({ default_x,default_y }));
						}

					}

					for (size_t i = 0; i < crystalBalls.size(); i++)
					{
						crystalBalls[i]->Update(dt, coObjects);
					}
				}
			}
			else
			{
				vx = vy = 0;
			}
		}
	}
	if (int(x) > limitedRight)
	{
		y += 0.05*dt;
		vx = -vx;
	}
	else if (x < limitedLeft)
	{
		vx = -vx;
		y += 0.05*dt;
	}

	//Collision Crystal Ball
	for (auto iter : *coObjects)
	{
		if (iter->GetID()== ID_SIMON)
		{
			float sl, st, sr, sb;		// simon object bbox
			float ol, ot, or , ob;		// object bbox
			iter->GetBoundingBox(sl, st, sr, sb);
			//GAME OVER
			for (size_t i = 0; i < crystalBalls.size(); i++)
			{
				crystalBalls[i]->GetBoundingBox(ol, ot, or , ob);
				if (CGame::GetInstance()->IsIntersectAABB({ long(sl),long(st), long(sr), long(sb) }, { long(ol), long(ot), long(or ), long(ob) })) {
					isGameOver = true;
					crystalBalls.erase(crystalBalls.begin() + i);
					i--;
					iter->SetPosition(CAMERA_ATTACK_BOSS_X_LEFT, POSITION_SIMON_GAMEOVER_Y);
				}
			}
		}
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
	
	for (auto iter : crystalBalls)
	{
		iter->Render();
	}

	if (isGameOver)
	{
		Draw({ 0, POSITION_SCENE_GAMEOVER_Y });
	}
	RenderBoundingBox();
}

void CBoss::Draw(D3DXVECTOR2 position)
{
	CSprites* sprites = CSprites::GetInstance();
	sprites->Get(ID_SPRITE_GAMEOVER)->Draw(position.x, position.y);
}

CBoss* CBoss::__instance;
/*CBoss* CBoss::GetInstance()
{
	return 1;
}*/