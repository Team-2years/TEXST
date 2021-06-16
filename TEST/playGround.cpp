#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{
	gameNode::init(true);
	// fadein out 효과에 자주 쓰임
	IMAGEMANAGER->addImage("검은배경", "image/ui/bgblack.bmp", WINSIZEX, WINSIZEY, false, RGB(255, 0, 255), true);
	SCENEMANAGER->addScene("메인메뉴", new mainMenu);
	SCENEMANAGER->addScene("노말스테이지", new nomalStage);
	SCENEMANAGER->addScene("시작스테이지", new startStage);
	SCENEMANAGER->addScene("스테이지1", new stage1);
	SCENEMANAGER->addScene("스테이지2", new stage2);
	SCENEMANAGER->addScene("스테이지3", new stage3);
	SCENEMANAGER->addScene("스테이지4", new stage4);
	SCENEMANAGER->addScene("스테이지5", new stage5);
	SCENEMANAGER->addScene("스테이지6", new stage6);
	SCENEMANAGER->addScene("보스스테이지", new bossStage);
	SCENEMANAGER->addScene("보스인트로", new bossIntro);
	SCENEMANAGER->setScene("메인메뉴");
	// 이펙트 추가
	EFFECTMANAGER->addEffect("teareffect7", "image/tear/effect/teareffect7.bmp", 1680, 105, 105, 105, 1, 0.5f, 50);
	EFFECTMANAGER->addEffect("bloodteareffect3", "image/tear/effect/bloodteareffect3.bmp", 1536, 96, 96, 96, 1, 0.5f, 50);
	EFFECTMANAGER->addEffect("coin1effect", "image/item/effect/coin1effect.bmp", 768, 128, 128, 128, 1, 0.3f, 20);
	EFFECTMANAGER->addEffect("poof_large", "image/effect/poof_large.bmp", 1530, 91, 102, 91, 1, 0.6f, 20);
	EFFECTMANAGER->addEffect("bloodpoof1", "image/effect/bloodpoof1.bmp", 1536, 128, 128, 128, 1, 0.5f, 50);
	EFFECTMANAGER->addEffect("bloodpoofalt1", "image/effect/bloodpoofalt1.bmp", 2048, 128, 128, 128, 1, 0.5f, 50);
	EFFECTMANAGER->addEffect("bloodpoof3", "image/effect/bloodpoof3.bmp", 3840, 200, 320, 200, 1, 0.5f, 20);
	EFFECTMANAGER->addEffect("bombeffect", "image/effect/bombeffect.bmp", 2304, 192, 192, 192, 1, 0.4f, 10);
	EFFECTMANAGER->addEffect("item_poof", "image/effect/item_poof.bmp", 2048, 128, 128, 128, 1, 0.4f, 20);
	EFFECTMANAGER->addEffect("mini_poof", "image/effect/mini_poof.bmp", 1024, 64, 64, 64, 1, 0.1f, 20);
	EFFECTMANAGER->addEffect("poof_boss", "image/effect/poof_boss.bmp", 4096, 256, 256, 256, 1, 0.5f, 20);

	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();
	if (KEYMANAGER->isOnceKeyDown('R')) {
		EFFECTMANAGER->release();
		init();
		SCENEMANAGER->restart();
		SCENEMANAGER->setScene("시작스테이지");
	}
	SCENEMANAGER->update();
	
}


void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	// 위에 건들지마라
	//================제발 이 사이에 좀 그립시다==========================	
	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	//==================================================
	//여기도 건들지마라
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
