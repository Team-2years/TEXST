#pragma once
#include "singletonBase.h"

enum moveState
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE,
	LEFTUP,
	LEFTDOWN,
	RIGHTUP,
	RIGHTDOWN
};

class dataManager :
	public singletonBase<dataManager>
{
private:
	float _ix;
	float _iy;
	float _tx;
	float _ty;
	
	bool _isClearBoss;
	float _bossHp;
	float _bossMaxHp;
	// 아이작 관련 정보들
	// 아이작의 스탯에 관한 멤버 변수
	int _maxHeart;
	int _heart;
	float _range;
	float _speed;
	float _tear;
	float _shotspeed;
	float _damage;
	// 아이작이 소지한 아이템
	int _chargebarMax;
	int _chargebar;
	int _coin;
	int _bomb;
	int _key;
	const char* _spaceItem;
	list<moveState> _lastTearKey;
	// 아이작의 현재 맵 위치
	//string _currentStage;

	float _x, _y;

	int _second;
	
	string _tearName;

	const char* _isaacheadkey;
	// 아이작 아이템 먹음 관련 변수들
	bool _isaac_onion;
	bool _isaac_innereye;
	bool _isaac_lokishorns;
	bool _isaac_wirehanger;
	bool _isaac_jesusjuice;
	bool _isaac_mutantspider;
	bool _isaac_halo;
public:
	dataManager() {}
	~dataManager() {}

	HRESULT init();
	void setCamera(float ix, float iy, float tx, float ty) 
	{
		_ix = ix;
		_iy = iy;
		_tx = tx;
		_ty = ty;
	}
	float getIX() { return _ix; }
	float getIY() { return _iy; }
	float getTX() { return _tx; }
	float getTY() { return _ty; }
	// 아이작 정보 저장
	void updateIsaacData
	(
		int _maxHeart,
		int _heart,
		float _range,
		float _speed,
		float _tear,
		float _shotspeed,
		float _damage,
		int _chargebarMax,
		int _chargebar,
		int _coin,
		int _bomb,
		int _key,
		const char* _spaceItem,
		list<moveState> lastTearKey,
		float _x,
		float _y,
		int _second,
		string _tearName,
		const char* _isaacheadkey,
		bool _isaac_onion
	) 
	{
		this->_maxHeart = _maxHeart;
		this->_heart = _heart;
		this->_range = _range;
		this->_speed = _speed;
		this->_tear = _tear;
		this->_shotspeed = _shotspeed;
		this->_damage = _damage;
		this->_chargebarMax = _chargebarMax;
		this->_chargebar = _chargebar;
		this->_coin = _coin;
		this->_bomb = _bomb;
		this->_key = _key;
		this->_spaceItem = _spaceItem;
		_lastTearKey = lastTearKey;
		this->_x = _x;
		this->_y = _y;
		this->_second = _second;
		this->_tearName = _tearName;
		this->_isaacheadkey = _isaacheadkey;
		this->_isaac_onion = _isaac_onion;
	}
	int getMaxHeart() { return _maxHeart; }
	int getHeart() { return _heart; }
	float getRange() { return _range; }
	float getSpeed() { return _speed; }
	float getTear() { return _tear; }
	float getShotspeed() { return _shotspeed; }
	float getDamage() { return _damage; }
	int getChargebarMax() { return _chargebarMax; }
	int getChargebar() { return _chargebar; }
	int getCoin() { return _coin; }
	int getBomb() { return _bomb; }
	int getKey() { return _key; }
	const char* getSpaceItem() { return _spaceItem; }
	float getX() { return _x; }
	float getY() { return _y; }
	int getSecond() { return _second; }
	string getTearName() { return _tearName; }
	const char* getIsaacHead() { return _isaacheadkey; }
	bool getOnion() { return _isaac_onion; }
	list<moveState> getLastTearKey() { return _lastTearKey; }

	void setInnerEye(bool is) { _isaac_innereye = is; }
	bool getInnerEye() { return _isaac_innereye; }

	void setLokisHorns(bool is) { _isaac_lokishorns = is; }
	bool getLokisHorns() { return _isaac_lokishorns; }

	void setWireHanger(bool is) { _isaac_wirehanger = is; }
	bool getWireHanger() { return _isaac_wirehanger; }

	void setJesusJuice(bool is) { _isaac_jesusjuice = is; }
	bool getJesusJuice() { return _isaac_jesusjuice; }

	void setMutantSpider(bool is) { _isaac_mutantspider = is; }
	bool getMutantSpider() { return _isaac_mutantspider; }
	
	void setHalo(bool is) { _isaac_halo = is; }
	bool getHalo() { return _isaac_halo; }

	void setIsClearBoss() { _isClearBoss = true; }
	bool getIsClearBoss() { return _isClearBoss; }

	void setBossHp(float num) { _bossHp = num; }
	float getBossHp() { return _bossHp; }
	void setMaxBossHp(float num) { _bossMaxHp = num; }
	float getMaxBossHp() { return _bossMaxHp; }

};

