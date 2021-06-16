#pragma once
#include "gameNode.h"
#include "isaac.h"
#include <vector>
#include "enemy.h"
#include "clotty.h"
#include "dip.h"
#include "sucker.h"
#include "horf.h"
#include"monstro.h"
#include "tear.h"

class enemyManager : public gameNode
{
private:
	// 몬스터의 벡터
	vector<enemy*>				_vEnemy;
	vector<enemy*>::iterator	_viEnemy;
	// bloodTear3
	enemyTear*	_enemyTear;

	// 유도, 및 접근시 탐지를 위한 x, y
	float _isaacX;
	float _isaacY;

	// 충돌 처리 렉트
	RECT _temp;
public:
	enemyManager() {}
	~enemyManager() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update(isaac* isaac);
	virtual void render();

	void setEnemy(enemyType enemyT, int x, int y);
	void enemyPattern();

	//개터 세터
	vector<enemy*>* getVEnemy() { return &_vEnemy; }
	vector<tagTear>* getVTear() { return _enemyTear->getVTear(); }
	enemyTear* getEnemyTear() { return _enemyTear; }
};

	

