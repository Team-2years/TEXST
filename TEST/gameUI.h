#pragma once
#include "gameNode.h"
#include "isaac.h"

class gameUI :
	public gameNode
{
private:
	// 아이작에 관한 정보 저장
	isaac* _isaac;
	// 하트 UI 이미지
	image* _heartUI;
	//  충전 바 UI 이미지
	image* _chargebarUI;
	// 픽업 아이템의 아이콘
	image* _pickUpItemIcon;
	// stat 아이콘
	image* _statIcon;
	// 숫자 
	image* _number;
	// 점
	image* _dot;
	// 차지바 그린
	image* _chargeGreen;

	image* _deathUI;

	int  _deathCount;

	// 체력바 이미지
	image* _progressBarTop;
	image* _progressBarBottom;

public:
	gameUI();
	~gameUI();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	// 아이작에 대한 데이터를 뽑아옴
	void updateIsaac(isaac* iac) { _isaac = iac; }
	// 하트 UI 그려주기
	void heartRender();
	// 충전바 UI 그려주기
	void chargedbarRender();
	// 픽업아이템 UI 그려주기
	void pickUpItemRender();
	// 스탯 UI 그려주기
	void statRender();
	void spaceItemRender();
	void deathUIRender();
	void bossHeath();
};

