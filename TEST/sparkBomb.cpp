#include "stdafx.h"
#include "sparkBomb.h"

HRESULT sparkBomb::init(float x, float y)
{
	_x = x;
	_y = y;
	_imageName = IMAGEMANAGER->findImage("sparkbomb");
	_frameX = _frameY = _count = 0;
	_st = PSPARKBOMB;
	_rc = RectMakeCenter(_x, _y + 16, _imageName->getFrameWidth() - 32, _imageName->getFrameHeight() - 54);
	return S_OK;
}

void sparkBomb::release()
{
}

void sparkBomb::update()
{
	_count++;
	if (_count % 4 == 0)
	{
		if (_frameX >= _imageName->getMaxFrameX()) _frameX = 0;
		_frameX++;
		if (_count == 120)
			EFFECTMANAGER->play("bombeffect", _x, _y - 50, (_rc.top + _rc.bottom) / 2);
	}
}

void sparkBomb::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc);
	}
	float middle = (_rc.top + _rc.bottom) / 2;
	RENDERMANAGER->pushBackFrameRenderInfo(middle, "sparkbomb", _x, _y, _frameX, _frameY, false);
}
