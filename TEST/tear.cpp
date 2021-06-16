#include "stdafx.h"
#include "tear.h"

#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;

isaacTear::isaacTear()
{
}

isaacTear::~isaacTear()
{
}

HRESULT isaacTear::init(const char * imageName, const char * tearShadow)
{
	_imageName = imageName;
	_tearShadow = tearShadow;
	return S_OK;
}

void isaacTear::release()
{
}

void isaacTear::update()
{
	move();
}

void isaacTear::render()
{
	for (_viTear = _vTear.begin(); _viTear != _vTear.end(); ++_viTear)
	{
		Rectangle(getMemDC(), _viTear->rc);
		// this is ÈÖ¾îÁü
		if (_viTear->range * 70 - getDistance(_viTear->fireX, _viTear->fireY, _viTear->x, _viTear->y) < 50 && !_viTear->isAngle)
		{
			_viTear->gravity += 0.06f * 10;
			_viTear->sumg += _viTear->gravity;
			RENDERMANAGER->pushBackRenderInfo((_viTear->rc.bottom + _viTear->rc.top) / 2, _viTear->imageName, _viTear->rc.left, _viTear->rc.top - 50 + _viTear->sumg, true);
		}
		else
			RENDERMANAGER->pushBackRenderInfo((_viTear->rc.bottom + _viTear->rc.top) / 2, _viTear->imageName, _viTear->rc.left, _viTear->rc.top - 50, true);
		RENDERMANAGER->pushBackRenderInfo((_viTear->rc.bottom + _viTear->rc.top) / 2, _viTear->shadowName, _viTear->rc.left, _viTear->rc.top, true, true, 150);

	}
}

void isaacTear::fire(float x, float y, float angle, float shotspeed, float range, float tearX, float tearY)
{
	tagTear tear;
	ZeroMemory(&tear, sizeof(tagTear));
	tear.tearImage = IMAGEMANAGER->findImage(_imageName);
	tear.tearShadow = IMAGEMANAGER->findImage(_tearShadow);
	tear.imageName = _imageName;
	tear.shadowName = _tearShadow;
	tear.speed = shotspeed;
	tear.radius = tear.tearImage->getWidth() / 2;
	tear.x = tear.fireX = x;
	tear.y = tear.fireY = y;
	tear.angle = angle;
	tear.range = range;
	tear.tearX = tearX;
	tear.tearY = tearY;
	tear.gravity = 0;
	tear.shadowSize = tear.tearShadow->getHeight() +2;
	tear.rc = RectMakeCenter(tear.x, tear.y , tear.tearImage->getWidth(), tear.shadowSize);

	_vTear.push_back(tear);
}

void isaacTear::move()
{
	for (_viTear = _vTear.begin(); _viTear != _vTear.end();)
	{
		
		{
			_viTear->x += cosf(_viTear->angle) * (_viTear->speed * 8) + _viTear->tearX;
			_viTear->y += -sinf(_viTear->angle) * (_viTear->speed * 8) + _viTear->tearY;
		}
		_viTear->rc = RectMakeCenter(_viTear->x, _viTear->y,
			_viTear->tearImage->getWidth(),
			_viTear->shadowSize);

		if (_viTear->range * 70 < getDistance(_viTear->x, _viTear->y, _viTear->fireX, _viTear->fireY))
		{
			
			EFFECTMANAGER->play("teareffect7", _viTear->x, _viTear->y, (_viTear->rc.bottom + _viTear->rc.top)/2);
			_viTear = _vTear.erase(_viTear);
		}
		else ++_viTear;
	}
}

HRESULT enemyTear::init(const char * imageName, const char * tearShadow)
{
	_imageName = imageName;
	_tearShadow = tearShadow;
	return S_OK;
}

void enemyTear::release()
{
}

void enemyTear::update()
{
	move();
}

