#include "Ghost.h"



CGhost::CGhost()
{
}


CGhost::~CGhost()
{
}

CGhost::CGhost(D3DXVECTOR2 position, int nextItemID,int nxGhost)
{
	x = position.x;
	y = position.y;
	id = ID_GHOST;
	AddAnimation(ANI_DESTROY);
	nx = -1;
	this->originY = y;
	delta = 0;
	scoreEnemy = NUM_SCORE_ENEMY_SPEARKNIGHT;
	this->nextItemID = nextItemID;
	this->healthEnemy = 3;
	isOnGround = true;
}

void CGhost::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	if (isActive)
	{
		if (!isDestroy)
		{
			left = x;
			top = y - GHOST_BBOX_HEIGHT;
			right = x + GHOST_BBOX_WIDTH;
			bottom = y;
		}
	}
	else
	{
		left = top = right = bottom = 0;
	}

}
void CGhost::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CEnemy::Update(dt, coObjects);
	//if (isInGrid != true)
		//return;

	// Simple fall down
	if (state == ENEMY_STATE_DESTROY)
	{
		vy = 0;
	}
	else if (isActive)
	{

		if (start_untouchable != 0)
		{
			vx = 0.00001;
			Untouchable();
		}
		else
		{
			if (timeStopWatch == 0)
			{
				isStopFrame = false;
				vx += nx*GHOST_WALKING_SPEED;
				delta += 3;
				y = sin(delta * 3.14 / 180) * 12 + originY;
			}
			else
			{
				isStopFrame = true;
				vx = 0;
				vy = 0;
			}

			
		}
		
	}


}

void CGhost::Render()
{
	if (state != ENEMY_STATE_DESTROY)
	{
		int ani = GHOST_ANI_WALKING_RIGHT;
		if (nx > 0)
		{
			ani = GHOST_ANI_WALKING_RIGHT;
		}
		else
		{
			ani = GHOST_ANI_WALKING_LEFT;
		}
		
		if (isActive)
		{
			if (isStopFrame)
			{
				animation_set->at(ani)->RenderFrame(x, y);
			}
			else
			{
				animation_set->at(ani)->Render(x, y);
			}
		}
	}
	else
	{
		animations[0]->Render(x, y);
	}


	RenderBoundingBox();
}

void CGhost::SetState(int state)
{
	CGameObject::SetState(state);

}