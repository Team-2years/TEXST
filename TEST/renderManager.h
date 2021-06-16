#pragma once
#include "singletonBase.h"
using namespace std;

struct renderInfo 
{
	//그려줄 좌표
	float x, y;
	// 스트링 키
	const char* strkey;
	//leftTop인가?
	bool leftTop;
	// 블랜드 할것인가?
	bool blend;
	// 프레임이미지 인가?
	bool isFrame;
	// 블랜드 값
	BYTE alpha;
	// 프레임 정보
	// 프레임 값
	int frameX;
	int frameY;
	// 애니메이션 렌더 인가?
	bool isAni;
	image* img;
	animation* ani;

};


class renderManager : public singletonBase<renderManager>
{
private:
	//first 그림자의 중앙값을 저장을 float
	//second 그려줄 정보
	typedef vector<pair<float, renderInfo>>				renderList;
	typedef vector<pair<float, renderInfo>>::iterator	renderIter;
private:
	renderList _mRenderList;

	float _cameraX;
	float _cameraY;
public:
	renderManager() {}
	~renderManager() {}

	void mergeSort(vector<pair<float, renderInfo>>& v, int s, int e);
	void merge(vector<pair<float, renderInfo>>& v, int s, int e, int m);

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	
	void pushBackFrameRenderInfo(float middle, const char* strkey, float x, float y, bool leftTop = true, bool blend = false, BYTE alpha = 255);
	void pushBackFrameRenderInfo(float middle, const char* strkey, float x, float y, int frameX, int frameY, bool leftTop = true, bool blend = false, BYTE alpha = 255);
	void pushBackRenderInfo(float middle, const char* strkey, float x, float y, bool leftTop = true, bool blend = false,  BYTE alpha = 255);
	void pushBackAniRenderInfo(float middle, image* imgname, float x, float y, animation* ani, bool leftTop = true, bool blend = false, BYTE alpha = 255);

	void setCameraX(float num) { _cameraX = num; }
	float getCameraX() { return _cameraX; }
	void setCameraY(float num) { _cameraY = num; }
	float getCameraY() { return _cameraY; }

	
};

