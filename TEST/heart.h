#pragma once
#include "pickUpItem.h"
class heart :
    public pickUpItem
{
public:
	heart() {}
	~heart() {}

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();
};

