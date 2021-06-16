#include "stdafx.h"
#include "gameUI.h"

gameUI::gameUI()
{
}

gameUI::~gameUI()
{
}

HRESULT gameUI::init()
{
	

	IMAGEMANAGER->addFrameImage("heartUI", "image/ui/heartUI.bmp", 90, 30, 3, 1, true, RGB(255, 0, 255), true);
	_heartUI = IMAGEMANAGER->findImage("heartUI");
	IMAGEMANAGER->addFrameImage("chargebarUI", "image/ui/chargebarUI.bmp", 160, 128, 5, 2, true, RGB(255, 0, 255), true);
	_chargebarUI = IMAGEMANAGER->findImage("chargebarUI");
	IMAGEMANAGER->addFrameImage("pickupitemIcon", "image/ui/pickupitemIcon.bmp", 96, 32, 3, 1, true, RGB(255,0,255), true);
	_pickUpItemIcon = IMAGEMANAGER->findImage("pickupitemIcon");
	IMAGEMANAGER->addFrameImage("statIcon", "image/ui/statIcon.bmp", 128, 128, 4, 4, true, RGB(255, 0, 255), true);
	_statIcon = IMAGEMANAGER->findImage("statIcon");
	IMAGEMANAGER->addFrameImage("number", "image/ui/number.bmp",90, 11, 10, 1, true, RGB(255, 0, 255), true);
	_number = IMAGEMANAGER->findImage("number");
	IMAGEMANAGER->addImage("dot", "image/ui/dot.bmp", 6, 6, true, RGB(255, 0, 255), true);
	_dot = IMAGEMANAGER->findImage("dot");
	IMAGEMANAGER->addImage("chargeGreen", "image/ui/chargeGreen.bmp", 12, 46, true, RGB(255, 0, 255));
	_chargeGreen = IMAGEMANAGER->findImage("chargeGreen");
	IMAGEMANAGER->addImage("deathUI", "image/ui/deathUI.bmp", 408, 472, true, RGB(255, 0, 255));
	_deathUI = IMAGEMANAGER->findImage("deathUI");
	_deathCount = 0;
	IMAGEMANAGER->addImage("HpBarBottom", "image/ui/hpBarBottom.bmp", 300, 64, true, RGB(255, 0, 255));
	_progressBarBottom = IMAGEMANAGER->findImage("HpBarBottom");
	IMAGEMANAGER->addImage("HpBarTop", "image/ui/hpBarTop.bmp", 220, 16, true, RGB(255, 0, 255));
	_progressBarTop = IMAGEMANAGER->findImage("HpBarTop");
	return S_OK;
}

void gameUI::release()
{
}

void gameUI::update()
{
}

void gameUI::render()
{
	heartRender();
	chargedbarRender();
	pickUpItemRender();
	statRender();
	spaceItemRender();
	if (DATAMANAGER->getHeart() <= 0) 
	{
		deathUIRender();
	}
	bossHeath();
}

void gameUI::heartRender()
{
	int currentHeart = DATAMANAGER->getHeart();
	int maxHeart = DATAMANAGER->getMaxHeart();
	for (int i = maxHeart; i > 0; i -= 2)
	{
		if (currentHeart >= 2) 
		{
			_heartUI->frameRender(getMemDC(), 100 + (maxHeart - i) * 13, 20, 0, 0);
			currentHeart -= 2;
		}
		else if (currentHeart >= 1) 
		{
			_heartUI->frameRender(getMemDC(), 100 + (maxHeart - i) * 13, 20, 1, 0);
			currentHeart -= 1;
		}
		else 
		{
			_heartUI->frameRender(getMemDC(), 100 + (maxHeart - i) * 13, 20, 2, 0);
		}
	}
}

void gameUI::chargedbarRender()
{
	int chargebar = DATAMANAGER->getChargebar();
	int chargebarMax = DATAMANAGER->getChargebarMax();
	_chargebarUI->frameRender(getMemDC(), 70, 10, 0, 0);
	_chargeGreen->render(getMemDC(), 70 + 8, 14 + (_chargeGreen->getHeight()+2)/chargebarMax * (chargebarMax - chargebar), 0, _chargeGreen->getHeight() - _chargeGreen->getHeight() * chargebar / chargebarMax, _chargeGreen->getWidth(), _chargeGreen->getHeight() * chargebar / chargebarMax);
	switch (chargebarMax)
	{
	case 6:
		_chargebarUI->frameRender(getMemDC(), 70, 10, 3, 0);
	default:
		break;
	}
	
}

