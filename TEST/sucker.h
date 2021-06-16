#pragma once
#include "enemy.h"
class sucker :
	public enemy
{

public:
	sucker() {}
	~sucker() {}

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void draw();

	void playPtn(enemyPtn ptn);
};

