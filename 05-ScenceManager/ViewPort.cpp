#include "ViewPort.h"

CViewPort* CViewPort::__instance = NULL;

CViewPort::CViewPort()
{
	position = { 0, 0 };
	height = 176;
	width = 320;
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

/*Viewport và World có tọa độ ngược nhau
- World hướng lên
- Viewport hướng xuống
*/

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
	if (position.x > endPosition - width)
		position.x = endPosition - width;

	position.y = int((playerPosition.y - 50) / 176) * 176;
	if (position.y > 176 * 3 - height)
		position.y = 176 * 3 - height;
	//DebugOut(L"Position: %d\n", position.x);
}

CViewPort::~CViewPort()
{
}

CViewPort * CViewPort::GetInstance()
{
	if (__instance == NULL) __instance = new CViewPort();
	return __instance;
}