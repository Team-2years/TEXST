#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init()
{
	return S_OK;
}

HRESULT enemy::init(POINT position)
{
	return E_NOTIMPL;
}

void enemy::release()
{
}

void enemy::update()
{
}

void enemy::render()
{
}

void enemy::move()
{
}

void enemy::draw()
{
}

bool enemy::patternCount()
{
	_rndCount++;
	if (_rndCount % _rndFireCount == 0)
	{
		_rndCount = 0;
		return true;
	}
	return false;
}
