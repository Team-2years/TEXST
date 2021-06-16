#pragma once
#include "enemy.h"

// 이친구 지멋대로 움직인다
// 그리고 오브젝트에 튕김

class dip :
	public enemy
{
public:
	dip() {};
	~dip() {};

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void draw();

	void playPtn(enemyPtn ptn);
};

