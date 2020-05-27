#include "Bridge.h"

CBridge* CBridge::__instance;
CBridge* CBridge::GetInstance()
{
	if (__instance == NULL) __instance = new CBridge();
	return __instance;
}

CBridge::CBridge()
{
	id = ID_BRIDGE;
	//SetState(SPEARKNIGHT_STATE_WALKING);
	nx = -1;
}

CBridge::~CBridge()
{
}

CBridge::CBridge(D3DXVECTOR2 position, float limitedLeft, float limitedRight)
{
	x = position.x;
	y = position.y;
	this->limitedLeft = limitedLeft;
	this->limitedRight = limitedRight;
	id = ID_BRIDGE;
	nx = -1;
	vx = nx*BRIDGE_SPEED;
	AddAnimation(951);
}

void CBridge::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y - BRIDGE_BBOX_HEIGHT;
	right = x + BRIDGE_BBOX_WIDTH;
	bottom = y;

}
void CBridge::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;


	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
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
		//y += min_ty*dy + ny*0.1f;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if ((CSimon*)(e->obj))
			{
				if (e->nx != 0)   
				{
					x += dx;
				}
			}
			

			else if (dynamic_cast<CBrick*>(e->obj))
			{
				if (e->nx != 0)
				{
					DebugOut(L"nx<0\n");
					vx = -vx;
				}
			}
		}


		// clean up collision events
		for (auto iter : coEvents) delete iter;
		coEvents.clear();
	}

	if (x <= limitedLeft) {
		nx = -nx;
		vx = nx*vx;
	}

	else if (x >= limitedRight) {
		nx = -nx;
		vx = nx*vx;
	}
	

}

void CBridge::Render()
{
	animation_set->at(BRIDGE_ANI_MOVE)->Render(x, y);
	//animations[0]->Render(x, y);
	RenderBoundingBox();
}