void gameUI::pickUpItemRender()
{
	int coin = DATAMANAGER->getCoin();
	int bomb = DATAMANAGER->getBomb();
	int key = DATAMANAGER->getKey();
	_pickUpItemIcon->frameRender(getMemDC(), 10, 150, 0, 0);
	_number->frameRender(getMemDC(), 40, 160, coin / 10, 0);
	_number->frameRender(getMemDC(), 47, 160, coin % 10 ,0);
	_pickUpItemIcon->frameRender(getMemDC(), 10, 182, 1, 0);
	_number->frameRender(getMemDC(), 40, 192, bomb / 10, 0);
	_number->frameRender(getMemDC(), 47, 192, bomb % 10, 0);
	_pickUpItemIcon->frameRender(getMemDC(), 10, 214, 2, 0);
	_number->frameRender(getMemDC(), 40, 224, key / 10, 0);
	_number->frameRender(getMemDC(), 47, 224, key % 10, 0);

}

void gameUI::statRender()
{
	int damage = DATAMANAGER->getDamage() * 100;
	int speed = DATAMANAGER->getSpeed() * 100;
	int tear = DATAMANAGER->getTear() * 100;
	int range = DATAMANAGER->getRange() * 100;
	int shotspeed = DATAMANAGER->getShotspeed() * 100;
	//공격력
	_statIcon->frameRender(getMemDC(), 10, 246, 0, 0);
	_number->frameRender(getMemDC(), 40, 256, damage / 100, 0);
	_number->frameRender(getMemDC(), 50, 256, (damage - damage / 100 * 100) / 10, 0);
	_dot->render(getMemDC(), 47, 262);
	_number->frameRender(getMemDC(), 57, 256, damage % 10, 0);
	//스피드
	_statIcon->frameRender(getMemDC(), 10, 278, 1, 0);
	_number->frameRender(getMemDC(), 40, 288, speed / 100, 0);
	_number->frameRender(getMemDC(), 50, 288, (speed - speed / 100 * 100) / 10, 0);
	_dot->render(getMemDC(), 47, 294);
	_number->frameRender(getMemDC(), 57, 288, speed % 10, 0);
	//티어
	_statIcon->frameRender(getMemDC(), 10, 310, 2, 0);
	_number->frameRender(getMemDC(), 40, 320, tear / 100, 0);
	_number->frameRender(getMemDC(), 50, 320, (tear - tear / 100 * 100) / 10, 0);
	_dot->render(getMemDC(), 47, 326);
	_number->frameRender(getMemDC(), 57, 320, tear % 10, 0);
	//사거리
	_statIcon->frameRender(getMemDC(), 10, 342, 0, 1);
	_number->frameRender(getMemDC(), 40, 348, range / 100, 0);
	_number->frameRender(getMemDC(), 50, 348, (range - range / 100 * 100) / 10, 0);
	_dot->render(getMemDC(), 47, 354);
	_number->frameRender(getMemDC(), 57, 348, range % 10, 0);
	//샷스피드
	_statIcon->frameRender(getMemDC(), 10, 374, 1, 1);
	_number->frameRender(getMemDC(), 40, 384, shotspeed / 100, 0);
	_number->frameRender(getMemDC(), 50, 384, (shotspeed - shotspeed / 100 * 100) / 10, 0);
	_dot->render(getMemDC(), 47, 390);
	_number->frameRender(getMemDC(), 57, 384, shotspeed % 10, 0);
}

void gameUI::spaceItemRender()
{
	if(DATAMANAGER->getSpaceItem() != "empty")
	IMAGEMANAGER->findImage(DATAMANAGER->getSpaceItem())->render(getMemDC(), 10, 5);
}

void gameUI::deathUIRender()
{
	_deathCount++;
	if (_deathCount > 80)
	_deathUI->render(getMemDC(), WINSIZEX/2 - _deathUI->getWidth()/2, WINSIZEY/2 - _deathUI->getHeight() / 2);
}

void gameUI::bossHeath()
{
	if (DATAMANAGER->getBossHp() > 0)
	{
		float width = (DATAMANAGER->getBossHp() / DATAMANAGER->getMaxBossHp()) * _progressBarTop->getWidth();
		_progressBarBottom->render(getMemDC(), WINSIZEX/2  - _progressBarBottom->getWidth()/2 , WINSIZEY - 72);
		_progressBarTop->render(getMemDC(), WINSIZEX / 2 - _progressBarTop->getWidth() / 2, WINSIZEY - 50, 0, 0, width, _progressBarTop->getHeight());
	}
}
