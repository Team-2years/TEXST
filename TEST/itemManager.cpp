#include "stdafx.h"
#include "itemManager.h"

HRESULT itemManager::init()
{

	return S_OK;
}

void itemManager::release()
{
}

void itemManager::update(isaac* _isaac)
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _isaac->getChargebar() == _isaac->getChargebarMax() && _isaac->getIst() != STDEATH)
	{
		_isaac->setIst(STITEM);
		_isaac->setItemFrameCount(30);
		_isaac->setChargebar(0);
		activeItemEffect(_isaac->getSpaceItem());
		_spaceItem = true;
	}
	// 조건 E가 눌리고 폭탄이 1개 이상이고 아이작의 상태가 죽음이 아닐때
	if (KEYMANAGER->isOnceKeyDown('E') && _isaac->getBomb() > 0 && _isaac->getIst() != STDEATH) 
	{
		setSparkBomb(_isaac->getX(), _isaac->getY());
		_isaac->setBomb(_isaac->getBomb() - 1);
	}
	for (_viPick = _vPick.begin(); _viPick != _vPick.end(); ++_viPick)
	{
		(*_viPick)->update();
	}
	for (_viBomb = _vBomb.begin(); _viBomb != _vBomb.end(); ++_viBomb)
	{
		(*_viBomb)->update();
	}
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem)->update();
	}
	// 스페이스 아이템 사용시
	if (_isaac->getItemFrameCount() > 0 && _spaceItem)
	{
		RENDERMANAGER->pushBackRenderInfo(_isaac->getMiddle()+1, _isaac->getSpaceItem(), _isaac->getRect().left - 15, _isaac->getRect().top - 95);
		if (_isaac->getItemFrameCount() == 1)
		_spaceItem = false;
	}
}

void itemManager::render()
{
	for (_viPick = _vPick.begin(); _viPick != _vPick.end(); ++_viPick)
	{
		(*_viPick)->render();
	}
	for (_viBomb = _vBomb.begin(); _viBomb != _vBomb.end(); ++_viBomb)
	{
		(*_viBomb)->render();
	}
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem)->render();
	}
}

// 픽업 아이템 충돌 처리
void itemManager::isPickCollision(isaac* _isaac )
{
	for (_viPick = _vPick.begin(); _viPick != _vPick.end();)
	{
		RECT _rc1 = _isaac->getRect();
		RECT _rc2 = (*_viPick)->getRect();
		if (IntersectRect(&_temp, &_rc1, &_rc2))
		{
			switch ((*_viPick)->getPickUpType())
			{
			case PCOIN:
				_isaac->setCoin(_isaac->getCoin() + 1);
				EFFECTMANAGER->play("coin1effect", (*_viPick)->getRect().right - 17, (*_viPick)->getRect().top + 4, ((*_viPick)->getRect().top + (*_viPick)->getRect().bottom) / 2);
				_viPick = _vPick.erase(_viPick);
				break;
			case PBOMB:
				_isaac->setBomb(_isaac->getBomb() + 1);
				EFFECTMANAGER->play("coin1effect", (*_viPick)->getRect().right - 17, (*_viPick)->getRect().top, ((*_viPick)->getRect().top + (*_viPick)->getRect().bottom) / 2);
				_viPick = _vPick.erase(_viPick);
				break;
			case PKEY:
				_isaac->setKey(_isaac->getKey() + 1);
				EFFECTMANAGER->play("coin1effect", (*_viPick)->getRect().right - 10, (*_viPick)->getRect().top, ((*_viPick)->getRect().top + (*_viPick)->getRect().bottom) / 2);
				_viPick = _vPick.erase(_viPick);
				break;
			case PHEART:
				if (_isaac->getMaxHeart() == _isaac->getHeart()) 
				{
					++_viPick;
				}
				else 
				{
					_isaac->setHeart(_isaac->getHeart() + 2);
					if(_isaac->getMaxHeart() < _isaac->getHeart())
						_isaac->setHeart(_isaac->getMaxHeart());

					EFFECTMANAGER->play("coin1effect", (*_viPick)->getRect().right - 15, (*_viPick)->getRect().top, ((*_viPick)->getRect().top + (*_viPick)->getRect().bottom) / 2);
					_viPick = _vPick.erase(_viPick);
				}
				break;
			
			default:
				_viPick = _vPick.erase(_viPick);
				break;
			}
		}
		else 
		{
			++_viPick;
		}
	}
}

