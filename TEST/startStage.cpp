#include "stdafx.h"
#include "startStage.h"

startStage::startStage()
{
	init();
}

startStage::~startStage()
{

}

HRESULT startStage::init()
{
	_deathCount = 0;
	_settingFlag = true;
	_increaseX = 0;
	_increaseY = 0;
	_targetX = 0;
	_targetY = 0;
	RENDERMANAGER->setCameraX(0);
	RENDERMANAGER->setCameraY(0);
	_isClear = false;
	IMAGEMANAGER->addImage("stage1", "image/stage/stage1.bmp", 936, 614, true, RGB(255, 0, 255));
	CAMERAMANAGER->init(WINSIZEX * 3, WINSIZEY * 3);
	_bgBlack = IMAGEMANAGER->findImage("검은배경");
	_isaac = new isaac;
	_isaac->init();
	_gameUI = new gameUI;
	_gameUI->init();
	_gameUI->updateIsaac(_isaac);
	_fadeCount = 0;
	_middleValX = WINSIZEX / 2 - IMAGEMANAGER->findImage("stage1")->getWidth() / 2;
	_middleValY = WINSIZEY / 2 - IMAGEMANAGER->findImage("stage1")->getHeight() / 2;
	// 에너미 초기화
	_enemyManager = new enemyManager;
	_itemManager = new itemManager;
	_enemyManager->init();
	_grid = new grid;
	_grid->makeWall(_middleValX, _middleValY);
	_grid->makeDoor(_middleValX, _middleValY);
	_grid->makeGrid(_middleValX, _middleValY);
	_doorCount = 0;


	//_enemyManager->setEnemy(CLOTTY, 5, 5);

	//_enemyManager->setEnemy(CLOTTY, 4, 5);
	//_enemyManager->setEnemy(CLOTTY, 3, 5);
	//_enemyManager->setEnemy(CLOTTY, 2, 5);
	//_enemyManager->setEnemy(MONSTRO, 12, 3);
	//_enemyManager->setEnemy(DIP, 4, 5);
	//_enemyManager->setEnemy(DIP, 4, 5);
	//_enemyManager->setEnemy(DIP, 4, 5);
	//_enemyManager->setEnemy(DIP, 4, 5);
	//_enemyManager->setEnemy(DIP, 4, 5);
	//_enemyManager->setEnemy(SUCKER, 6, 4);
	//_enemyManager->setEnemy(SUCKER, 8, 3);
	//_enemyManager->setEnemy(SUCKER, 4, 2);  
	//_enemyManager->setEnemy(SUCKER, 6, 4);
	//_enemyManager->setEnemy(HORF, 4, 5);
	//_enemyManager->setEnemy(HORF, 4, 4);
	//_enemyManager->setEnemy(HORF, 4, 3);



	// 아이템 매니져 초기화

	///*_itemManager->setCoin(3, 0);
	//_itemManager->setCoin(4, 0);
	//_itemManager->setBomb(5, 0);
	//_itemManager->setKey(6, 0);
	//_itemManager->setHeart(7, 0);
	_itemManager->setItem(0, 6);
	_itemManager->setItem(1, 6);
	_itemManager->setItem(2, 6);
	_itemManager->setItem(3, 6);
	_itemManager->setItem(4, 6);
	_itemManager->setItem(5, 6);
	_itemManager->setItem(6, 6);
	_itemManager->setItem(7, 6);
	_itemManager->setItem(8, 6);
	_itemManager->setItem(9, 6);
	//_itemManager->setItem(3, 6);*/
	////_itemManager->setItem("onion", 800, 400, PASSIVE);
	
	/*_grid->makeRocks(0, 0, 2, 2);
	_grid->makeRock(6, 5);*/
	_wall = _grid->getWall();
	_door = _grid->getDoor();
	_tgrid = _grid->getGrid();
	_door[0].gridv = GRIDEMPTY;
	_door[1].gridv = GRIDEMPTY;
	_door[2].gridv = GRIDEMPTY;
	for (int i = 0; i < 4; i++)
	{
		_door[i].isOpen = false;
	}
	return S_OK;
}

void startStage::release()
{
}

