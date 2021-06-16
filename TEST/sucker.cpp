#include "stdafx.h"
#include "sucker.h"

HRESULT sucker::init()
{
	return S_OK;
}

HRESULT sucker::init(POINT position)
{
	_imageName = IMAGEMANAGER->findImage("sucker");
	_x = 204 + 28 + position.x * 56;
	_y = 208 + 24 + position.y * 56;
	_frameX = 0;
	_frameY = 0;
	_rc = RectMakeCenter(_x, _y, _imageName->getFrameWidth() - 30, _imageName->getFrameHeight()- 50);
	
	_radius = 0;
	_damage = 1;
	_angle = 0;
	_speed = 1.5;
	_blendCount = _currentFrameX = _currentFrameY = _maxCount = _count = _rndCount = 0;
	_rndFireCount = RND->getFromIntTo(60, 80);
	_st = SUCKER;
	_blend = 150;
	_hp = 9;
	return S_OK;
}

void sucker::release()
{
}

void sucker::update()
{
	move();
	_count++;
	// °¡¶ó ÆÄ´Ú¸ó 
	if (_count % 3 == 0)
	{
		if (_frameX > _imageName->getMaxFrameX() ) _frameX = 0;
		_currentFrameX = _frameX;
		_frameX++;
		_count = 0;
	}
	if (_angle > PI / 2 && _angle < PI * 3 / 2)
		_currentFrameY = 0;
	else
		_currentFrameY = 1;
	_rc = RectMakeCenter(_x, _y, _imageName->getFrameWidth() - 30, _imageName->getFrameHeight() - 50);
}

void sucker::render()
{
	draw();
}

void sucker::move()
{
	_x -= cosf(_angle) * _speed + RND->getFromFloatTo(-2, 2);
	_y -= -sinf(_angle) * _speed + RND->getFromFloatTo(-2, 2);
}

void sucker::draw()
{
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), _rc);
	}
	if (_blendCount % 10 >= 5)
	{
		RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "sucker", _x, _y - 50, _currentFrameX, _currentFrameY, false, true, _blend);
		RENDERMANAGER->pushBackRenderInfo(getMiddle(), "dipshadow", _x, _y, false, true, 150);

	}
	else
	{
		RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "sucker", _x, _y - 50, _currentFrameX, _currentFrameY, false);
		RENDERMANAGER->pushBackRenderInfo(getMiddle(), "dipshadow", _x, _y, false, true, 150);
	}
	if (_blendCount > 0)
		_blendCount--;
}

void sucker::playPtn(enemyPtn ptn)
{
}