void itemManager::isItemCollision(isaac* _isaac)
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		RECT _rc1 = _isaac->getRect();
		RECT _rc2 = (*_viItem)->getRect();
		if (IntersectRect(&_temp, &_rc1, &_rc2))
		{
			if (_temp.right - _temp.left > _temp.bottom - _temp.top) // 위충돌 
			{
				if (_rc1.top < _rc2.top)
				{
					_isaac->setY(_isaac->getY() - (_temp.bottom - _temp.top));
				}
				else 
				{
					_isaac->setY(_isaac->getY() + (_temp.bottom - _temp.top));
				}
			}
			else // 옆 충돌
			{
				if (_rc1.left < _rc2.left) 
				{
					_isaac->setX(_isaac->getX() - (_temp.right - _temp.left));
				}
				else
				{
					_isaac->setX(_isaac->getX() + (_temp.right - _temp.left));
				}
			}
			if ((*_viItem)->getIv() != EMPTY) 
			{
				EFFECTMANAGER->play("item_poof", (*_viItem)->getX(), (*_viItem)->getY() - 60, (*_viItem)->getMiddle() + 1);

				_isaac->setIst(STITEM);
				_isaac->setItemFrameCount(30);
				(*_viItem)->setItemFrameCount(30);
				switch ((*_viItem)->getIv())
				{
				case PASSIVE:
					if ((*_viItem)->getItemName() == "cricketshead") 
					{
						_isaac->setDamage(_isaac->getDamage() * 1.5);
						_isaac->setCricketshead();
					}
					if ((*_viItem)->getItemName() == "onion")
					{
						_isaac->setTear(_isaac->getTear() + 0.5);
						_isaac->setOnion(true);
					}
					if ((*_viItem)->getItemName() == "breakfast") 
					{
						_isaac->setMaxHeart(_isaac->getMaxHeart() + 2);
						_isaac->setHeart(_isaac->getHeart() + 5);
						if (_isaac->getMaxHeart() < _isaac->getHeart())
							_isaac->setHeart(_isaac->getMaxHeart());
					}
					if ((*_viItem)->getItemName() == "dessert")
					{
						_isaac->setMaxHeart(_isaac->getMaxHeart() + 2);
						_isaac->setHeart(_isaac->getHeart() + 5);
						if (_isaac->getMaxHeart() < _isaac->getHeart())
							_isaac->setHeart(_isaac->getMaxHeart());
					}
					if ((*_viItem)->getItemName() == "dinner")
					{
						_isaac->setMaxHeart(_isaac->getMaxHeart() + 2);
						_isaac->setHeart(_isaac->getHeart() + 4);
						if (_isaac->getMaxHeart() < _isaac->getHeart())
							_isaac->setHeart(_isaac->getMaxHeart());
					}
					if ((*_viItem)->getItemName() == "lunch")
					{
						_isaac->setMaxHeart(_isaac->getMaxHeart() + 2);
						_isaac->setHeart(_isaac->getHeart() + 5);
						if (_isaac->getMaxHeart() < _isaac->getHeart())
							_isaac->setHeart(_isaac->getMaxHeart());
					}
					if ((*_viItem)->getItemName() == "rottenmeat")
					{
						_isaac->setMaxHeart(_isaac->getMaxHeart() + 2);
						_isaac->setHeart(_isaac->getHeart() + 4);
						if (_isaac->getMaxHeart() < _isaac->getHeart())
							_isaac->setHeart(_isaac->getMaxHeart());
					}
					if ((*_viItem)->getItemName() == "theinnereye") 
					{
						_isaac->setTear(_isaac->getTear() - 0.7);
						DATAMANAGER->setInnerEye(true);
					}
					if ((*_viItem)->getItemName() == "lokishorns")
					{
						DATAMANAGER->setLokisHorns(true);
					}
					if ((*_viItem)->getItemName() == "wirecoathanger")
					{
						_isaac->setTear(_isaac->getTear() + 0.5);
						DATAMANAGER->setWireHanger(true);

					}
					if ((*_viItem)->getItemName() == "jesusjuice") 
					{
						_isaac->setDamage(_isaac->getDamage() + 0.5);
						_isaac->setRange(_isaac->getRange() + 0.38);
						DATAMANAGER->setJesusJuice(true);
					} 
					if ((*_viItem)->getItemName() == "mutantspider") 
					{
						_isaac->setTear(_isaac->getTear() - 1.4);
						DATAMANAGER->setMutantSpider(true);
					}
					if ((*_viItem)->getItemName() == "halo")
					{
						_isaac->setMaxHeart(_isaac->getMaxHeart() + 2);
						_isaac->setHeart(_isaac->getHeart() + 2);
						_isaac->setTear(_isaac->getTear() + 0.2);
						_isaac->setDamage(_isaac->getDamage() + 0.3);
						_isaac->setRange(_isaac->getRange() + 0.38);
						_isaac->setSpeed(_isaac->getSpeed() + 0.1);
						_isaac->setShotspeed(_isaac->getShotspeed() + 0.1);
						DATAMANAGER->setHalo(true);
					}
					break;
				case ACTIVE:
					break;
				default:
					break;
				}
				(*_viItem)->setIv(EMPTY); 
				
			}
		}
		if ((*_viItem)->getIfc() > 0)
		{
			(RENDERMANAGER->pushBackRenderInfo(_isaac->getMiddle()+1, (*_viItem)->getItemName(), _rc1.left - 10, _rc1.top - 100 - (10 - (*_viItem)->getIfc()*0.5)));
		}
	}
}

