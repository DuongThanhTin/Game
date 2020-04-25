#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "Utils.h"
#include "Game.h"
#include "define.h"
#include <vector>
#include "Item.h"
 
class CListItem
{
public:
	static CListItem* __instance;
	static CListItem* GetInstance();
	vector<CItem*> ListItem;	// list chứa các item

	CListItem();
	~CListItem();
};