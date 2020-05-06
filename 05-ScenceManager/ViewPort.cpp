#include "ViewPort.h"

CViewPort* CViewPort::__instance = NULL;
 
CViewPort::CViewPort()
{
	position = { 0, 0 };
	height = 256;
	width = 272; 
}

CViewPort::CViewPort(D3DXVECTOR2 position, int width, int height)
{
	this->position = position;
	this->width = width;
	this->height = height;
}

void CViewPort::SetPosition(D3DXVECTOR2 position) {
	this->position = position;
}

D3DXVECTOR2 CViewPort::GetPosition() {
	return position;
}


D3DXVECTOR2 CViewPort::ConvertWorldToViewPort(D3DXVECTOR2 worldPosition) {
	return{ worldPosition.x - position.x, worldPosition.y - position.y };
}

D3DXVECTOR2 CViewPort::ConvertViewPortToWorld(D3DXVECTOR2 viewportPosition) {
	return{ viewportPosition.x + position.x, viewportPosition.y + position.y };
}

void CViewPort::Update(D3DXVECTOR2 playerPosition, int startPosition, int endPosition) {

	//Cho Simon ở giữa camera (Vị trí simon trong camera)
	position.x = playerPosition.x - SCREEN_WIDTH/2;
	//Kiểm tra viewport ra ngoài world
	if (position.x < startPosition)
		position.x = startPosition;
	if (position.x > endPosition - SCREEN_WIDTH)
		position.x = endPosition - SCREEN_WIDTH;
}

CViewPort::~CViewPort()
{
}

CViewPort * CViewPort::GetInstance()
{
	if (__instance == NULL) __instance = new CViewPort();
	return __instance;
}