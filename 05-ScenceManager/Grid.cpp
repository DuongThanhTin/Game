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

}

CGrid::~CGrid()
{
}



void CGrid::GetObjects(vector<LPGAMEOBJECT> &objects)
{	
	float vl, vt, vr, vb;
	CViewPort::GetInstance()->GetBoundingBox(vl, vt, vr, vb);

	// Để Tìm các Objects va chạm với Viewport trong Grid
	int wMin = vl / width - 1;
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

	//DebugOut(L"AA %d\n", wMin);
	// Add to set to avoid duplication
	for (int i = wMin; i < wMax; i++)
		for (int j = hMin; j < hMax; j++)
		{
			for (size_t k = 0; k < cells[j][i].size(); k++)
			{
				if ((find(objects.begin(), objects.end(), cells[j][i].at(k)) != objects.end() == false))
				{
					if (cells[j][i].at(k)->IsVisible())
					{
						objects.push_back(cells[j][i].at(k));
					}
				}
			}
		}

	//Debug Grid
	for (auto iter : objects)
	{
		if (iter->GetID() == ID_ROCK)
		{
			//DebugOut(L"Test Grid %d\n", iter->GetID());
		}
	}
}

void CGrid::LoadObj(LPGAMEOBJECT obj)
{
	float ol, ot, or , ob, gl, gt, gr, gb;
	float x, y;
	obj->GetPosition(x, y);
	int grid_row, grid_column;

	//Objects chua Active thì bounding = 0
	if (obj->GetID() == ID_GHOST )
	{
		grid_row = int(y / height);
		grid_column = int(x / width);
		cells[grid_row][grid_column].push_back(obj);
	}
	else if(obj->GetID() == ID_BOSS)
	{
		grid_row = int(y / height);
		grid_column = int(x / width);
		cells[grid_row][grid_column].push_back(obj);
	}
	else
	{
		obj->GetBoundingBox(ol, ot, or , ob);
		for (int j = 0; j < row; j++)
			for (int i = 0; i < column; i++)
			{
				gl = i * width;
				gr = (i + 1) * width;
				gt = j * height;
				gb = (j + 1) * height;
				if (CGame::IsIntersectAABB({ (long)ol, (long)ot, (long) or , (long)ob },
				{ (long)gl, (long)gt, (long)gr, (long)gb }))
				{
					cells[j][i].push_back(obj);
				}
			}
	}



	


}



