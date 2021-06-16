#include "stdafx.h"
#include "monstro.h"


HRESULT monstro::init()
{
	// 보스 몬스터
	return S_OK;
}

HRESULT monstro::init(POINT position)
{
	_imageName = IMAGEMANAGER->findImage("monstro");

	_x = 204 + 28 + position.x * 56;
	_y = 208 + 24 + position.y * 56;
	_frameX = 0;
	_frameY = 0;
	_rc = RectMakeCenter(_x, _y, _imageName->getFrameWidth(), _imageName->getFrameHeight());
	_damage = 1;
	_angle = 0;
	_speed = 4;
	_z = 0;
	_blendCount = _currentFrameX = _currentFrameY = _maxCount = _count = _rndCount = 0;
	_rndFireCount = RND->getFromIntTo(50, 80);
	_st = MONSTRO;
	_blend = 150;
	_hp = 200;
	_gravity = 0;
	_sumg = 0;
	return S_OK;
}

void monstro::release()
{
}

void monstro::update()
{
	if (_hp < 0)
	{
		_currentFrameX = 4;
		_z = 0;
	}else
	playPtn(_ptn);

	_rc = RectMakeCenter(_x, _y, _imageName->getFrameWidth() - 40, _imageName->getFrameHeight() - 159);
	
}

void monstro::render()
{
	draw();
}

void monstro::move()
{
}

void monstro::draw()
{
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), _rc);
	}


	RENDERMANAGER->pushBackFrameRenderInfo(getMiddle(), "monstro", _x, _y - 80 + _z, _currentFrameX, _currentFrameY, false);
	RENDERMANAGER->pushBackRenderInfo(getMiddle(), "monstroshadow", _x, _y + 10, false, true, 150);


}

void monstro::playPtn(enemyPtn ptn)
{
	switch (ptn)
	{
	case EPTNA: // 낮은 점프 패턴
		_count++;
		if (_count % 2 == 0 && _maxCount > 0)
		{
			switch (_frameX) // 프레임별로 조작하기 위한 기적의 똥쇼
			{
			case 0:

				_setAngle = getAngle2(
					DATAMANAGER->getX(),
					DATAMANAGER->getY(),
					_x,
					_y);
				break;
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:

			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
				_currentFrameX = 4;
				break;
			case 11:

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
			case 26:
			case 27:
			case 28:
			case 29:
			case 30:
			case 31:
			default:
				_gravity += 0.02f * 10;
				_sumg += _gravity;
				_z = _z - 20 + _sumg;
				_currentFrameX = 8;
				if (_z > 0)
					_z = 0;
				break;
			}
			if (_setAngle > PI / 2 && _setAngle < PI * 3 / 2)
				_currentFrameY = 1;
			else
				_currentFrameY = 0;
			_frameX++;

			if (_frameX <= 33 && _speed > 0 && _frameX > 12)
			{
				_x -= cosf(_setAngle) * _speed;
				_y -= -sinf(_setAngle) * _speed;
			}
			else if (_frameX > 35 && _sumg != 0)
			{
				_currentFrameX = 0;
				_z = 0;
				_gravity = 0;
				_sumg = 0;
				

			}
			_count = 0;
		}
		break;
	case EPTNB: // 눈물 쏘기 패턴
		_count++;
		if (_count % 2 == 0 && _maxCount > 0)
		{


			switch (_frameX) // 프레임별로 조작하기 위한 기적의 똥쇼
			{
			case 0:

				_setAngle = getAngle2(
					DATAMANAGER->getX(),
					DATAMANAGER->getY(),
					_x,
					_y);
				break;
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				_currentFrameX = 4;
				break;
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
				_currentFrameX = 0;
				break;
			case 11:

			case 12:
			case 13:
			case 14:
			case 15:

			case 16:
			case 17:
			case 18:

			case 19:
			case 20:
				_currentFrameX = 2;
				break;
			case 21:
			
			case 22:
			case 23:
			case 24:
			case 25:

			case 26:
			case 27:
			case 28:

			case 29:
			case 30:
				if (_frameX % 2 == 0)
					_x += 3;
				else
					_x -= 3;

				_currentFrameX = 3;
				break;
			case 31:
			default:
				break;
			}
			if (_setAngle > PI / 2 && _setAngle < PI * 3 / 2)
				_currentFrameY = 1;
			else
				_currentFrameY = 0;
			_frameX++;

			if (_frameX > 35 && _sumg != 0)
			{
				_currentFrameX = 0;
				_z = 0;
				_gravity = 0;
				_sumg = 0;

			}
			_count = 0;
		}
		break;
	case EPTNC:
		_count++;
		
		if (_count % 2 == 0 && _maxCount > 0)
		{
			switch (_frameX) // 프레임별로 조작하기 위한 기적의 똥쇼
			{
			case 0:
				_setAngle = getAngle2(
					DATAMANAGER->getX(),
					DATAMANAGER->getY(),
					_x,
					_y);
				_currentFrameX = 0;
				break;
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:

				_currentFrameX = 0;
				break;
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
				_y += 1;
				_currentFrameX = 5;
				break;
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
				_z -= 100;
				_currentFrameX = 6;
				break;
			case 21:
			case 22:
			case 23:
			case 24:
			case 25:
			case 26:
			case 27:
			case 28:
			case 29:
			case 30:
			case 31:
			case 32:
			case 33:
			case 34:
			case 35:
			case 36:
			case 37:
			case 38:
			case 39:
			case 40:
				_x -= cosf(_setAngle) * _speed;
				_y -= -sinf(_setAngle) * _speed;
				_speed -= 1;
				if (_speed < 0)
					_speed = 0;
				break;
			default:
				_currentFrameX = 7;
				_z += 100;
				if (_z >= 0) {
					_z = 0;
				}
				break;
			}
			_frameX++;

			if (_setAngle > PI / 2 && _setAngle < PI * 3 / 2)
				_currentFrameY = 1;
			else
				_currentFrameY = 0;
			if (_frameX > 42 && _z == 0)
			{
				_currentFrameX = 4;
				if (_frameX % 4 >= 2)
					_x += 2;
				else
					_x -= 2;

			}
			_count = 0;
		}

		break;
	default:
		break;
	}
}
