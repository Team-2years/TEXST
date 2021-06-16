#pragma once
#include "pickUpItem.h"
class coin :
    public pickUpItem
{
public:
    coin() {}
    ~coin() {}

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();
};

