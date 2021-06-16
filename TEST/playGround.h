#pragma once
#include "gameNode.h"
#include "nomalStage.h"
#include "startStage.h"
#include "mainMenu.h"
#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "stage4.h"
#include "stage5.h"
#include "stage6.h"
#include "bossStage.h"
#include "bossIntro.h"
class playGround : public gameNode
{
private:


public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	
};

