#pragma once
#include "define.h"
#include "Enemy.h"
#include "Brick.h"
#include "Bone.h"
#include "ViewPort.h"

#define SKELETON_WALKING_SPEED 0.03f
#define SKELETON_GRAVITY 0.002f

#define SKELETON_BBOX_WIDTH 16
#define	SKELETON_BBOX_HEIGHT 30

#define SKELETON_STATE_IDLE 100
#define SKELETON_STATE_JUMP 200
#define SKELETON_STATE_WALKING 300

#define SKELETON_ANI_WALKING_LEFT 0
#define SKELETON_ANI_WALKING_RIGHT 1

#define TIME_ATTACK_BONE 1000

class CSkeleton : public CEnemy
{
	float limitedRight, limitedLeft;
	int id_AISkeleton;
	int timeAttackBone;
	vector<CBone *> bonesOb;
	//vector<vector<float>> bones;
	
	//CAnimation* bone_ani_left = CAnimations::GetInstance()->Get(ID_ANI_BONE_LEFT);
	//CAnimation* bone_ani_right = CAnimations::GetInstance()->Get(ID_ANI_BONE_RIGHT);
public:
	CSkeleton();
	CSkeleton(D3DXVECTOR2 position, int nextItemID, float limitedLeft, float limitedRight, int nx, int idSkeleton);
	~CSkeleton();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
};

