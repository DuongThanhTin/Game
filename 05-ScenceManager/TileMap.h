#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <fstream>
#include <string>
#include <vector>
#include "json.hpp"
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"
#include "ViewPort.h"

using json = nlohmann::json;

class CTileSet {
private:
	int	tileWidth;
	int tileHeight;
	int rowNumber;
	int columnNumber;
	map<int, RECT> listTile; //chứa các danh sách TileSet

	LPDIRECT3DTEXTURE9 texture;

public:
	CTileSet();
	void LoadFromFile(LPCWSTR filePath);
	void DrawTile(int id, D3DXVECTOR2 position);
	int GetTileWidth();
	int GetTileHeight();
	~CTileSet();
};

typedef CTileSet* LPTILESET;

class CTileMap
{
private:
	int rowNumber;
	int columnNumber;

	int rowMapNumber;
	int columnMapNumber;

	int limitedViewPort;

	int wStart;
	int wEnd;
	 
	LPTILESET tileSet;
	vector<vector<int>> widthEdge;
	int** mapData;

	int idground;
public:
	CTileMap();
	void LoadFromFile(LPCWSTR filePath);
	void DrawMap(D3DXVECTOR2 position);
	int GetLimitedViewPort() { return limitedViewPort; };
	~CTileMap();
};