void startStage::update()
{
	if (!_settingFlag)
	{
		_vTear->clear();
		EFFECTMANAGER->stop();
		_isaac->init();
		_isaac->setMaxHeart(DATAMANAGER->getMaxHeart());
		_isaac->setHeart(DATAMANAGER->getHeart());
		_isaac->setRange(DATAMANAGER->getRange());
		_isaac->setSpeed(DATAMANAGER->getSpeed());
		_isaac->setTear(DATAMANAGER->getTear());
		_isaac->setShotspeed(DATAMANAGER->getShotspeed());
		_isaac->setDamage(DATAMANAGER->getDamage());
		_isaac->setChargebarMax(DATAMANAGER->getChargebarMax());
		_isaac->setChargebar(DATAMANAGER->getChargebar());
		_isaac->setCoin(DATAMANAGER->getCoin());
		_isaac->setBomb(DATAMANAGER->getBomb());
		_isaac->setKey(DATAMANAGER->getKey());
		_isaac->setSpaceItem(DATAMANAGER->getSpaceItem());
		_isaac->setX(DATAMANAGER->getX());
		_isaac->setY(DATAMANAGER->getY());
		_isaac->setSecond(DATAMANAGER->getSecond());
		_isaac->setTearName(DATAMANAGER->getTearName());
		_isaac->setHeadKey(DATAMANAGER->getIsaacHead());
		_isaac->setOnion(DATAMANAGER->getOnion());
		_isaac->setLastTearKey(DATAMANAGER->getLastTearKey());

		_increaseX = DATAMANAGER->getIX();
		_increaseY = DATAMANAGER->getIY();
		_targetX = DATAMANAGER->getTX();
		_targetY = DATAMANAGER->getTX();
		_settingFlag = true;
	}
	// 죽으면 티어 벡터 초기화
	if (_isaac->getIst() == STDEATH) {
		_vTear->clear();
		_vTear->resize(0);
	}
	// 아이템 매니저 업데이트
	_itemManager->update(_isaac);
	_vBomb = _itemManager->getVBomb();
	// 애너미 매니저 업데이트
	_enemyManager->update(_isaac);
	// 적 눈물 업데이트
	_vETear = _enemyManager->getVTear();
	// 적 벡터 업데이트
	_vEnemy = _enemyManager->getVEnemy();
	// 아이작 업데이트
	_isaac->update();
	// 아이작 눈물 벡터
	_vTear = _isaac->getVTear();
	// 눈물과 적의 충돌
	EnemyTearCollision();
	// 아이작과 적에 대한 충돌 처리 
	isaacEnemyCollision();
	// 픽업아이템 충돌처리
	_itemManager->isPickCollision(_isaac);
	// 아이템 충돌 처리
	_itemManager->isItemCollision(_isaac);
	// 페이드 인
	if (_fadeCount < 255)
	{
		_fadeCount += 5;
	}


	_gameUI->updateIsaac(_isaac);
	// 폭탄이 있을때만 
	if (!_vBomb->empty())
		bombCollision();
	wallCollision();
	gridCollision();
	doorCollision();
	tearWallCollision();
	EnemyDead();
	// 적이 없고 클리어 상태가 아니라면 스테이지 클리어
	if (_vEnemy->empty() && !_isClear) {
		stageClear();
	}
	EFFECTMANAGER->update();
	// 카메라 움직임
	moveCamera();
	// 클리어 상태라면 문열림 밑 문이동 준비 완료
	if (_isClear)
	doorMove();
	DATAMANAGER->updateIsaacData
	(
		_isaac->getMaxHeart(),
		_isaac->getHeart(),
		_isaac->getRange(),
		_isaac->getSpeed(),
		_isaac->getTear(),
		_isaac->getShotspeed(),
		_isaac->getDamage(),
		_isaac->getChargebarMax(),
		_isaac->getChargebar(),
		_isaac->getCoin(),
		_isaac->getBomb(),
		_isaac->getKey(),
		_isaac->getSpaceItem(),
		_isaac->getLastTearKey(),
		_isaac->getX(),
		_isaac->getY(),
		_isaac->getSecond(),
		_isaac->getTearName(),
		_isaac->getIsaacHead(),
		_isaac->getOnion()
	);
}

void startStage::render()
{

	EFFECTMANAGER->render();
	if (KEYMANAGER->isToggleKey('P'))
	{
	}
	else
	RENDERMANAGER->pushBackRenderInfo(-999, "stage1", _middleValX, _middleValY);
	//	IMAGEMANAGER->findImage("stage1")->render(getMemDC(), _middleValX, _middleValY);
	_grid->render();
	_itemManager->render();
	_enemyManager->render();
	_isaac->render();

	RENDERMANAGER->render(getMemDC());
	_gameUI->render();
	_bgBlack->alphaRender(getMemDC(), 255 - _fadeCount);

}

// 벽충돌
void startStage::wallCollision()
{
	for (int i = 0; i < 12; i++)
	{
		RECT rc = _isaac->getRect();
		if (IntersectRect(&_temp, &rc, &_wall[i].rc))
		{
			if (_temp.bottom - _temp.top > _temp.right - _temp.left) // 옆
			{
				if (rc.left < _wall[i].rc.left)
				{
					_isaac->setX(_isaac->getX() - (_temp.right - _temp.left));
				}
				else
				{
					_isaac->setX(_isaac->getX() + (_temp.right - _temp.left));
				}
			}
			else // 위 아래
			{
				if (rc.top < _wall[i].rc.top)
				{
					_isaac->setY(_isaac->getY() - (_temp.bottom - _temp.top));
				}
				else
				{
					_isaac->setY(_isaac->getY() + (_temp.bottom - _temp.top));
				}
			}
			_isaac->setRect(RectMakeCenter(_isaac->getX(), _isaac->getY(), 40, 10));
			// 추가적인 보정 필요 //
		}
	}

}

