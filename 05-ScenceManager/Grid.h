#pragma once
#include <set> 
#include "Game.h"
#include "GameObject.h"
#include "ViewPort.h"
#include "define.h"
#include "Textures.h"

//#define GRID_WIDTH 112 //8*16 = 128
//#define GRID_HEIGHT 80 //5*16+8 = 88

class CGrid
{
	set<LPGAMEOBJECT>** groundObjects;
	set<LPGAMEOBJECT> moveObjects;
	vector<LPGAMEOBJECT> updateObjects;
	vector<LPGAMEOBJECT> cells[10][10];
	int column;
	int row;
	int width;
	int height;
public:
	CGrid(int column, int row,int witdh, int height);
	~CGrid();

	void GetObjects(vector<LPGAMEOBJECT> &objects);
	void LoadObj(LPGAMEOBJECT obj);

};

