#include "Grid.h"




CGrid::CGrid(int column, int row, int width, int height)
{
	//SCENE 1, 4: width 112, height 44 
	//SCENE 3: width 112, height 64
	//ScENE 2: width 100, heigth 64
	this->column = column;
	this->row = row;
	this->width = width;
	this->height = height;

	groundObjects = new set<LPGAMEOBJECT>*[row];
	for (int i = 0; i < row; i++)
		groundObjects[i] = new set<LPGAMEOBJECT>[column];
}

CGrid::~CGrid()
{
}

void CGrid::InsertObject(LPGAMEOBJECT object)
{
	float ol, ot, or , ob, gl, gt, gr, gb;

	object->GetBoundingBox(ol, ot, or , ob);
	
	for (int i = 0; i < column; i++)
		for (int j = 0; j < row; j++)
		{
			gl = i * width;
			gr = (i + 1) * width;
			gt = j * height ;
			gb = (j + 1) * height;
			if (CGame::IsIntersectAABB({ (long)ol, (long)ot, (long) or , (long)ob },
			{ (long)gl, (long)gt, (long)gr, (long)gb }))
				groundObjects[j][i].insert(object);
		}
}

void CGrid::LoadObjects(vector<LPGAMEOBJECT>* objects)
{
	for (auto iter : *objects)
		InsertObject(iter);
}

void CGrid::GetObjects(vector<LPGAMEOBJECT>* objects)
{
	float vl, vt, vr, vb;
	CViewPort::GetInstance()->GetBoundingBox(vl, vt, vr, vb);
	
	// Để Tìm các Objects va chạm với Viewport trong Grid
	int wMin = vl / width -1;
	int wMax = vr / width + 1;
	int hMin = vt / height;
	int hMax = vb / height;

	if (wMin < 0)
		wMin = 0;

	if (wMax > column)
		wMax = column;

	if (hMin < 0)
		hMin = 0;

	if (hMax > row)
		hMax = row;

	//DebugOut(L"AA %d\n", objects->size());
	// Add to set to avoid duplication
	set<LPGAMEOBJECT> tmpObjects;
	for (int i = wMin; i < wMax; i++)
		for (int j = hMin; j < hMax; j++)
			for (auto iter : groundObjects[j][i])
				if(iter->GetState()!=STATE_DESTROYED)
					tmpObjects.insert(iter);
					

	for (auto iter : tmpObjects)
	{	
		objects->push_back(iter);
	}		
	//DebugOut(L"ID %d \n", tmpObjects.size());

}

void CGrid::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	// move objects
	moveObjects.clear();

	// Add move objects
	for (auto iter : *objects)
	{
		switch (iter->GetID())
		{
		case ID_CANDLE:
		case ID_TORCH:
		case ID_STAIR:
		case ID_HIDEBRICK:
		case ID_AREAACTIVE:
		case ID_AREASWITCHCAM:
			break;
		default:
			moveObjects.insert(iter);
			break;
		}
	}
	objects->clear();
	
	for (auto iter : moveObjects)
	{
		//DebugOut(L"moveObject %d\n", iter->GetID());
		objects->push_back(iter);
	}

	
	// Add ground objects
	GetObjects(objects);
}

void CGrid::Clear()
{

}