// 그리드 충돌
void startStage::gridCollision()
{
	for (int i = 0; i < MAX_GRID; i++)
	{
		switch (_tgrid[i].gridv)
		{
		case GRIDEMPTY:
			break;
		case GRIDROCK:
			RECT rc = _isaac->getRect();
			if (IntersectRect(&_temp, &rc, &_tgrid[i].rc))
			{
				if (_temp.bottom - _temp.top > _temp.right - _temp.left) // 옆
				{
					if (rc.left < _tgrid[i].rc.left)
					{
						_isaac->setX(_isaac->getX() - (_temp.right - _temp.left));
					}
					else
					{
						_isaac->setX(_isaac->getX() + (_temp.right - _temp.left));
					}
				}
				else // 위 아래
				{
					if (rc.top < _tgrid[i].rc.top)
					{
						_isaac->setY(_isaac->getY() - (_temp.bottom - _temp.top));
					}
					else
					{
						_isaac->setY(_isaac->getY() + (_temp.bottom - _temp.top));
					}
				}
				_isaac->setRect(RectMakeCenter(_isaac->getX(), _isaac->getY(), 40, 10));
			}
			// 적 충돌
			for (_viEnemy = _vEnemy->begin(); _viEnemy != _vEnemy->end(); ++_viEnemy)
			{
				rc = (*_viEnemy)->getRect();
				switch ((*_viEnemy)->getEnemyType())
				{
				case CLOTTY:
				case DIP:
					if (IntersectRect(&_temp, &rc, &_tgrid[i].rc))
					{
						if (_temp.bottom - _temp.top > _temp.right - _temp.left) // 옆
						{
							if (rc.left < _tgrid[i].rc.left)
							{
								(*_viEnemy)->setX((*_viEnemy)->getX() - (_temp.right - _temp.left));
							}
							else
							{
								(*_viEnemy)->setX((*_viEnemy)->getX() + (_temp.right - _temp.left));
							}
						}
						else // 위 아래
						{
							if (rc.top < _tgrid[i].rc.top)
							{
								(*_viEnemy)->setY((*_viEnemy)->getY() - (_temp.bottom - _temp.top));
							}
							else
							{
								(*_viEnemy)->setY((*_viEnemy)->getY() + (_temp.bottom - _temp.top));
							}
						}
						switch ((*_viEnemy)->getEnemyType())
						{
						case CLOTTY:
							(*_viEnemy)->setRect(RectMakeCenter((*_viEnemy)->getX(), (*_viEnemy)->getY() + 30, 140 - 65, 140 - 110));
							break;
						case DIP:
							if (_temp.bottom - _temp.top > _temp.right - _temp.left) // 옆
							{
								if (rc.left < _tgrid[i].rc.left) // 왼
								{
									(*_viEnemy)->setAngle(PI - (*_viEnemy)->getAngle());
								}
								else // 오
								{
									(*_viEnemy)->setAngle(PI - (*_viEnemy)->getAngle());
								}
							}
							else // 위 아래
							{
								if (rc.top < _tgrid[i].rc.top)
								{
									(*_viEnemy)->setAngle(PI2 - (*_viEnemy)->getAngle());
								}
								else
								{
									(*_viEnemy)->setAngle(PI2 - (*_viEnemy)->getAngle());
								}
							}
							(*_viEnemy)->setRect(RectMakeCenter((*_viEnemy)->getX(), (*_viEnemy)->getY() + 15, IMAGEMANAGER->findImage("dip")->getFrameWidth() - 8, IMAGEMANAGER->findImage("dip")->getFrameHeight() - 40));
							break;
						case HORF:
							break;
						case SUCKER:
							break;
						default:
							break;
						}
					}

					break;
				case HORF:
					break;
				case SUCKER:
					break;
				default:
					break;
				}
			}

			// 눈 물 충돌
			for (_viTear = _vTear->begin(); _viTear != _vTear->end(); )
			{
				if (IntersectRect(&_temp, &_tgrid[i].rc, &_viTear->rc))
				{

					if (_viTear->range * 70 - 100 < getDistance(_viTear->x, _viTear->y, _viTear->fireX, _viTear->fireY))
					{
						float dis = getDistance(_viTear->x, _viTear->y, _viTear->fireX, _viTear->fireY) - _viTear->range * 70;
						EFFECTMANAGER->play("teareffect7", _viTear->x, _viTear->y + dis * 0.5, (_viTear->rc.bottom + _viTear->rc.top) / 2);
					}
					else
						EFFECTMANAGER->play("teareffect7", _viTear->x, _viTear->y - 50, (_viTear->rc.bottom + _viTear->rc.top) / 2);
					_viTear = _vTear->erase(_viTear);

				}
				else
				{
					++_viTear;
				}
			}

			for (_viETear = _vETear->begin(); _viETear != _vETear->end(); )
			{
				if (IntersectRect(&_temp, &_tgrid[i].rc, &_viETear->rc))
				{

					if (_viETear->range * 70 - getDistance(_viETear->fireX, _viETear->fireY, _viETear->x, _viETear->y) < _viETear->z)
					{
						EFFECTMANAGER->play("bloodteareffect3", _viETear->x, _viETear->y - _viETear->z + _viETear->sumg, (_viETear->rc.bottom + _viETear->rc.top) / 2);
					}
					else
						EFFECTMANAGER->play("bloodteareffect3", _viETear->x, _viETear->y - _viETear->z, (_viETear->rc.bottom + _viETear->rc.top) / 2);
					_viETear = _vETear->erase(_viETear);
				}
				else
				{
					++_viETear;
				}
			}
			break;
		case GRIDPOT:
			break;
		case GRIDPOOP:
			break;
		default:
			break;
		}
	}
}

