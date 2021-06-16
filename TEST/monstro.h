#pragma once
#include "enemy.h"

class monstro :
	public enemy
{
private:
	float _gravity;
	float _sumg;
	float _setAngle;
public:
	monstro() {}
	~monstro() {}

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void draw();

	void playPtn(enemyPtn ptn);
};

