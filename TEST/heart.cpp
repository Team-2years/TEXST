#include "stdafx.h"
#include "heart.h"

HRESULT heart::init(float x, float y)
{
	_x = x;
	_y = y;


	_imageName = IMAGEMANAGER->findImage("heart");
	_frameX = _frameY = _count = 0;
	_st = PHEART;
	_rc = RectMakeCenter(_x, _y +8, _imageName->getWidth()-32, _imageName->getHeight()-58);
	return S_OK;
}

void heart::release()
{
}

void heart::update()
{
}

void heart::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
	float middle = (_rc.top + _rc.bottom) / 2;
	RENDERMANAGER->pushBackRenderInfo(middle, "heart", _x, _y, false);
}