// 벽과 아이작 몬스터 충돌
void startStage::doorCollision()
{
	for (int i = 0; i < 4; i++)
	{
		RECT rc;
		switch (_door[i].gridv)
		{
		case GRIDEMPTY:
			rc = _isaac->getRect();
			if (IntersectRect(&_temp, &rc, &_door[i].rc))
			{
				if (_temp.bottom - _temp.top > _temp.right - _temp.left) // 옆
				{
					if (rc.left < _door[i].rc.left)
					{
						_isaac->setX(_isaac->getX() - (_temp.right - _temp.left));
					}
					else
					{
						_isaac->setX(_isaac->getX() + (_temp.right - _temp.left));
					}
				}
				else // 위 아래
				{
					if (rc.top < _door[i].rc.top)
					{
						_isaac->setY(_isaac->getY() - (_temp.bottom - _temp.top));
					}
					else
					{
						_isaac->setY(_isaac->getY() + (_temp.bottom - _temp.top));
					}
				}
				_isaac->setRect(RectMakeCenter(_isaac->getX(), _isaac->getY(), 40, 10));
			}
			break;
		case GRIDDOOR:
			if (!_door[i].isOpen)
			{


				rc = _isaac->getRect();
				if (IntersectRect(&_temp, &rc, &_door[i].rc))
				{
					if (_temp.bottom - _temp.top > _temp.right - _temp.left) // 옆
					{
						if (rc.left < _door[i].rc.left)
						{
							_isaac->setX(_isaac->getX() - (_temp.right - _temp.left));
						}
						else
						{
							_isaac->setX(_isaac->getX() + (_temp.right - _temp.left));
						}
					}
					else // 위 아래
					{
						if (rc.top < _door[i].rc.top)
						{
							_isaac->setY(_isaac->getY() - (_temp.bottom - _temp.top));
						}
						else
						{
							_isaac->setY(_isaac->getY() + (_temp.bottom - _temp.top));
						}
					}
					_isaac->setRect(RectMakeCenter(_isaac->getX(), _isaac->getY(), 40, 10));
				}
			}

			break;
		case GRIDBOSSDOOR:
			break;
		default:
			break;

		}

		for (_viEnemy = _vEnemy->begin(); _viEnemy != _vEnemy->end(); ++_viEnemy)
		{
			rc = (*_viEnemy)->getRect();
			if (IntersectRect(&_temp, &rc, &_door[i].rc))
			{
				if (_temp.bottom - _temp.top > _temp.right - _temp.left) // 옆
				{
					if (rc.left < _door[i].rc.left)
					{
						(*_viEnemy)->setX((*_viEnemy)->getX() - (_temp.right - _temp.left));
					}
					else
					{
						(*_viEnemy)->setX((*_viEnemy)->getX() + (_temp.right - _temp.left));
					}
				}
				else // 위 아래
				{
					if (rc.top < _door[i].rc.top)
					{
						(*_viEnemy)->setY((*_viEnemy)->getY() - (_temp.bottom - _temp.top));
					}
					else
					{
						(*_viEnemy)->setY((*_viEnemy)->getY() + (_temp.bottom - _temp.top));
					}
				}
				switch ((*_viEnemy)->getEnemyType())
				{
				case CLOTTY:
					(*_viEnemy)->setRect(RectMakeCenter((*_viEnemy)->getX(), (*_viEnemy)->getY() + 30, 140 - 65, 140 - 110));
					break;
				case DIP:
					if (_temp.bottom - _temp.top > _temp.right - _temp.left) // 옆
					{
						if (rc.left < _tgrid[i].rc.left) // 왼
						{
							(*_viEnemy)->setAngle(PI - (*_viEnemy)->getAngle());
						}
						else // 오
						{
							(*_viEnemy)->setAngle(PI - (*_viEnemy)->getAngle());
						}
					}
					else // 위 아래
					{
						if (rc.top < _tgrid[i].rc.top)
						{
							(*_viEnemy)->setAngle(PI2 - (*_viEnemy)->getAngle());
						}
						else
						{
							(*_viEnemy)->setAngle(PI2 - (*_viEnemy)->getAngle());
						}
					}
					(*_viEnemy)->setRect(RectMakeCenter((*_viEnemy)->getX(), (*_viEnemy)->getY() + 15, IMAGEMANAGER->findImage("dip")->getFrameWidth() - 8, IMAGEMANAGER->findImage("dip")->getFrameHeight() - 40));
					break;
				case HORF:
					(*_viEnemy)->setRect(RectMakeCenter((*_viEnemy)->getX(), (*_viEnemy)->getY() - 2, IMAGEMANAGER->findImage("horf")->getFrameWidth() - 10, IMAGEMANAGER->findImage("horf")->getFrameHeight() - 50));

					break;
				case SUCKER:
					(*_viEnemy)->setRect(RectMakeCenter((*_viEnemy)->getX(), (*_viEnemy)->getY(), IMAGEMANAGER->findImage("sucker")->getFrameWidth() - 30, IMAGEMANAGER->findImage("sucker")->getFrameHeight() - 50));

					break;
				default:
					break;
				}
				// 추가적인 보정 필요 //
			}
		}
	}
}

