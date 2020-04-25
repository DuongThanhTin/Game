﻿#include "TileMap.h"

std::wstring s2ws(const std::string& s);
#define ID_TEX_TILESET_01 -10
#define HUD_HEIGHT			50

CTileSet::CTileSet()
{
}

void CTileSet::LoadFromFile(LPCWSTR filePath)
{
	DebugOut(L"[INFO] HELLO %d: \n", filePath);
	// Load info
	ifstream file(filePath);
	json j = json::parse(file);
	tileWidth = j["tilesets"][0]["tilewidth"].get<int>();
	tileHeight = j["tilesets"][0]["tileheight"].get<int>();
	columnNumber = j["tilesets"][0]["columns"].get<int>();
	int tileCount = j["tilesets"][0]["tilecount"].get<int>();

	string tmpPath = "textures\\" + j["tilesets"][0]["image"].get<string>();
	rowNumber = (tileCount - 1) / columnNumber + 1;
	DebugOut(L"[INFO] rowNumber OK: %d\n", rowNumber);
	DebugOut(L"[INFO] tileWidth OK: %d\n", tileWidth);
	wstring sTmp;
	sTmp = s2ws(tmpPath);
	LPCWSTR imagePath = sTmp.c_str();

	//DebugOut(L"[INFO] imagePath OK: %d\n", imagePath);
	// Add list tiles
	for (int i = 0; i < rowNumber; i++)
		for (int j = 0; j < columnNumber; j++)
		{
			RECT tmpRect = { j * tileWidth, i * tileHeight, (j + 1) * tileWidth, (i + 1) * tileHeight };
			int tmpID = i * columnNumber + j + 1;
			listTile.insert(pair<int, RECT>(tmpID, tmpRect));

			//Debug
			//DebugOut(L"[INFO] tmpID OK: %d\n", tmpRect);
		}

	// Add texture
	CTextures::GetInstance()->Add(ID_TEX_TILESET_01, imagePath, 0);
	this->texture = CTextures::GetInstance()->Get(ID_TEX_TILESET_01);
	if (texture)
		DebugOut(L"Load tile texure OK: %s\n", imagePath);

	file.close();
}

void CTileSet::DrawTile(int id, D3DXVECTOR2 position)
{
	RECT sourceRect = listTile[id];
	CGame::GetInstance()->Draw(position.x, position.y, texture, sourceRect.left, sourceRect.top, sourceRect.right, sourceRect.bottom);
}

int CTileSet::GetTileWidth()
{
	return tileWidth;
}

int CTileSet::GetTileHeight()
{
	return tileHeight;
}

// https://stackoverflow.com/questions/27220/how-to-convert-stdstring-to-lpcwstr-in-c-unicode
// covert std::string to std:: wstring
std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}


CTileMap::CTileMap()
{
	tileSet = new CTileSet();
	wStart = 0;
	wEnd = 49 * 16;
}

void CTileMap::LoadFromFile(LPCWSTR filePath)
{
	// Load info
	ifstream file(filePath);
	json j = json::parse(file);


	//rowNumber = j["layers"][0]["height"].get<int>();
	//columnNumber = j["layers"][0]["width"].get<int>();

	vector<int> data = j["layers"][0]["data"].get<vector<int>>();
	rowMapNumber = j["layers"][0]["height"].get<int>();
	columnMapNumber = j["layers"][0]["width"].get<int>();
	//DebugOut
	DebugOut(L"rowNumber: %d\n ", rowNumber);
	DebugOut(L"columnMapNumber: %d\n ", columnMapNumber);

	// Map data from vector to matrix	
	mapData = new int*[rowMapNumber];
	for (int i = 0; i < rowMapNumber; i++)
	{
		mapData[i] = new int[columnMapNumber];

		for (int j = 0; j < columnMapNumber; j++)
		{
			int tmp = i * columnMapNumber + j;
			mapData[i][j] = data[tmp];
		}
	}

	// Load tileset
	tileSet->LoadFromFile(filePath);

	for (int i = 0; i < rowMapNumber; i++)
		for (int j = 0; j < columnMapNumber; j++)
			DebugOut(L"%d, ", mapData[i][j]);
	DebugOut(L"\n");
}

void CTileMap::Render(D3DXVECTOR2 position)
{
	CViewPort * viewport = CViewPort::GetInstance();

	/*for (int i = 0; i < 11; i++) // rowNumber
	{
		for (int j = 0; j < 49; j++) // ColumnNumber
		{
		D3DXVECTOR2 pos;
		pos.x = int (position.x + j * tileSet->GetTileWidth());
		pos.y = int (position.y + i * tileSet->GetTileHeight());
		pos = CViewPort::GetInstance()->ConvertWorldToViewPort(pos);
		//DebugOut(L" DRAW %d %d \n", i, j);
		tileSet->DrawTile(mapData[i][j], pos);
		}
	}*/

	//Vẽ map khi camera di chuyển
	//DebugOut(L"ASD %d\n", viewport->GetPosition().x);
	//DebugOut(L"TILE test\n");
	int wStart = viewport->GetPosition().x / tileSet->GetTileWidth();
	int hStart = viewport->GetPosition().y / tileSet->GetTileHeight();
	int wEnd = wStart + viewport->GetWidth() / tileSet->GetTileWidth();
	if (wEnd > columnMapNumber) {
		wEnd = columnMapNumber;
	}
	int hEnd = hStart + viewport->GetHeight() / tileSet->GetTileHeight();
	if (hEnd > rowMapNumber) {
		hEnd = rowMapNumber;
	}
	for (int i = hStart; i < hEnd; i++)
	{
		for (int j = wStart; j < wEnd; j++)
		{
			D3DXVECTOR2 pos;
			pos.x = position.x + j * tileSet->GetTileWidth();
			pos.y = position.y + i * tileSet->GetTileHeight() + 45;
			pos = CViewPort::GetInstance()->ConvertWorldToViewPort(pos);
		//	DebugOut(L" DRAW %d %d \n",i,j);
			tileSet->DrawTile(mapData[i][j], pos);
		}
	}
}

 