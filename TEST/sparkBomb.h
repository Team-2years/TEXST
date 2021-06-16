#pragma once
#include "pickUpItem.h"
class sparkBomb :
    public pickUpItem
{
public:
    sparkBomb() {}
    ~sparkBomb() {}

    virtual HRESULT init(float x, float y);
    virtual void release();
    virtual void update();
    virtual void render();
};