//눙물과 벽 충돌
void startStage::tearWallCollision()
{
	for (_viTear = _vTear->begin(); _viTear != _vTear->end(); )
	{
		// 눈물 벽 충돌
		if (_viTear->rc.left < 184 || _viTear->rc.right > 752 + 204 || _viTear->rc.top < 203 || _viTear->rc.bottom > 634)
		{
			if (_viTear->range * 70 - 100 < getDistance(_viTear->x, _viTear->y, _viTear->fireX, _viTear->fireY))
			{
				float dis = getDistance(_viTear->x, _viTear->y, _viTear->fireX, _viTear->fireY) - _viTear->range * 70;
				EFFECTMANAGER->play("teareffect7", _viTear->x, _viTear->y + dis * 0.5, (_viTear->rc.bottom + _viTear->rc.top) / 2);
			}
			else
				EFFECTMANAGER->play("teareffect7", _viTear->x, _viTear->y - 50, (_viTear->rc.bottom + _viTear->rc.top) / 2);
			_viTear = _vTear->erase(_viTear);
		}
		else
		{
			++_viTear;
		}
	}
	for (_viETear = _vETear->begin(); _viETear != _vETear->end(); )
	{
		if (_viETear->rc.left < 184 || _viETear->rc.right > 752 + 204 || _viETear->rc.top < 203 || _viETear->rc.bottom > 634)
		{

			if (_viETear->range * 70 - getDistance(_viETear->fireX, _viETear->fireY, _viETear->x, _viETear->y) < _viETear->z)
			{
				EFFECTMANAGER->play("bloodteareffect3", _viETear->x, _viETear->y - _viETear->z + _viETear->sumg, (_viETear->rc.bottom + _viETear->rc.top) / 2);
			}
			else
				EFFECTMANAGER->play("bloodteareffect3", _viETear->x, _viETear->y - _viETear->z, (_viETear->rc.bottom + _viETear->rc.top) / 2);
			_viETear = _vETear->erase(_viETear);
		}
		else
		{
			++_viETear;
		}
	}
}

// 아이작과 적 충돌
void startStage::isaacEnemyCollision()
{
	RECT rc = _isaac->getRect();
	for (_viEnemy = _vEnemy->begin(); _viEnemy != _vEnemy->end(); ++_viEnemy)
	{
		RECT eRc = (*_viEnemy)->getRect();
		if (IntersectRect(&_temp, &rc, &eRc))
		{

			if ((*_viEnemy)->getEnemyType() != MONSTRO) {
				if (_isaac->getIst() != STDEATH && _isaac->getDefenceTime() == 0)
					_isaac->isaacDamage((*_viEnemy)->getDamage());
			}
			else
			{
				if ((*_viEnemy)->getZ() > -50)
					if (_isaac->getIst() != STDEATH && _isaac->getDefenceTime() == 0)
						_isaac->isaacDamage((*_viEnemy)->getDamage());
				cout << (*_viEnemy)->getZ();
			}
		}

	}
	for (_viETear = _vETear->begin(); _viETear != _vETear->end(); )
	{
		if (IntersectRect(&_temp, &rc, &_viETear->rc))
		{
			

			if (_viETear->z < 50)
			{
				if (_isaac->getIst() != STDEATH && _isaac->getDefenceTime() == 0)
					_isaac->isaacDamage(_viETear->damage);
				_viETear = _vETear->erase(_viETear);
				if (_viETear->range * 70 - getDistance(_viETear->fireX, _viETear->fireY, _viETear->x, _viETear->y) < _viETear->z)
				{
					EFFECTMANAGER->play("bloodteareffect3", _viETear->x, _viETear->y - _viETear->z + _viETear->sumg, (_viETear->rc.bottom + _viETear->rc.top) / 2);
				}
				else
					EFFECTMANAGER->play("bloodteareffect3", _viETear->x, _viETear->y - _viETear->z, (_viETear->rc.bottom + _viETear->rc.top) / 2);
			}
			else 
			{
				++_viETear;
			}
			
		}
		else
		{
			++_viETear;
		}
	}
}