void itemManager::activeItemEffect(const char* itemName)
{
	if (itemName == "dice") 
	{
		for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
		{
			// 아이템이 비어 있지 않고 존재 한다면 돌린다는 얘기
			if ((*_viItem)->getIv() != EMPTY)
			{
				item* _item = new item();
				int x = (*_viItem)->getX();
				int y = (*_viItem)->getY();
				int rndNum = RND->getFromIntTo(0, 13);
				switch (rndNum)
				{
				case 0:
					_item->init("cricketshead", x, y, PASSIVE);
					break;
				case 1:
					_item->init("onion", x, y, PASSIVE);
					break;
				case 2:
					_item->init("breakfast", x, y, PASSIVE);
					break;
				case 3:
					_item->init("dessert", x, y, PASSIVE);
					break;
				case 4:
					_item->init("dinner", x, y, PASSIVE);
					break;
				case 5:
					_item->init("lunch", x, y, PASSIVE);
					break;
				case 6:
					_item->init("rottenmeat", x, y, PASSIVE);
					break;
				default:
				case 7:
					_item->init("theinnereye", x, y, PASSIVE);
					break;
				case 8:
					_item->init("lokishorns", x, y, PASSIVE);
					break;
				case 9:
					_item->init("wirecoathanger", x, y, PASSIVE);
					break;
				case 10:
					_item->init("jesusjuice", x, y, PASSIVE);
					break;
				case 11:
					_item->init("mutantspider", x, y, PASSIVE);
					break;
				case 12:
					_item->init("halo", x, y, PASSIVE);
					break;
				}
				EFFECTMANAGER->play("poof_large", x, y - 60, (*_viItem)->getMiddle() + 1);
				(*_viItem) = _item;
			}
		}
	}
}

// 동전 설치
void itemManager::setCoin(int x, int y)
{
	x = 204 + 28 + x * 56;
	y = 208 + 24 + y * 56;
	pickUpItem* _coin = new coin();
	_coin->init(x, y);
	_vPick.push_back(_coin);
}
// 폭탄 설치
void itemManager::setBomb(int x, int y)
{
	x = 204 + 28 + x * 56;
	y = 208 + 24 + y * 56;
	pickUpItem* _bomb = new bomb();
	_bomb->init(x, y);
	_vPick.push_back(_bomb);
}
// 열쇠 설치
void itemManager::setKey(int x, int y)
{
	x = 204 + 28 + x * 56;
	y = 208 + 24 + y * 56;
	pickUpItem* _key = new key();
	_key->init(x, y);
	_vPick.push_back(_key);
}
// 하트 설치
void itemManager::setHeart(int x, int y)
{
	x = 204 + 28 + x * 56;
	y = 208 + 24 + y * 56;
	pickUpItem* _heart = new heart();
	_heart->init(x, y);
	_vPick.push_back(_heart);
}
// 아이템 설치
void itemManager::setItem(const char* itemName, int x, int y, itemVal iv)
{
	x = 204 + 28 + x * 56;
	y = 208 + 24 + y * 56;
	item* _item = new item();
	_item->init(itemName, x, y, iv);
	_vItem.push_back(_item);
}

void itemManager::setItem(int x, int y)
{
	x = 204 + 28 + x * 56;
	y = 208 + 24 + y * 56;
	item* _item = new item();
	
	int rndNum = RND->getFromIntTo(0, 13);
	switch (rndNum)
	{
	case 0:
		_item->init("cricketshead", x, y, PASSIVE);
		break;
	case 1:
		_item->init("onion", x, y, PASSIVE);
		break;
	case 2:
		_item->init("breakfast", x, y, PASSIVE);
		break;
	case 3:
		_item->init("dessert", x, y, PASSIVE);
		break;
	case 4:
		_item->init("dinner", x, y, PASSIVE);
		break;
	case 5:
		_item->init("lunch", x, y, PASSIVE);
		break;
	case 6:
		_item->init("rottenmeat", x, y, PASSIVE);
		break;
	case 7:
		_item->init("theinnereye", x, y, PASSIVE);
		break;
	case 8:
		_item->init("lokishorns", x, y, PASSIVE);
		break;
	case 9:
		_item->init("wirecoathanger", x, y, PASSIVE);
		break;
	case 10:
		_item->init("jesusjuice", x, y, PASSIVE);
		break;
	case 11:
		_item->init("mutantspider", x, y, PASSIVE);
		break;
	case 12:
		_item->init("halo", x, y, PASSIVE);
		break;
	default:
		break;
	}
	_vItem.push_back(_item);
}

void itemManager::setSparkBomb(int x, int y)
{
	pickUpItem* _sparkBomb = new sparkBomb();
	_sparkBomb->init(x, y);
	_vBomb.push_back(_sparkBomb);
}

