#pragma once
#include "gameNode.h"
class bossIntro :
	public gameNode
{
private:
	float _ix;
	float _iy;
	float _tx;
	float _ty;
	bool _settingFlag;
	int _count;
	image* _bossIntro;

public:
	bossIntro() { init(); }
	~bossIntro() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	void moveCameraSetting(float ix, float iy, float tx, float ty);
	void moveCamera();
};

