#include "Weapon.h"

#define STOPWATCH_ITEM_GRAVITY				0.0005f
#define STOPWATCH_ITEM_BBOX_WIDTH			15
#define STOPWATCH_ITEM_BBOX_HEIGHT			15

class CStopWatch : public CWeapon
{
	int timeLock = 0;
public:
	CStopWatch();
	~CStopWatch();
	void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *ojects);
};