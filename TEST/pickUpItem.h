#pragma once
#include "gameNode.h"


enum pickUpType
{
	PNONE,
	PCOIN,
	PBOMB,
	PKEY,
	PHEART,
	PSPARKBOMB
};

class pickUpItem :
    public gameNode
{
protected:
	image* _imageName;
	float _x;
	float _y;
	float _frameX;
	float _frameY;
	int _count;
	pickUpType _st;
	RECT _rc;
public:
	pickUpItem() {}
	~pickUpItem() {}

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	inline RECT getRect() { return _rc; }
	inline pickUpType getPickUpType() { return _st; }
	int getCount() { return _count; }
};

