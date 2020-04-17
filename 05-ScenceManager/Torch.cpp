#include "Torch.h"



CTorch::CTorch()
{
}


CTorch::~CTorch()
{
}

CTorch::CTorch(D3DXVECTOR2 position, int nextItemID)
{
	x = position.x;
	y = position.y;
	id = ID_TORCH;
	this->nextItemID = nextItemID;
}

void CTorch::GetBoundingBox(float &l, float &t, float &r, float &b) {
	l = x;
	t = y - TORCH_BBOX_HEIGHT;
	r = x + TORCH_BBOX_WIDTH;
	b = y ;
}

void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
	CGameObject::Update(dt);
	if (state == STATE_DESTROYED) {
		CGameObject* nextItem;
		switch (GetNextItemID())
		{
		case ID_HEART:
			nextItem = new CHeart({ x,y  });
			nextItem->Render();
			objectsItem.push_back(nextItem);
			break;
		default:
			nextItem = NULL;
			break;
		}
		if (nextItem) {
			coObjects->push_back(nextItem);
			objectsItem.push_back(nextItem);
		//	RenderItem();
		}
	}
}

void CTorch::Render()
{
	animation_set->at(0)->Render(x, y);
}

