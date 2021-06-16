#include "stdafx.h"
#include "bossIntro.h"

HRESULT bossIntro::init()
{
	_settingFlag = false;
	_count = _ix = _iy = _tx = _ty = 0;
	IMAGEMANAGER->addImage("bossIntro", "image/ui/bgboss.bmp", WINSIZEX, WINSIZEY, false, RGB(0,0,0));
  
	return S_OK;
}

void bossIntro::release()
{
}

void bossIntro::update()
{
	if (!_settingFlag)
	{
		EFFECTMANAGER->stop();
		_ix = -40;
		_iy = DATAMANAGER->getIY();
		_tx = DATAMANAGER->getTX();
		_ty = DATAMANAGER->getTX();
		DATAMANAGER->setCamera(0, 0, 0, 0);
		_settingFlag = true;
	}
	
	moveCamera();
	if (_count >= 80) 
	{
		SCENEMANAGER->setScene("보스스테이지");
	}
}

void bossIntro::render()
{
	RENDERMANAGER->pushBackRenderInfo(999, "bossIntro", 0, 0);
	RENDERMANAGER->render(getMemDC());
}

void bossIntro::moveCameraSetting(float ix, float iy, float tx, float ty)
{
	_ix = ix;
	_iy = iy;
	_tx = tx;
	_ty = ty;
}

void bossIntro::moveCamera()
{
	// 아무 작업도 안함
	if (_ix == 0 && _iy == 0) return;
	if (0 > _ix)
	{
		RENDERMANAGER->setCameraX(RENDERMANAGER->getCameraX() + _ix);
		if (RENDERMANAGER->getCameraX() < _tx)
		{
			RENDERMANAGER->setCameraX(_tx);
			_count++;
		}
	}
	else
	{
		RENDERMANAGER->setCameraX(RENDERMANAGER->getCameraX() + _ix);
		if (RENDERMANAGER->getCameraX() > _tx)
		{
			RENDERMANAGER->setCameraX(_tx);
		}
	}
	if (0 > _iy)
	{
		RENDERMANAGER->setCameraY(RENDERMANAGER->getCameraY() + _iy);
		if (RENDERMANAGER->getCameraY() < _ty)
		{
			RENDERMANAGER->setCameraY(_ty);
		}
	}
	else
	{
		RENDERMANAGER->setCameraY(RENDERMANAGER->getCameraY() + _iy);
		if (RENDERMANAGER->getCameraY() > _ty)
		{
			RENDERMANAGER->setCameraY(_ty);
		}
	}
}
