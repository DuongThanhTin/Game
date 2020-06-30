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

void CTorch::GetBoundingBox(float &l, float &t, float &r, float &b) 
{

	if (!isDestroy)
	{
		l = x;
		t = y - TORCH_BBOX_HEIGHT;
		r = x + TORCH_BBOX_WIDTH;
		b = y;
	}
	else
	{
		l = t = r = b = 0;
	}
}


