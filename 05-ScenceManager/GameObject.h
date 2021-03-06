#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "Animations.h"
#include "Utils.h"
#include "define.h"

 
using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define  UNTOUCHABLE_TIME	200
class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	
	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL) 
	{ 
		this->t = t; 
		this->nx = nx; 
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj; 
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};


class CGameObject
{
public:

	float x; 
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx,ny;	 

	int state;
	int id;
	int nextItemID;
	int areaactive_enemy;
	int hidebrick_id;
	int scoreEnemy;
	int healthEnemy;
	int damagedWeapon;

	bool isOnGround;
	bool isActive;
	bool isOnGroundFire;
	bool isInGrid = true;
	bool isEnemy = false;
	bool isStopFrame = false;

	bool isVisible;
	DWORD dt;
	DWORD start_untouchable = 0;
	int timeStopWatch = 0;

	CAnimationSet animations;
	LPANIMATION_SET animation_set;

public: 
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void AddPosition(float x, float y) { this->x = this->x + x; this->y = this->y + y; }
	void SetSpeed(float vx, float vy) { this->vx = vx; this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	int GetID() { return id; }
	int GetState() { return this->state;  }

	void RenderBoundingBox(int alpha = 255);

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }
	 
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny, 
		float &rdx, 
		float &rdy);
	void AddAnimation(int aniId);
	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }
	virtual void BeHurted() {};
	virtual void BeDamaged() {};
	virtual void BeDamagedEnemy(int score) {};
	virtual int GetDamageWhip() { return damagedWeapon; }
	virtual void TakeDamagedEnemy(int damage);
	virtual void ResetAnimation();
	virtual void TimeFireDestroy();
	virtual void Untouchable();

	// Visibility
	void SetVisible(bool isVisible) { this->isVisible = isVisible; }
	bool IsVisible() { return this->isVisible; }
	int GetNx();
	int GetNy();
	int GetNextItemID();
	int GetAreaActiveEnemy();
	int GetHideBrickId() { return hidebrick_id; }
	virtual int GetScore() { return scoreEnemy; }
	virtual int GetHealthEnemy() { return healthEnemy; }
	virtual void SetHealthEnemy(int healthEnemy) {  this->healthEnemy = healthEnemy; }
	virtual int GetDamagedWeapon() { return damagedWeapon; }
	virtual void SetDamagedWeapon(int damaged) { this->damagedWeapon = damaged; }
	void StartStopWatch();
	~CGameObject();
};

