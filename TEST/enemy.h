#pragma once
#include "gameNode.h"

enum enemyType 
{
	CLOTTY,
	DIP,
	HORF,
	SUCKER,
	MONSTRO
};

enum enemyPtn 
{
	EPTNA,
	EPTNB,
	EPTNC,
	EPTND,
	EPTNE
};

class enemy : public gameNode
{
protected:
	image* _imageName;		//에너미 이미지
	float _x;
	float _y;
	int _frameX;		//프레임번호로 사용할 변수
	int _frameY;
	int _currentFrameX;
	int _currentFrameY;
	float _radius;

	int _damage;
	float _speed;
	float _angle;
	float _hp;

	RECT _rc;				//렉트

	int _count;				//프레임렌더링 용
	int _maxCount;

	enemyType _st;			// 무슨 에너미 인가?
	int _rndCount;			//발사 카운트 용
	int _rndFireCount;		//랜덤 발사 카운트 용

	int _blendCount;
	BYTE _blend;

	enemyPtn _ptn;
	float _z;
	float _isaacX;
	float _isaacY;

public:
	enemy() {}
	~enemy() {}

	virtual HRESULT init();
	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	void move();
	void draw();

	bool patternCount();

	// 개터 쌔더
	void setPtn(enemyPtn ptn) { _ptn = ptn; }
	void setRndFireCount(int num) { _rndFireCount = num; };
	void setAngle(float angle) { _angle = angle; }
	float getAngle() { return _angle; }
	void setMaxCount(int num) { _maxCount = num; }
	int getMaxCount() { return _maxCount; }
	inline float getMiddle() { return (_rc.bottom + _rc.top) / 2; }
	inline RECT getRect() { return _rc; }
	inline enemyType getEnemyType() { return _st; }
	int getDamage() { return _damage; }
	float getX() { return _x; }
	float getY() { return _y; }
	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }
	void setRect(RECT rc) { _rc = rc; }
	void enemyDamage(float damage) { _hp -= damage; }
	float getHp() { return _hp; }
	int getBlendCount() { return _blendCount; }
	BYTE getBlend() { return _blend; }
	void  setBlendCount(int blendCount) { _blendCount = blendCount; }
	void  setBlend(BYTE blend) { _blend = blend; }
	void setSpeed(float speed) { _speed = speed; }
	void setFrameX(int num) { _frameX = num; }
	float getRadius() { return _radius; }
	void setIsaacX(float num) { _isaacX = num; }
	void setIsaacY(float num) { _isaacY = num; }
	void setZ(float num) { _z = num; }
	float getZ() { return _z; }
	int getFrameX() { return _frameX; }
	enemyPtn getPtn() { return _ptn; }
};

