#pragma once
#include "gameNode.h"

class mainMenu :
    public gameNode
{
private:
	// 페이드인 아웃
	BYTE _fadeCount;
	bool _isFade;
	// 고른 메뉴 목록
	int _selectNum;
	// 키보드 인식 간격
	int _term;
	
	// 로딩 카운트
	int _loadingCount;
	
	// 이미지 저장 변수들
	image* _mainMenu;		// 메인메뉴 이미지
	image* _menuWord;		// 메뉴 글자 이미지
	image* _bgBlack;		// 페이드 인 아웃 처리할 이미지
	image* _menuSelector;	// 메뉴 목록에서 선택되었는지 확인할 화살표
	image* _loading;		// 로딩 이미지
public:
	mainMenu();
	~mainMenu();

	HRESULT init();
	void release();
	void update();
	void render();
};

