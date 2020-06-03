#include "AreaSwitchCam.h"



CAreaSwitchCam::CAreaSwitchCam() {

	id = ID_AREASWITCHCAM;
}

CAreaSwitchCam::CAreaSwitchCam(D3DXVECTOR2 position, int width, int height, int scene_id, int player_x, int player_y)
{
	this->width = width;
	this->height = height;
	this->x = position.x;
	this->y = position.y;
	this->scene_id = scene_id;
	this->player_x = player_x;
	this->player_y = player_y;
	id = ID_AREASWITCHCAM;
}

CAreaSwitchCam::~CAreaSwitchCam() {

}
void CAreaSwitchCam::Render()
{
	RenderBoundingBox();
}

void CAreaSwitchCam::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y - height;
	r = x + width;
	b = y;
}