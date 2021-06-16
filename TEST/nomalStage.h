#pragma once
#include "gameNode.h"
#include "isaac.h"
#include "gameUI.h"
#include "itemManager.h"
#include "enemyManager.h"
#include "grid.h"

class nomalStage : public gameNode
{


private:
	bool _settingFlag;
	// 아군 눈물
	vector<tagTear>					*_vTear;
	vector<tagTear>::iterator		_viTear;
	// 적군 눈물
	vector<tagTear>* _vETear;
	vector<tagTear>::iterator		_viETear;
	// 폭탄
	vector<pickUpItem*>*             _vBomb;
	vector<pickUpItem*>::iterator   _viBomb;
	// 클리어 햇눈가?
	bool							_isClear;
	int								_fadeCount;
	int								_middleValX;
	int								_middleValY;
	int _doorCount;
	// 아이작!	
	isaac*							_isaac;
	//아이템 매니져!
	itemManager*					_itemManager;
	//에너미 매니져
	enemyManager*					_enemyManager;
	// 게임 UI	
	gameUI*							_gameUI;
	// 이미지	
	image*							_bgBlack;
	// 그리드
	grid*							_grid;
	//
	vector<enemy*>* _vEnemy;
	vector<enemy*>::iterator _viEnemy;

	tagTILE* _wall;
	tagTILE* _door;
	tagTILE* _tgrid;
	RECT _temp;

	float _targetX;
	float _targetY;
	float _increaseX;
	float _increaseY;

public:
	nomalStage();
	~nomalStage();

	virtual HRESULT init();
	virtual HRESULT init( isaac* _isaac, float ix, float iy, float tx, float ty);
	virtual void release();
	virtual void update();
	virtual void render();

	void wallCollision();
	void gridCollision();
	void doorCollision();
	void tearWallCollision();
	void isaacEnemyCollision();
	void EnemyTearCollision();
	void bombCollision();
	void EnemyDead();
	void stageClear();
	void moveCameraSetting(float increaseX, float increaseY, float targetX, float targetY);
	void doorMove();
	void moveCamera();
};

