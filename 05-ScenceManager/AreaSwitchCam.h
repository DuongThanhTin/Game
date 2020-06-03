#pragma once
#include "Brick.h"
#include "define.h"

class CAreaSwitchCam : public CBrick
{
	int width;
	int height;
	int scene_id;
	int player_x;
	int player_y;
public:
	CAreaSwitchCam();
	~CAreaSwitchCam();
	CAreaSwitchCam(D3DXVECTOR2 position, int width, int height, int scene_id, int player_x, int player_y);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	int GetSceneID() { return scene_id; }
	int GetPlayerX() { return player_x; }
	int GetPlayerY() { return player_y; }
};

