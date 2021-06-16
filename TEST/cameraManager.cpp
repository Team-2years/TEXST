#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init(int width, int height)
{	
	//backDC와 frontDC크기 설정
	_backWidth = width;
	_backHeight = height;
	_frontWidth = WINSIZEX;
	_frontHeight = WINSIZEY;
	//화면 Rect 생성
	_screen = RectMake(0, 0, WINSIZEX, WINSIZEY);

	return S_OK;
}

void cameraManager::release()
{
}

void cameraManager::updateScreen(float standardX, float standardY, float ratioX, float ratioY)
{
	//플레이어 기준으로 화면(_screen)갱신
	//playground.cpp의 update()에서 계속 갱신해주면 됨
	//인수로 기준이 되는 객체의 x, y좌표를 받음(현재는 player의 x, y)

	//X축 (좌, 우)
	if (standardX - _frontWidth * ratioX < 0)
		standardX = 0;
	else if (standardX + _frontWidth * (1 - ratioX) > _backWidth)
		standardX = _backWidth - _frontWidth;
	else
		standardX -= _frontWidth * ratioX;
	//Y축 (상, 하)
	if (standardY - _frontHeight * ratioY < 0)
		standardY = 0;
	else if (standardY + _frontHeight * (1 - ratioY) > _backHeight)
		standardY = _backHeight - _frontHeight;
	else
		standardY -= _frontHeight * ratioY;

	//갱신
	_screen = RectMake(standardX, standardY, _frontWidth, _frontHeight);
}

void cameraManager::render(HDC frontDC, int destX, int destY, HDC backDC, bool map, bool mini)
{
	/********* 인수 설명 *********/ /*
	HDC frontDC: 복사를 받을 DC (실제로 우리가 보는 화면)
	int destX: 우리가 보는 화면에서 출력해줄 x좌표
	int destY: 우리가 보는 화면에서 출력해줄 y좌표
	HDC backDC: 복사해 올 DC (실제로 우리가 그리는 화면)
	bool map: true면 전체맵 출력, false면 안 출력
	bool mini: true면 미니맵 출력, false면 안 출력
	*/

	if (map) {
		StretchBlt(
			backDC,
			_screen.left,
			_screen.top,
			_frontWidth,
			_frontHeight,
			backDC,
			0,
			0,
			_backWidth,
			_backHeight,
			SRCCOPY);
	}
	//미니맵 변수가 true면 스크린의 우측상단에 미니맵 출력
	else if (mini) {
		StretchBlt(
			backDC,
			_screen.right - _frontWidth / 4,
			_screen.top,
			_frontWidth / 4,
			_frontHeight / 5,
			backDC,
			_screen.left,
			_screen.top,
			_frontWidth,
			_frontHeight,
			SRCCOPY);
	}
	//DC영역간의 고속복사를 해줌(화면 깜빡임 방지)
	BitBlt(
		frontDC,				//복사받는 DC
		destX,					//복사받는 좌표(left)
		destY,					//복사받는 좌표(top)
		_frontWidth,			//복사되는 가로크기
		_frontHeight,			//복사되는 세로크기
		backDC,					//복사되는 DC
		_screen.left, _screen.top,	//복사되는 시작좌표(left, top)
		SRCCOPY);				//그대로 복사해오기(모드)
}