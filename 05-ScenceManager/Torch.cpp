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
	timeFire = 0;
}

void CTorch::GetBoundingBox(float &l, float &t, float &r, float &b) 
{
	l = x;
	t = y - TORCH_BBOX_HEIGHT;
	r = x + TORCH_BBOX_WIDTH;
	b = y;
}


