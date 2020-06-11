#include "ListItem.h"
 
CListItem* CListItem::__instance = NULL;


CListItem* CListItem::GetInstance()
{
	if (__instance == NULL) __instance = new CListItem();
	return __instance;
}

CListItem::CListItem()
{
	ListItem.clear();

}


CListItem::~CListItem()
{
}
