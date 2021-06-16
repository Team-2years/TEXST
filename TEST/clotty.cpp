#include "stdafx.h"
#include "clotty.h"

HRESULT clotty::init()
{
	// 특징 설명
	// 이 친구는 지맴대로 움직인다.
	// 그리고 4방향으로 눙물을 쏜다.
	return S_OK;
}

HRESULT clotty::init(POINT position)
{
	_imageName = IMAGEMANAGER->findImage("clotty");

	_x = 204 + 28 + position.x * 56;
	_y = 208 + 24 + position.y * 56;
	_frameX = 0;
	_frameY = 0;
	_rc = RectMakeCenter(_x, _y + 30, _imageName->getFrameWidth() -65, _imageName->getFrameHeight() - 110);
	// 감지 범위 clotty는 그딴거 필ㄹ요 없따
	_radius = 0;
	_damage = 1;
	_speed = 3;
	_angle = 0;
	_blendCount = _currentFrameX = _currentFrameY = _maxCount =_count = _rndCount = 0;
	_rndFireCount = RND->getFromIntTo(50, 80);
	_st = CLOTTY;
	_blend = 150;
	_hp = 12;
	return S_OK;

}

void clotty::release()
{
}

void clotty::update()
{
	playPtn(_ptn);
	
	_rc = RectMakeCenter(_x, _y + 30, _imageName->getFrameWidth() -65, _imageName->getFrameHeight() - 110);
}

void clotty::render()
{
	draw();
}

void clotty::move()
{
}

void clotty::draw()
{
	if (KEYMANAGER->isToggleKey('T')) 
	{
		Rectangle(getMemDC(), _rc);
	}
	if (_blendCount % 10 >= 5) 
	{
		RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "clotty", _x, _y, _currentFrameX, _currentFrameY, false, true, _blend);
		RENDERMANAGER->pushBackRenderInfo(getMiddle(), "clottyshadow", _x, _y + 30, false, true, 150);
		
	}
	else
	{
		RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "clotty", _x, _y, _currentFrameX, _currentFrameY, false);
		RENDERMANAGER->pushBackRenderInfo(getMiddle(), "clottyshadow", _x, _y + 30, false, true, 150);
	}
	if (_blendCount > 0)
	_blendCount--;
}

void clotty::playPtn(enemyPtn ptn)
{
	switch (ptn)
	{
	case EPTNA:
		_count++;
		if (_count % 1 == 0 && _maxCount > 0)
		{
			if (_angle > PI / 2 && _angle < PI * 3 / 2)
				_currentFrameY = 2;
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
			case 3:
			case 4:
				_currentFrameX = 1;
				break;		
			case 5:
			case 6:			
			case 7:
			case 8:
				_currentFrameX = 2;
				break;
			case 9:				
			case 10:
			case 12:	
			case 13:
				_currentFrameX = 3;
				break;
			case 14:
			case 15:				
			case 16:
				_currentFrameX = 4;
				break;
			case 17:
			case 18:				
				_currentFrameX = 5;
				break;
			case 19:
			case 20:
			case 21:
				_currentFrameX = 6;
				break;
			case 22:
			case 23:
			case 24:
			case 25:
				_currentFrameX = 7;
				break;
			default:
				_currentFrameX = 0;
				break;
			}
			if (_frameX <= 17)
			{
				_x += cosf(_angle) * _speed;
				_y += -sinf(_angle) * _speed;
			}
			_count = 0;
		}
		_speed = RND->getFromIntTo(2, 10);
		_maxCount--;
		if (_maxCount == 0)
		{
			_rndFireCount = RND->getFromIntTo(75, 90);
			_frameX = 0;
		}
		break;
	case EPTNB:
		_count++;
		if (_count % 3 == 0 && _maxCount > 0)
		{
			if (_angle > PI / 2 && _angle < PI * 3 / 2)
				_currentFrameY = 3;
			else
				_currentFrameY = 1;
			
			_frameX++;
			switch (_frameX)
			{
			case 1:
			case 2:
				_currentFrameX = 0;
				break;
			case 3:
			case 4:
				_currentFrameX = 2;
				break;
			case 5:
				_currentFrameX = 1;
				break;
			case 6:
				_currentFrameX = 2;
				break;
			case 7:
			case 8:
			case 9:
				_currentFrameX = 0;
				break;
			default:
				if (_angle > PI / 2 && _angle < PI * 3 / 2)
				{
					_currentFrameY = 2;
					_currentFrameX = 0;
				}
				else
				{
					_currentFrameY = 0;
					_currentFrameX = 0;
				}
				break;
			}
		}
		_maxCount--;
		if (_maxCount == 0)
		{
			_frameX = 0;
		}
		break;
	default:
		break;
	}
}