void startStage::EnemyTearCollision()
{
	for (_viEnemy = _vEnemy->begin(); _viEnemy != _vEnemy->end(); ++_viEnemy)
	{
		RECT eRc = (*_viEnemy)->getRect();
		for (_viTear = _vTear->begin(); _viTear != _vTear->end();)
		{
			if (IntersectRect(&_temp, &eRc, &_viTear->rc))
			{

				if (_viTear->range * 70 - 100 < getDistance(_viTear->x, _viTear->y, _viTear->fireX, _viTear->fireY))
				{
					float dis = getDistance(_viTear->x, _viTear->y, _viTear->fireX, _viTear->fireY) - _viTear->range * 70;
					//teareffect7
					//bloodpoofalt1
					EFFECTMANAGER->play("teareffect7", _viTear->x, _viTear->y + dis * 0.5, (_viTear->rc.bottom + _viTear->rc.top) / 2);
				}
				else
					EFFECTMANAGER->play("teareffect7", _viTear->x, _viTear->y - 50, (_viTear->rc.bottom + _viTear->rc.top) / 2);
				// 상하좌우 살짝 밀기
				if (_viTear->angle == PI)
				{
					(*_viEnemy)->setX((*_viEnemy)->getX() - 4);
				}
				else if (_viTear->angle == 0)
				{
					(*_viEnemy)->setX((*_viEnemy)->getX() + 4);
				}
				else if (_viTear->angle == PI / 2)
				{
					(*_viEnemy)->setY((*_viEnemy)->getY() - 4);
				}
				else if (_viTear->angle == PI * 3 / 2)
				{
					(*_viEnemy)->setY((*_viEnemy)->getY() + 4);
				}
				switch ((*_viEnemy)->getEnemyType())
				{
				case CLOTTY:
					(*_viEnemy)->setRect(RectMakeCenter((*_viEnemy)->getX(), (*_viEnemy)->getY() + 30, 140 - 65, 140 - 110));
					break;
				case DIP:
					(*_viEnemy)->setRect(RectMakeCenter((*_viEnemy)->getX(), (*_viEnemy)->getY() + 15, IMAGEMANAGER->findImage("dip")->getFrameWidth() - 8, IMAGEMANAGER->findImage("dip")->getFrameHeight() - 40));

					break;
				case HORF:
					(*_viEnemy)->setRect(RectMakeCenter((*_viEnemy)->getX(), (*_viEnemy)->getY() - 2, IMAGEMANAGER->findImage("horf")->getFrameWidth() - 10, IMAGEMANAGER->findImage("horf")->getFrameHeight() - 50));

					break;
				case SUCKER:
					(*_viEnemy)->setRect(RectMakeCenter((*_viEnemy)->getX(), (*_viEnemy)->getY(), IMAGEMANAGER->findImage("sucker")->getFrameWidth() - 30, IMAGEMANAGER->findImage("sucker")->getFrameHeight() - 50));
					break;
				default:
					break;
				}
				//EFFECTMANAGER->play("bloodpoofalt1", (*_viEnemy)->getX(), (*_viEnemy)->getY(), (*_viEnemy)->getMiddle());
				(*_viEnemy)->setBlendCount(30);
				(*_viEnemy)->enemyDamage(_isaac->getDamage());
				_viTear = _vTear->erase(_viTear);

			}
			else
			{

				++_viTear;
			}
		}

	}
}

void startStage::bombCollision()
{
	for (_viBomb = _vBomb->begin(); _viBomb != _vBomb->end();)
	{
		RECT rc = (*_viBomb)->getRect();
		rc.left -= 80;
		rc.right += 80;
		rc.top -= 80;
		rc.bottom += 60;
		Rectangle(getMemDC(), rc);
		if ((*_viBomb)->getCount() == 120)
		{
			// 오브젝트
			for (int i = 0; i < MAX_GRID; i++)
			{
				switch (_tgrid[i].gridv)
				{
				case GRIDEMPTY:
					break;
				case GRIDROCK:
					if (IntersectRect(&_temp, &rc, &_tgrid[i].rc))
					{
						_tgrid[i].gridv = GRIDDESTROYEDROCK;
						_tgrid[i].frameX = 3;
					}
					break;
				case GRIDPOT:
					break;
				case GRIDPOOP:
					break;
				default:
					break;
				}
			}
			// 나
			RECT irc = _isaac->getRect();
			if (IntersectRect(&_temp, &rc, &irc))
			{
				_isaac->isaacDamage(2);
			}
			// 적
			for (_viEnemy = _vEnemy->begin(); _viEnemy != _vEnemy->end(); ++_viEnemy)
			{
				RECT erc = (*_viEnemy)->getRect();
				if (IntersectRect(&_temp, &rc, &erc))
				{
					(*_viEnemy)->enemyDamage(40);
				}
			}
			_viBomb = _vBomb->erase(_viBomb);
		}
		else
		{
			++_viBomb;
		}
	}
}

