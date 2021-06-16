#include "stdafx.h"
#include "coin.h"

HRESULT coin::init(float x, float y)
{
	_x = x;
	_y = y;
	

	_imageName = IMAGEMANAGER->findImage("coin1");
	_frameX = _frameY = _count = 0;
	_st = PCOIN;
	_rc = RectMakeCenter(_x, _y, _imageName->getFrameWidth() - 30, _imageName->getFrameHeight() - 8);
	return S_OK;
}

void coin::release()
{
}

void coin::update()
{
	_count++;
	if (_count % 8 == 0)
	{
		if (_frameX >= _imageName->getMaxFrameX() + 8) _frameX = 0;

		if (_frameX >= 7 )
		_imageName->setFrameX(_frameX - 7);
		else
		_imageName->setFrameX(0);

		
		_frameX++;
		_count = 0;
	}
}

void coin::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
	float middle = (_rc.top + _rc.bottom) / 2;
	RENDERMANAGER->pushBackFrameRenderInfo(middle, "coin1", _x, _y, false);
}
