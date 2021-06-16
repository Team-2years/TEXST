#include "stdafx.h"
#include "bomb.h"

HRESULT bomb::init(float x, float y)
{
	_x = x;
	_y = y;


	_imageName = IMAGEMANAGER->findImage("bomb");
	_frameX = _frameY = _count = 0;
	_st = PBOMB;
	_rc = RectMakeCenter(_x, _y+16, _imageName->getWidth() -32, _imageName->getHeight() - 54);
	return S_OK;
}

void bomb::release()
{
}

void bomb::update()
{
}

void bomb::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
	float middle = (_rc.top + _rc.bottom) / 2;
	RENDERMANAGER->pushBackRenderInfo(middle, "bomb", _x, _y, false);
}