void startStage::EnemyDead()
{
	for (_viEnemy = _vEnemy->begin(); _viEnemy != _vEnemy->end();)
	{
		if ((*_viEnemy)->getHp() <= 0)
		{
			switch ((*_viEnemy)->getEnemyType())
			{
			case CLOTTY:
				EFFECTMANAGER->play("bloodpoof3", (*_viEnemy)->getX(), (*_viEnemy)->getY(), (*_viEnemy)->getMiddle());
				_viEnemy = _vEnemy->erase(_viEnemy);

				break;
			case DIP:
				EFFECTMANAGER->play("bloodpoofalt1", (*_viEnemy)->getX(), (*_viEnemy)->getY(), (*_viEnemy)->getMiddle());
				_viEnemy = _vEnemy->erase(_viEnemy);

				break;
			case HORF:
				EFFECTMANAGER->play("bloodpoof1", (*_viEnemy)->getX(), (*_viEnemy)->getY(), (*_viEnemy)->getMiddle());
				_viEnemy = _vEnemy->erase(_viEnemy);

				break;
			case SUCKER:
				EFFECTMANAGER->play("bloodpoofalt1", (*_viEnemy)->getX(), (*_viEnemy)->getY() - 50, (*_viEnemy)->getMiddle());
				_enemyManager->getEnemyTear()->fire((*_viEnemy)->getX(), (*_viEnemy)->getY(), 50, 0, 0.8, 5, 0, 0, 1);
				_enemyManager->getEnemyTear()->fire((*_viEnemy)->getX(), (*_viEnemy)->getY(), 50, PI / 2, 0.8, 5, 0, 0, 1);
				_enemyManager->getEnemyTear()->fire((*_viEnemy)->getX(), (*_viEnemy)->getY(), 50, PI, 0.8, 5, 0, 0, 1);
				_enemyManager->getEnemyTear()->fire((*_viEnemy)->getX(), (*_viEnemy)->getY(), 50, PI * 3 / 2, 0.8, 5, 0, 0, 1);
				_viEnemy = _vEnemy->erase(_viEnemy);

				break;
			case MONSTRO:
				_deathCount++;
				if (_deathCount % 5 == 1)

					EFFECTMANAGER->play("bloodpoof1",
						RND->getFromIntTo((*_viEnemy)->getRect().left, (*_viEnemy)->getRect().right),
						RND->getFromIntTo((*_viEnemy)->getRect().top, (*_viEnemy)->getRect().bottom),
						(*_viEnemy)->getMiddle()
					);
				if (_deathCount > 62)
					{
						EFFECTMANAGER->play("bloodpoof3", (*_viEnemy)->getX(), (*_viEnemy)->getY(), (*_viEnemy)->getMiddle());
						_viEnemy = _vEnemy->erase(_viEnemy);
					}
					else 
					{
						++_viEnemy;
					}
				break;
			default:
				break;
			}
		}
		else
		{
			++_viEnemy;
		}
	}
}

// 스테이지 클리어 시 호출
void startStage::stageClear()
{
	if (_isaac->getChargebar() >= _isaac->getChargebarMax())
		_isaac->setChargebar(_isaac->getChargebarMax());
	else
		_isaac->setChargebar(_isaac->getChargebar() + 1);
	_isClear = true;
	/*if (RND->getFromIntTo(0, 100) > 50)
	{
		EFFECTMANAGER->play("poof_large", WINSIZEX / 2, WINSIZEY / 2 - 20, WINSIZEX / 2);

		int rnd = RND->getFromIntTo(1, 61);
		if (rnd <= 20)
		{
			_itemManager->setBomb(6, 3);
		}
		else if (rnd <= 40)
		{
			_itemManager->setCoin(6, 3);
		}
		else
		{
			_itemManager->setKey(6, 3);
		}
	}*/
}

