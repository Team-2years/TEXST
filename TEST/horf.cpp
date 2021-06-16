#include "stdafx.h"
#include "horf.h"

HRESULT horf::init()
{
	return S_OK;
}

HRESULT horf::init(POINT position)
{
	_imageName = IMAGEMANAGER->findImage("horf");

	_x = 204 + 28 + position.x * 56;
	_y = 208 + 24 + position.y * 56;
	_frameX = 0;
	_frameY = 0;
	_rc = RectMakeCenter(_x, _y -2, _imageName->getFrameWidth()-10, _imageName->getFrameHeight()- 50);
	_radius = 300;
	_damage = 1;
	_angle = 0;
	_speed = 0;
	_blendCount = _currentFrameX = _currentFrameY = _count = _rndCount = 0;
	_maxCount = 0;
	_rndFireCount = RND->getFromIntTo(60, 80);
	_st = HORF;
	_blend = 150;
	_hp = 9;

	return S_OK;
}

void horf::release()
{
}

void horf::update()
{
	if (_angle > PI / 2 && _angle < PI * 3 / 2)
		_currentFrameY = 0;
	else
		_currentFrameY = 1;
	playPtn(_ptn);
	_rc = RectMakeCenter(_x, _y - 2, _imageName->getFrameWidth() - 10, _imageName->getFrameHeight() - 50);
}

void horf::render()
{
	draw();
}

void horf::move()
{
}

void horf::draw()
{
	if (KEYMANAGER->isToggleKey('T'))
	{
		EllipseMakeCenter(getMemDC(), _x, _y, _radius * 2, _radius * 2);
		Rectangle(getMemDC(), _rc);
	}
	if (_blendCount % 10 >= 5)
	{
		RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "horf", _x, _y - 30, _currentFrameX, _currentFrameY, false, true, _blend);
		RENDERMANAGER->pushBackRenderInfo(getMiddle(), "clottyshadow", _x, _y, false, true, 150);

	}
	else
	{
		RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "horf", _x, _y- 30, _currentFrameX, _currentFrameY, false);
		RENDERMANAGER->pushBackRenderInfo(getMiddle(), "clottyshadow", _x, _y, false, true, 150);
	}
	if (_blendCount > 0)
		_blendCount--;
}

void horf::playPtn(enemyPtn ptn)
{

	switch (ptn)
	{
	case EPTNA:
		_count++;
		
		if (_count % 2 == 0 && _maxCount > 0)
		{

			_frameX++;

			switch (_frameX) // 프레임별로 조작하기 위한 기적의 똥쇼
			{
			case 0:
				_currentFrameX = 0;
				break;
			case 1:
			case 2:
			case 3:
				_currentFrameX = 1;
				break;
			case 4:
			case 5:
				_currentFrameX = 0;
				break;
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
				_currentFrameX = 2;
				break;
			case 12:
			case 13:

			case 14:
			case 15:

			case 16:
			case 17:

			case 18:
			case 19:
			case 20:
			default:
				_currentFrameX = 0;
				break;
			}
			_count = 0;
			_maxCount -= 1;
		}
		break;
	default:
		break;
	}
}
