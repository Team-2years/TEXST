#pragma once
#include "pickUpItem.h"
class bomb :
    public pickUpItem
{
public:
	bomb() {}
	~bomb() {}

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();
};