void enemyTear::render()
{
	for (_viTear = _vTear.begin(); _viTear != _vTear.end(); ++_viTear)
	{
		if (KEYMANAGER->isToggleKey('T'))
			Rectangle(getMemDC(), _viTear->rc);
		// this is ÈÖ¾îÁü
		if (_viTear->range * 70 - getDistance(_viTear->fireX, _viTear->fireY, _viTear->x, _viTear->y) < _viTear->z && !_viTear->isAngle) 
		{
			_viTear->gravity += 0.06f * 10;
			_viTear->sumg += _viTear->gravity;
			RENDERMANAGER->pushBackRenderInfo((_viTear->rc.bottom + _viTear->rc.top) / 2, _viTear->imageName, _viTear->rc.left,
				_viTear->rc.top - _viTear->z + _viTear->sumg, true);
		}else
		RENDERMANAGER->pushBackRenderInfo((_viTear->rc.bottom + _viTear->rc.top) / 2, _viTear->imageName, _viTear->rc.left,
			_viTear->rc.top - _viTear->z, true);

		RENDERMANAGER->pushBackRenderInfo((_viTear->rc.bottom + _viTear->rc.top) / 2, _viTear->shadowName,
			_viTear->rc.left, _viTear->rc.top, true, true, 150);

	}
}

void enemyTear::fire(float x, float y, float z, float angle, float speed, float range, float tearX, float tearY, int damage, float gravity, bool isAngle)
{
	tagTear tear;
	ZeroMemory(&tear, sizeof(tagTear));
	tear.tearImage = IMAGEMANAGER->findImage(_imageName);
	tear.tearShadow = IMAGEMANAGER->findImage(_tearShadow);
	tear.imageName = _imageName;
	tear.shadowName = _tearShadow;
	tear.speed = speed;
	tear.radius = tear.tearImage->getWidth() / 2;
	tear.x = tear.fireX = x;
	tear.y = tear.fireY = y;
	tear.z = z;
	tear.angle = angle;
	tear.range = range;
	tear.tearX = tearX;
	tear.tearY = tearY;
	tear.damage = damage;
	tear.gravity = gravity;
	tear.gravity2 = gravity;
	tear.shadowSize = tear.tearShadow->getHeight();
	tear.rc = RectMakeCenter(tear.x, tear.y, tear.tearImage->getWidth(), tear.shadowSize);
	tear.isAngle = isAngle;
	tear.sumg = 0;
	tear.sumg2 = 0;
	if (isAngle) 
	{
		tear.z = 0;
		tear.rndiz = RND->getFromFloatTo(5, 10);
	}
	_vTear.push_back(tear);
}

void enemyTear::move()
{
	for (_viTear = _vTear.begin(); _viTear != _vTear.end();)
	{
	
		if (_viTear->isAngle) 
		{
			_viTear->gravity += _viTear->tearY * 10;
			_viTear->sumg += _viTear->gravity;
			_viTear->z += _viTear->speed * 10;
			_viTear->z -= _viTear->sumg;
			_viTear->x += cosf(_viTear->angle) * (_viTear->tearX * 8) + _viTear->tearX;
			_viTear->y += -sinf(_viTear->angle) * (_viTear->tearX * 8) + _viTear->tearY;
			_viTear->rc = RectMakeCenter(_viTear->x, _viTear->y,
				_viTear->tearImage->getWidth(),
				_viTear->shadowSize);
			
			
		}
		else 
		{
			_viTear->x += cosf(_viTear->angle) * (_viTear->speed * 8) + _viTear->tearX;
			_viTear->y += -sinf(_viTear->angle) * (_viTear->speed * 8) + _viTear->tearY;

			_viTear->rc = RectMakeCenter(_viTear->x, _viTear->y,
				_viTear->tearImage->getWidth(),
				_viTear->shadowSize);
		}
		
		if (_viTear->z < 0)
		{

			EFFECTMANAGER->play("bloodteareffect3", _viTear->x, _viTear->y, (_viTear->rc.bottom + _viTear->rc.top) / 2);
			_viTear = _vTear.erase(_viTear);
		}else if (_viTear->range * 70 < getDistance(_viTear->x, _viTear->y, _viTear->fireX, _viTear->fireY))
		{

			EFFECTMANAGER->play("bloodteareffect3", _viTear->x, _viTear->y, (_viTear->rc.bottom + _viTear->rc.top) / 2);
			_viTear = _vTear.erase(_viTear);
		}
		else ++_viTear;

	
	}
}
