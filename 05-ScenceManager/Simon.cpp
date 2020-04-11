#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include "Simon.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"


CSimon::CSimon() {
	//id = ID_SIMON;

	untouchable = 0;
	jumpStart = 0;
	attackStart = 0;
	untouchableStart = 0;

	isOnGround = false;
	whip = new CWhip();
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += SIMON_GRAVITY*dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	//Collision with wall
	vector<LPGAMEOBJECT> wallObjects;
	for (int i = 0;i < coObjects->size();i++) {
		if (coObjects->at(i)->GetID() == ID_GROUND)
			wallObjects.push_back(coObjects->at(i));
	}


	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		//CalcPotentialCollisions(coObjects, coEvents); //Collision Objects
		CalcPotentialCollisions(&wallObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block 
		x += min_tx*dx + nx*0.1f;	
		y += min_ty*dy + ny*0.1f;

		if (nx != 0) vx = 0;

		if (ny < 0) {
			vy = 0;

			if (!isOnGround)
			{
				isOnGround = true;
			}
		}
		else y += dy;


		// clean up collision events
		for (auto iter : coEvents) delete iter;
		coEvents.clear();
	}

	// clean up collision events
	//for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	// update sub weapon
	if (GetTickCount() - attackSubStart > SIMON_ATTACK_TIME)
	{
		attackSubStart = 0;
	}


	// update jump state
	if (GetTickCount() - jumpStart > SIMON_JUMP_TIME)
		jumpStart = 0;

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchableStart > SIMON_UNTOUCHABLE_TIME)
	{
		untouchableStart = 0;
		untouchable = 0;
	}

	// update attack state and whip
	UpdateWhip(dt, coObjects);
	
	
}

void CSimon::Render()
{
	//http://gameprogrammingpatterns.com/state.html

	int ani;

	if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	else if (state == SIMON_STATE_ATTACK) {
		if (nx > 0)
			ani = SIMON_ANI_ATTACK_RIGHT;
		else
			ani = SIMON_ANI_ATTACK_LEFT;
	}

	else if (state == SIMON_STATE_JUMP) {
		if (!isOnGround) {
			if (nx > 0)
				ani = SIMON_ANI_SIT_RIGHT;
			else
				ani = SIMON_ANI_SIT_LEFT;
		}
		else {
			if (nx > 0)
				ani = SIMON_ANI_IDLE_RIGHT;
			else
				ani = SIMON_ANI_IDLE_LEFT;
		}
	}

	else if (state == SIMON_STATE_SIT) {
		if (nx > 0)
			ani = SIMON_ANI_SIT_RIGHT;
		else
			ani = SIMON_ANI_SIT_LEFT;
	}
	else if (state == SIMON_STATE_SIT_ATTACK) {
		if (nx > 0)
			ani = SIMON_ANI_SIT_ATTACK_RIGHT;
		else
			ani = SIMON_ANI_SIT_ATTACK_LEFT;
	}

	else {
		if (vx == 0) {
			if (nx > 0)
				ani = SIMON_ANI_IDLE_RIGHT;
			else
				ani = SIMON_ANI_IDLE_LEFT;
		}
		else {
			if (vx > 0) {
				ani = SIMON_ANI_WALKING_RIGHT;
			}
			else
				ani = SIMON_ANI_WALKING_LEFT;
		}
	}


	int alpha = 255;
	if (untouchableStart>0)
		alpha = 128;
	animation_set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox();
	if (attackStart)
		whip->Render();
}

void CSimon::RenderBoundingBox(int alpha)
{
	CGameObject::RenderBoundingBox(alpha);
	whip->RenderBoundingBox(alpha);
}

void CSimon::SetState(int state)
{
	if (attackStart > 0)
		return;
	if (attackSubStart > 0)
		return;

	//if (state != SIMON_STATE_JUMP)
	//	vx = 0;

	if (jumpStart > 0 && state != SIMON_STATE_ATTACK && state != SIMON_STATE_ATTACK_SUBWEAPON)
		return;

	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED_Y;
		y -= 5;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_ATTACK:
		break;
	case SIMON_STATE_SIT:
		SetSpeed(0, vy);
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	}
}

void CSimon::UpdateWhip(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	if (GetTickCount() - attackStart <= SIMON_ATTACK_TIME)
	{
		float playerX, playerY;
		if (state == SIMON_STATE_SIT_ATTACK) {
			playerY = y + 7;
		}
		else
			playerY = y;
		playerX = x - 2 * nx;
		whip->Update(dt, objects, { playerX, playerY }, nx);
	}
	else if (attackStart > 0)
	{
		attackStart = 0;
		if (state == SIMON_STATE_SIT_ATTACK) {
			state = SIMON_STATE_SIT;
		}
		else
			state = SIMON_STATE_IDLE;
	}
}


void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y - SIMON_BBOX_HEIGHT;
	right = x + SIMON_BBOX_WIDTH;
	bottom = y;
}

void CSimon::StartUntouchable()
{
	untouchable = 1;
	untouchableStart = GetTickCount();
}

void CSimon::StartAttack() {
	if (attackStart > 0)
		return;
	if (attackSubStart > 0)
		return;

	if (state != SIMON_STATE_JUMP)
		vx = 0;
	
	ResetAnimation();
	//whip->ResetAnimation();

	if (state == SIMON_STATE_SIT)
		SetState(SIMON_STATE_SIT_ATTACK);
	else
		SetState(SIMON_STATE_ATTACK);
	attackStart = GetTickCount();
}



void CSimon::StartJump()
{
	SetState(SIMON_STATE_JUMP);
	isOnGround = false;
	jumpStart = GetTickCount();
}
