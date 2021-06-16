#pragma once
#include "pickUpItem.h"
class key :
    public pickUpItem
{
private:

public:
	key() {}
	~key() {}

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();
};

