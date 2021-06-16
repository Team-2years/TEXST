#include "stdafx.h"
#include "mainMenu.h"

mainMenu::mainMenu()
{
	init();
}

mainMenu::~mainMenu()
{
}

HRESULT mainMenu::init()
{
	// 변수 초기화
	_fadeCount = _selectNum = _loadingCount = 0;
	_isFade = false;
	// 이미지 초기화
	IMAGEMANAGER->addImage("메인메뉴", "image/ui/mainMenu.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255));
	_mainMenu = IMAGEMANAGER->findImage("메인메뉴");
	
	IMAGEMANAGER->addImage("선택자", "image/ui/menuSelect.bmp", 50, 100, true, RGB(255, 0, 255));
	_menuSelector = IMAGEMANAGER->findImage("선택자");

	IMAGEMANAGER->addFrameImage("메뉴글자", "image/ui/menuWord.bmp", 232, 300, 1, 3, true, RGB(255, 0, 255), true);
	_menuWord = IMAGEMANAGER->findImage("메뉴글자");

	
	_bgBlack = IMAGEMANAGER->findImage("검은배경");

	IMAGEMANAGER->addFrameImage("로딩", "image/ui/loading.bmp", 482, 300, 2, 1, true, RGB(255, 0, 255), true);
	_loading = IMAGEMANAGER->findImage("로딩");
	// 적 이미지 추가
	// 일반 몹
	IMAGEMANAGER->addFrameImage("clotty", "image/enemy/monster/clotty/clotty.bmp", 1120, 560, 8, 4, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("clottyshadow", "image/enemy/monster/clotty/clottyshadow.bmp", 65, 16, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("dip", "image/enemy/monster/dip/dip.bmp", 210, 100, 5, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("dipshadow", "image/enemy/monster/dip/dipshadow.bmp", 30, 13,true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("sucker", "image/enemy/monster/sucker/sucker.bmp", 128, 128, 2, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("horf", "image/enemy/monster/horf/horf.bmp", 210, 140, 3, 2, true, RGB(255, 0, 255), true);
	// 보스 몹
	IMAGEMANAGER->addFrameImage("monstro", "image/enemy/boss/monstro/monstro.bmp", 2160, 498, 9, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("monstroshadow", "image/enemy/boss/monstro/monstroshadow.bmp", 240, 64, true, RGB(255, 0, 255), true);

	// 픽업 아이템 이미지 추가
	IMAGEMANAGER->addFrameImage("coin1", "image/item/coin1.bmp", 384, 32, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bomb", "image/item/bomb.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("key", "image/item/key.bmp", 144, 45, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("heart", "image/item/heart.bmp", 64, 64, true, RGB(255, 0, 255));
	// 폭탄 도화서 불타는거
	IMAGEMANAGER->addFrameImage("sparkbomb", "image/item/sparkbomb.bmp", 512, 64, 8, 1, true, RGB(255, 0, 255));
	// 아이템 이미지 추가
	IMAGEMANAGER->addImage("cricketshead", "image/item/icon/cricketshead.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bloodofthemartyr", "image/item/icon/bloodofthemartyr.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("breakfast", "image/item/icon/breakfast.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("dessert", "image/item/icon/dessert.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("dinner", "image/item/icon/dinner.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("dice", "image/item/icon/dice.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("lunch", "image/item/icon/lunch.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("onion", "image/item/icon/onion.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rottenmeat", "image/item/icon/rottenmeat.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("steven", "image/item/icon/steven.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("thebelt", "image/item/icon/thebelt.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("thebookofbelial", "image/item/icon/thebookofbelial.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("theinnereye", "image/item/icon/theinnereye.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("thepoop", "image/item/icon/thepoop.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("lokishorns", "image/item/icon/lokishorns.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("wirecoathanger", "image/item/icon/wirecoathanger.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("jesusjuice", "image/item/icon/jesusjuice.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mutantspider", "image/item/icon/mutantspider.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("halo", "image/item/icon/thehalo.bmp", 64, 64, true, RGB(255, 0, 255));

	// 받침대 및 그림자
	IMAGEMANAGER->addImage("itemShadow", "image/item/itemShadow.bmp", 26, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("prop", "image/item/prop.bmp", 64, 64, true, RGB(255, 0, 255));
	// 그리드 이미지
	// 돌, 항아리 등등
	IMAGEMANAGER->addFrameImage("rocks", "image/grid/rocks.bmp", 256, 192, 4 ,3, true, RGB(255, 0, 255));
	// 문 이미지
	IMAGEMANAGER->addFrameImage("doorUD", "image/grid/doorupdown.bmp", 768, 192, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("doorLR", "image/grid/doorleftright.bmp", 576, 256, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossdoorUD", "image/grid/bossdoorud.bmp", 640, 192, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bossdoorLR", "image/grid/bossdoorlr.bmp", 480, 256, 5, 2, true, RGB(255, 0, 255));

	// 눙물
	IMAGEMANAGER->addImage("bloodtear3", "image/tear/bloodtear3.bmp", 23, 23, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("tearshadow3", "image/tear/shadow/tearShadow3.bmp", 23, 5, true, RGB(255, 0, 255), true);
	return S_OK;
}

void mainMenu::release()
{
}

void mainMenu::update()
{
	// 페이드 인 처리
	if (_fadeCount < 255 && _isFade == false) 
	{
		_fadeCount += 5;
	}
	// 페이드 아웃
	if (_fadeCount > 0 && _isFade == true)
	{
		_fadeCount -= 5;
	}

	// 메뉴 이동 간격
	_term++;
	// esc
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) 
	{
		exit(1);
	}
	// R
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		init();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) 
	{
		switch (_selectNum)
		{
		case 0:
			_isFade = true;
			break;
		case 1:
			
			break;
		case 2:
			
			break;
		default:
			break;
		}
	}
	// 이동간격 마다 들어가서 작동
	if (_term > 20 && KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_selectNum++;
		if (_selectNum >= 3)
			_selectNum = 0;
		_term = 0;
	}
	if (_term > 20 && KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_selectNum--;
		if (_selectNum <= -1)
			_selectNum = 2;
		_term = 0;
	}
}

void mainMenu::render()
{
	// 메뉴 화면 처리
	_mainMenu->render(getMemDC());
	switch (_selectNum)
	{
	case 0:		
		_menuSelector->render(getMemDC(), 420, 295);
		_menuWord->alphaFrameRender(getMemDC(), 450, 280, 0, 0, 255);
		_menuWord->alphaFrameRender(getMemDC(), 455, 380, 0, 1, 100);
		_menuWord->alphaFrameRender(getMemDC(), 460, 480, 0, 2, 100);
		break;
	case 1:		
		_menuSelector->render(getMemDC(), 430, 395);
		_menuWord->alphaFrameRender(getMemDC(), 450, 280, 0, 0, 100);
		_menuWord->alphaFrameRender(getMemDC(), 455, 380, 0, 1, 255);
		_menuWord->alphaFrameRender(getMemDC(), 460, 480, 0, 2, 100);
		break;
	case 2:		
		_menuSelector->render(getMemDC(), 440, 495);
		_menuWord->alphaFrameRender(getMemDC(), 450, 280, 0, 0, 100);
		_menuWord->alphaFrameRender(getMemDC(), 455, 380, 0, 1, 100);
		_menuWord->alphaFrameRender(getMemDC(), 460, 480, 0, 2, 255);
		break;
	default:
		break;
	}
	

	// 페이드 인 아웃 처리할 꺼만 배경
	_bgBlack->alphaRender(getMemDC(), 255 - _fadeCount);
	// 로딩 이미지
	if (_isFade)
	{
		_loadingCount++;
		if (_loadingCount%10 >= 5)
		{
			_loading->alphaFrameRender(getMemDC(), WINSIZEX/2 - _loading->getFrameWidth() / 2, WINSIZEY/2 - _loading->getFrameHeight() / 2, 1, 0, 255 - _fadeCount);
		}
		else
		{
			_loading->alphaFrameRender(getMemDC(), WINSIZEX/2 - _loading->getFrameWidth() / 2, WINSIZEY/2 - _loading->getFrameHeight() / 2, 0, 0, 255 - _fadeCount);
		}
		if (_loadingCount > 60) 
		{
			SCENEMANAGER->setScene("시작스테이지");
		}
	}
}
