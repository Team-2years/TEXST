#include "stdafx.h"
#include "enemyManager.h"

HRESULT enemyManager::init()
{
	_enemyTear = new enemyTear;
	_enemyTear->init("bloodtear3","tearshadow3");
	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update(isaac* isaac)
{
	_isaacX = isaac->getX();
	_isaacY = isaac->getY();
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
		// 서커의 유도 기능
		switch ((*_viEnemy)->getEnemyType())
		{
		case SUCKER:
		case MONSTRO:
			(*_viEnemy)->setAngle(getAngle(_isaacX, _isaacY, (*_viEnemy)->getX(), (*_viEnemy)->getY()));
			if ((*_viEnemy)->getPtn() == EPTNB && (*_viEnemy)->getFrameX() == 21)
			{
			

				for (int i = RND->getFromIntTo(8, 15); i != 0; i--) 
				{
					_enemyTear->fire((*_viEnemy)->getX(), (*_viEnemy)->getY(), RND->getFromIntTo(30, 150), PI + (*_viEnemy)->getAngle() + RND->getFromFloatTo(-PI / 16, PI/16), RND->getFromFloatTo(0.8, 1.5), RND->getFromFloatTo(4, 10), RND->getFromFloatTo(0.1,1.0), RND->getFromFloatTo(0.0005, 0.004), 2, 0, true);

				}
			}
			else if ((*_viEnemy)->getPtn() == EPTNC && (*_viEnemy)->getFrameX() == 51 && (*_viEnemy)->getZ() == 0)
			{


				for (int i = RND->getFromIntTo(8, 10); i != 0; i--)
				{
					_enemyTear->fire((*_viEnemy)->getX(), (*_viEnemy)->getY(), RND->getFromIntTo(30, 150), RND->getFromFloatTo(0, PI2), RND->getFromFloatTo(0.8, 1.5), RND->getFromFloatTo(4, 10), RND->getFromFloatTo(0.1, 1.0), RND->getFromFloatTo(0.0005, 0.004), 2, 0, true);
				}
			}
			if ((*_viEnemy)->getEnemyType() == MONSTRO) 
			{
				if (DATAMANAGER->getBossHp() <= 0)
					DATAMANAGER->setMaxBossHp((*_viEnemy)->getHp());
				DATAMANAGER->setBossHp((*_viEnemy)->getHp());
			}
			
			break;
		case HORF:
			
			break;
		default:
			break;
		}
		
	}
	enemyPattern();
	_enemyTear->update();
}

void enemyManager::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy) 
	{
		(*_viEnemy)->render();
	}
	_enemyTear->render();
}

void enemyManager::setEnemy(enemyType enemyT, int x, int y)
{
	enemy* _enemy;
	POINT pt = PointMake(x, y);
	switch (enemyT)
	{
	case CLOTTY:
		_enemy = new clotty;
		_enemy->init(pt);
		break;
	case DIP:
		_enemy = new dip;
		_enemy->init(pt);
		break;
	case HORF:
		_enemy = new horf;
		_enemy->init(pt);
		break;
	case SUCKER:
		_enemy = new sucker;
		_enemy->init(pt);
		break;
	case MONSTRO:
		_enemy = new monstro;
		_enemy->init(pt);
		break;
	default:
		break;
	}
	_vEnemy.push_back(_enemy);
}

// 적패퉨
void enemyManager::enemyPattern()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		if ((*_viEnemy)->patternCount())
		{
			int rnd = RND->getFromIntTo(0, 100);
			switch ((*_viEnemy)->getEnemyType())
			{
			case CLOTTY:
				if (rnd > 20) 
				{
					(*_viEnemy)->setPtn(EPTNA);
					(*_viEnemy)->setAngle(RND->getFromFloatTo(0, PI2));
					(*_viEnemy)->setMaxCount(50);
				}
				else 
				{
					EFFECTMANAGER->play("bloodpoof1", (*_viEnemy)->getX(), (*_viEnemy)->getY(), (*_viEnemy)->getMiddle());
					_enemyTear->fire((*_viEnemy)->getX(), (*_viEnemy)->getY() + 30,30, 0, 0.8, 5, 0, 0, 1);
					_enemyTear->fire((*_viEnemy)->getX(), (*_viEnemy)->getY() + 30,30, PI/2, 0.8, 5, 0, 0, 1);
					_enemyTear->fire((*_viEnemy)->getX(), (*_viEnemy)->getY() + 30,30, PI, 0.8, 5, 0, 0, 1);
					_enemyTear->fire((*_viEnemy)->getX(), (*_viEnemy)->getY() + 30,30, PI * 3/2, 0.8, 5, 0, 0, 1);
					(*_viEnemy)->setPtn(EPTNB);
					(*_viEnemy)->setMaxCount(30);
				}
				break;
			case DIP:
				(*_viEnemy)->setPtn(EPTNA);
				(*_viEnemy)->setAngle(RND->getFromFloatTo(0, PI2));
				(*_viEnemy)->setSpeed(RND->getFromIntTo(5, 10));
				(*_viEnemy)->setMaxCount(35);
				(*_viEnemy)->setFrameX(0);
				(*_viEnemy)->setRndFireCount(RND->getFromIntTo(50, 100));
				break;
			case HORF:
				(*_viEnemy)->setAngle(getAngle(_isaacX, _isaacY, (*_viEnemy)->getX(), (*_viEnemy)->getY()));
				//감지 범위
				if (getDistance(_isaacX, _isaacY, (*_viEnemy)->getX(), (*_viEnemy)->getY()) < (*_viEnemy)->getRadius() && (*_viEnemy)->getMaxCount() <= 0)
					(*_viEnemy)->setMaxCount(20);
				if ((*_viEnemy)->getMaxCount() > 0)
				{
					EFFECTMANAGER->play("bloodpoofalt1", (*_viEnemy)->getX(), (*_viEnemy)->getY(), (*_viEnemy)->getMiddle());
					_enemyTear->fire((*_viEnemy)->getX(), (*_viEnemy)->getY(), 30, PI + (*_viEnemy)->getAngle(), 0.8, 5, 0, 0, 1);
				}
				(*_viEnemy)->setPtn(EPTNA);
				(*_viEnemy)->setFrameX(0);
				(*_viEnemy)->setRndFireCount(RND->getFromIntTo(80, 150));
				break;

			case SUCKER:
				// 이친구는 없어
				break;
			case MONSTRO:
				
				if (rnd <= 30)
				{
					(*_viEnemy)->setPtn(EPTNC);
					(*_viEnemy)->setMaxCount(58);
					(*_viEnemy)->setFrameX(0);
					(*_viEnemy)->setRndFireCount(120);
					(*_viEnemy)->setSpeed(20);
				}
				else if (rnd <= 60)
				{
					(*_viEnemy)->setPtn(EPTNB);
					
					(*_viEnemy)->setMaxCount(40);
					(*_viEnemy)->setFrameX(0);
					(*_viEnemy)->setRndFireCount(90);
				}
				else 
				{
					(*_viEnemy)->setPtn(EPTNA);
					
					(*_viEnemy)->setMaxCount(40);
					(*_viEnemy)->setFrameX(0);
					(*_viEnemy)->setSpeed(RND->getFromIntTo(4,10));
					(*_viEnemy)->setRndFireCount(90);
				}
				break;
			default:
				break;
			}
		}
	}
}