void startStage::doorMove()
{
	// 문열기
	for (int i = 0; i < 4; i++)
	{
		if (_door[i].doorInt <= 5)
			_door[i].doorInt += 3;
		else
			_door[i].isOpen = true;
	}
// _viTear->rc.left < 184 || _viTear->rc.right > 752 + 204 || _viTear->rc.top < 203 || _viTear->rc.bottom > 634
	// 왼
	if (_isaac->getRect().right > 752 + 214)
	{
		moveCameraSetting(-80, 0, -WINSIZEX, 0);
	}
	// 오
	if (_isaac->getRect().left < 164)
	{
		moveCameraSetting(80, 0, WINSIZEX, 0);
	}
	// 위
	if (_isaac->getRect().bottom > 634)
	{
		moveCameraSetting(0, -80, 0, -WINSIZEY);
	}
	// 아래 
	if (_isaac->getRect().top < 193)
	{
		moveCameraSetting(0, 80, 0, WINSIZEY);
	}

	// 맵 변경 작업
	if (RENDERMANAGER->getCameraX() == WINSIZEX) 
	{
		_isaac->setX(752 + 164);
		_isaac->setY(WINSIZEY / 2);
		RENDERMANAGER->setCameraX(-WINSIZEX);
		moveCameraSetting(80, 0, 0, 0);
		_vTear->clear();
		_vTear->resize(0);
		RENDERMANAGER->setCameraY(0);
		
	}
	else if (RENDERMANAGER->getCameraX() == -WINSIZEX) 
	{
		_vTear->clear();
		_vTear->resize(0);
		EFFECTMANAGER->stop();
		
		_isaac->setX(224);
		_isaac->setY(WINSIZEY / 2);
		moveCameraSetting(-80, 0, 0, 0);
		RENDERMANAGER->setCameraX(WINSIZEX);
		RENDERMANAGER->setCameraY(0);
		// 플래그 꺼주기
		_settingFlag = false;
		// 데이터 옮겨 갈거 넣어 주기
		DATAMANAGER->setCamera(_increaseX, _increaseY, _targetX, _targetY);
		DATAMANAGER->updateIsaacData
		(
			_isaac->getMaxHeart(),
			_isaac->getHeart(),
			_isaac->getRange(),
			_isaac->getSpeed(),
			_isaac->getTear(),
			_isaac->getShotspeed(),
			_isaac->getDamage(),
			_isaac->getChargebarMax(),
			_isaac->getChargebar(),
			_isaac->getCoin(),
			_isaac->getBomb(),
			_isaac->getKey(),
			_isaac->getSpaceItem(),
			_isaac->getLastTearKey(),
			_isaac->getX(),
			_isaac->getY(),
			_isaac->getSecond(),
			_isaac->getTearName(),
			_isaac->getIsaacHead(),
			_isaac->getOnion()
		);
		SCENEMANAGER->setScene("노말스테이지");
		//SCENEMANAGER->setScene("스테이지6");

	}
	else if (RENDERMANAGER->getCameraY() == WINSIZEY) 
	{
		_isaac->setX(WINSIZEX / 2);
		_isaac->setY(594);
		moveCameraSetting(0, 80, 0, 0);
		RENDERMANAGER->setCameraX(0);
		RENDERMANAGER->setCameraY(-WINSIZEY);
		_vTear->clear();
		_vTear->resize(0);
	}
	else if (RENDERMANAGER->getCameraY() == -WINSIZEY) 
	{
		_isaac->setX(WINSIZEX / 2);
		_isaac->setY(214);
		moveCameraSetting(0, -80, 0, 0);
		RENDERMANAGER->setCameraX(0);
		RENDERMANAGER->setCameraY(WINSIZEY);
		_vTear->clear();
		_vTear->resize(0);
	}
}

// 카메라 세팅
	void startStage::moveCameraSetting(float increaseX, float increaseY, float targetX, float targetY)
	{
		_increaseX = increaseX;
		_increaseY = increaseY;
		_targetX = targetX;
		_targetY = targetY;
	}

	// 카메라 움직임
	void startStage::moveCamera()
	{
		// 아무 작업도 안함
		if (_increaseX == 0 && _increaseY == 0) return;
		if (0 > _increaseX)
		{
			RENDERMANAGER->setCameraX(RENDERMANAGER->getCameraX() + _increaseX);
			if (RENDERMANAGER->getCameraX() < _targetX)
			{
				RENDERMANAGER->setCameraX(_targetX);
			}
		}
		else 
		{
			RENDERMANAGER->setCameraX(RENDERMANAGER->getCameraX() + _increaseX);
			if (RENDERMANAGER->getCameraX() > _targetX)
			{
				RENDERMANAGER->setCameraX(_targetX);
			}
		}
		if (0 > _increaseY) 
		{
			RENDERMANAGER->setCameraY(RENDERMANAGER->getCameraY() + _increaseY);
			if (RENDERMANAGER->getCameraY() < _targetY)
			{
				RENDERMANAGER->setCameraY(_targetY);
			}
		}
		else 
		{
			RENDERMANAGER->setCameraY(RENDERMANAGER->getCameraY() + _increaseY);
			if (RENDERMANAGER->getCameraY() > _targetY)
			{
				RENDERMANAGER->setCameraY(_targetY);
			}
		}
	}
