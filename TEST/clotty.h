#pragma once
#include "enemy.h"
class clotty :
	public enemy
{

public:
	clotty() {}
	~clotty() {}

	virtual HRESULT init();
	virtual HRESULT init( POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void draw();

	void playPtn(enemyPtn ptn);
};

