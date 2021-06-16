#pragma once
#include "gameNode.h"

struct tagTear
{
	// tearImageøÕshadow¿Ã∏ß
	image* tearImage;
	image* tearShadow;
	const char* imageName;
	const char* shadowName;
	RECT rc;
	float x, y, z;
	float angle;
	float radius;
	float speed;
	float fireX, fireY;
	float tearX, tearY;
	float range;
	float shadowSize;
	float sumg;
	float gravity;
	float gravity2;
	int count;
	int damage;
	bool isAngle;
	float rndiz;
	float sumg2;
};

class isaacTear :
	public gameNode
{
	vector<tagTear> _vTear;
	vector<tagTear>::iterator _viTear;
	const char* _imageName;
	const char * _tearShadow;
public:
	isaacTear();
	~isaacTear();

	virtual HRESULT init(const char* imageName, const char * tearShadow);
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y, float angle, float speed, float range, float tearX, float tearY);
	void move();


	///////
	//getter setter
	///////
	vector<tagTear>* getVTear() { return &_vTear; }
	vector<tagTear>::iterator getViTear() { return _viTear; }
};



class enemyTear :
	public gameNode 
{
	vector<tagTear> _vTear;
	vector<tagTear>::iterator _viTear;
	const char* _imageName;
	const char * _tearShadow;
public:
	enemyTear() {}
	~enemyTear() {}

	virtual HRESULT init(const char* imageName, const char * tearShadow);
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(float x, float y, float z, float angle, float speed, float range, float tearX, float tearY, int damage, float gravity = 0 ,bool isAngle = false);
	void move();

	///////
	//getter setter
	///////
	vector<tagTear>* getVTear() { return &_vTear; }
	vector<tagTear>::iterator getViTear() { return _viTear; }
};
