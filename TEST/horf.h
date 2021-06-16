#pragma once
#include "enemy.h"

// 이 친구는 못움직임
// 탐지 범위안에 아이작이 들어 올시 눈물을 뱉음

class horf :
	public enemy
{
public:
	horf() {}
	~horf() {}

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void draw();

	void playPtn(enemyPtn ptn);
};

