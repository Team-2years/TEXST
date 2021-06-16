#include "stdafx.h"
#include "dip.h"



HRESULT dip::init()
{

	return S_OK;
}

HRESULT dip::init(POINT position)
{
	_imageName = IMAGEMANAGER->findImage("dip");

	_x = 204 + 28 + position.x * 56;
	_y = 208 + 24 + position.y * 56;
	_frameX = 0;
	_frameY = 0;
	_rc = RectMakeCenter(_x, _y+15 , _imageName->getFrameWidth() - 8, _imageName->getFrameHeight() - 40);
	// 얘도 감지범위 따위 필요 없따
	_radius = 0;
	_damage = 1;
	_angle = 0;
	_speed = 5;
	_blendCount = _currentFrameX = _currentFrameY = _maxCount = _count = _rndCount = 0;
	_rndFireCount = RND->getFromIntTo(60, 80);
	_st = DIP;
	_blend = 150;
	_hp = 5;

	return S_OK;
}

void dip::release()
{
}

void dip::update()
{
	playPtn(_ptn);
	_rc = RectMakeCenter(_x, _y + 15, _imageName->getFrameWidth() - 8, _imageName->getFrameHeight() - 40);
}

void dip::render()
{
	draw();
}

void dip::move()
{
	
}

void dip::draw()
{
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), _rc);
	}
	if (_blendCount % 10 >= 5)
	{
		RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "dip", _x, _y, _currentFrameX, _currentFrameY, false, true, _blend);
		RENDERMANAGER->pushBackRenderInfo(getMiddle(), "dipshadow", _x, _y + 15, false, true, 150);

	}
	else
	{
		RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "dip", _x, _y, _currentFrameX, _currentFrameY, false);
		RENDERMANAGER->pushBackRenderInfo(getMiddle(), "dipshadow", _x, _y + 15, false, true, 150);
	}
	if (_blendCount > 0)
		_blendCount--;
}

void dip::playPtn(enemyPtn ptn)
{

	switch (ptn)
	{
	case EPTNA:
		_count++;
		if (_count % 2 == 0 && _maxCount > 0)
		{
			if (_angle > PI / 2 && _angle < PI * 3 / 2)
				_currentFrameY = 1;
			else
				_currentFrameY = 0;
			_frameX++;
			switch (_frameX) // 프레임별로 조작하기 위한 기적의 똥쇼
			{
			case 0:
				_currentFrameX = 0;
				break;
			case 1:
			case 2:
				_currentFrameX = 1;
				break;
			case 3:
			case 4:
				_currentFrameX = 2;
				break;

			case 5:
			case 6:
				
			case 7:
			case 8:
			case 9:
			case 10:
			case 12:
			case 13:

			case 14:
			case 15:
				
			case 16:
			case 17:

			case 18:
			case 19:
			case 20:
			case 21:

			case 22:
			case 23:
			case 24:
			case 25:
				if (_frameX % 10 >= 5)
					_currentFrameX = 3;
				else
					_currentFrameX = 4;
				break;
			default:
				_currentFrameX = 0;
				break;
			}
			if (_frameX <= 25 && _speed > 0)
			{
				_x += cosf(_angle) * _speed;
				_y += -sinf(_angle) * _speed;
				
			}
			_count = 0;
			if (_frameX % 5 == 1)
			{
				_speed -= 1;
			}
			_maxCount -= 1;
			
			break;
	default:
		break;
		}
	}
}