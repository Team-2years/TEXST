#include "stdafx.h"
#include "key.h"

HRESULT key::init(float x, float y)
{

	_x = x;
	_y = y;


	_imageName = IMAGEMANAGER->findImage("key");
	_frameX = _frameY = _count = 0;
	_st = PKEY;
	_rc = RectMakeCenter(_x-1, _y+10, _imageName->getFrameWidth()-2, _imageName->getFrameHeight()-30);
	return S_OK;
}

void key::release()
{
}

void key::update()
{
	_count++;
	if (_count % 2 == 0)
	{
		if (_frameX >= _imageName->getMaxFrameX() + 31) _frameX = 0;

		if (_frameX >= 30)
			_imageName->setFrameX(_frameX - 30);
		else
			_imageName->setFrameX(0);
		
		_frameX++;
		_count = 0;
	}
}

void key::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
	float middle = (_rc.top + _rc.bottom) / 2;
	RENDERMANAGER->pushBackFrameRenderInfo(middle, "key", _x, _y, false);
}
