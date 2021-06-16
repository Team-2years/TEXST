#pragma once
#include "singletonBase.h"
#include "image.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	//카메라가 비추는 화면 크기(WINSIZEX, WINSIZEY)와 좌표(left, right, top, bottom)
	RECT _screen;
	int _backWidth, _backHeight;	//backDC 크기
	int _frontWidth, _frontHeight;	//frontDC 크기

public:
	cameraManager();
	~cameraManager();

	HRESULT init(int width, int height);
	void release();

	//카메라 위치 갱신
	void updateScreen(float standardX, float standardY,
		float ratioX = 0.5f, float ratioY = 0.5f);
	//카메라 출력
	void render(HDC frontDC, int destX, int destY, HDC backDC, bool map = false, bool mini = false);
};

