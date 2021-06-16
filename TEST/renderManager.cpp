#include "stdafx.h"
#include "renderManager.h"

#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;

HRESULT renderManager::init()
{
	_cameraX = 0;
	_cameraY = 0;
	return S_OK;
}

void renderManager::release()
{
}

void renderManager::update()
{
}


// sort 비교함수
bool compare(pair<float, renderInfo> a, pair<float, renderInfo> b) 
{
	return a.first < b.first;
}

void renderManager::render(HDC hdc)
{
	// z오더 ? 순으로 정렬
	// 알고리즘헤더를 사용하여 비교함수를 썻을 경우 정렬이 되지만 퀵정렬은 불안정 정렬 이므로 순서가 뒤바뀔 가능성이 있다.
	//sort(_mRenderList.begin(), _mRenderList.end(), compare);
	mergeSort(_mRenderList, 0, _mRenderList.size()-1);
	for (renderIter iter = _mRenderList.begin(); iter != _mRenderList.end(); iter++) 
	{
		if (iter->second.isFrame) // 프레임 이미지 렌더할 경우
		{
			if (iter->second.blend) 
			{
				if (iter->second.leftTop)
				{
					if (iter->second.frameX == -1 && iter->second.frameY == -1)
						IMAGEMANAGER->findImage(iter->second.strkey)->alphaFrameRender(hdc, iter->second.x + _cameraX, iter->second.y + _cameraY, iter->second.alpha);
					else
						IMAGEMANAGER->findImage(iter->second.strkey)->alphaFrameRender(hdc, iter->second.x + _cameraX, iter->second.y + _cameraY, iter->second.frameX, iter->second.frameY, iter->second.alpha);
				}
				else
				{
					if (iter->second.frameX == -1 && iter->second.frameY == -1)
						IMAGEMANAGER->findImage(iter->second.strkey)->alphaFrameRender(hdc, iter->second.x + _cameraX - IMAGEMANAGER->findImage(iter->second.strkey)->getFrameWidth() / 2, iter->second.y + _cameraY - IMAGEMANAGER->findImage(iter->second.strkey)->getFrameHeight() / 2, iter->second.alpha);
					else
						IMAGEMANAGER->findImage(iter->second.strkey)->alphaFrameRender(hdc, iter->second.x + _cameraX - IMAGEMANAGER->findImage(iter->second.strkey)->getFrameWidth() / 2, iter->second.y + _cameraY - IMAGEMANAGER->findImage(iter->second.strkey)->getFrameHeight() / 2, iter->second.frameX, iter->second.frameY, iter->second.alpha);
				}
			}
			else 
			{
				if (iter->second.leftTop) 
				{
					if(iter->second.frameX == -1 && iter->second.frameY == -1)
					IMAGEMANAGER->findImage(iter->second.strkey)->frameRender(hdc, iter->second.x + _cameraX, iter->second.y + _cameraY);
					else
					IMAGEMANAGER->findImage(iter->second.strkey)->frameRender(hdc, iter->second.x + _cameraX, iter->second.y + _cameraY, iter->second.frameX, iter->second.frameY);
				}
				else 
				{
					if (iter->second.frameX == -1 && iter->second.frameY == -1)
					IMAGEMANAGER->findImage(iter->second.strkey)->frameRender(hdc, iter->second.x + _cameraX - IMAGEMANAGER->findImage(iter->second.strkey)->getFrameWidth() / 2, iter->second.y + _cameraY - IMAGEMANAGER->findImage(iter->second.strkey)->getFrameHeight() / 2);
					else
					IMAGEMANAGER->findImage(iter->second.strkey)->frameRender(hdc, iter->second.x + _cameraX - IMAGEMANAGER->findImage(iter->second.strkey)->getFrameWidth() / 2, iter->second.y + _cameraY - IMAGEMANAGER->findImage(iter->second.strkey)->getFrameHeight() / 2, iter->second.frameX, iter->second.frameY);
				}
			}
		}
		else if (iter->second.isAni) 
		{
			if (iter->second.blend)
			{
				if (iter->second.leftTop)
				{

				}
				else
				{

				}
			}
			else 
			{
				if (iter->second.leftTop)
				{
					
					iter->second.img->aniRender(hdc, iter->second.x + _cameraX, iter->second.y + _cameraY, iter->second.ani);
				}
				else
				{
					iter->second.img->aniRender(hdc, iter->second.x + _cameraX - iter->second.img->getFrameWidth()/2, iter->second.y + _cameraY, iter->second.ani);
				}
			}
			
		}
		else // 이미지 렌더할 경우
		{
			if (iter->second.blend)
			{
				
				if (iter->second.leftTop)
					IMAGEMANAGER->findImage(iter->second.strkey)->alphaRender(hdc, iter->second.x + _cameraX, iter->second.y + _cameraY, iter->second.alpha);
				else
					IMAGEMANAGER->findImage(iter->second.strkey)->alphaRender(hdc, iter->second.x - IMAGEMANAGER->findImage(iter->second.strkey)->getWidth()/2, iter->second.y - IMAGEMANAGER->findImage(iter->second.strkey)->getHeight() / 2, iter->second.alpha);
			}
			else
			{
				if (iter->second.leftTop)
					IMAGEMANAGER->findImage(iter->second.strkey)->render(hdc, iter->second.x + _cameraX, iter->second.y + _cameraY);
				else
					IMAGEMANAGER->findImage(iter->second.strkey)->render(hdc, iter->second.x + _cameraX - IMAGEMANAGER->findImage(iter->second.strkey)->getWidth() / 2, iter->second.y + _cameraY - IMAGEMANAGER->findImage(iter->second.strkey)->getHeight() / 2);

			}
		}
	}
	_mRenderList.clear();
	_mRenderList.resize(0);
}

void renderManager::pushBackFrameRenderInfo(float middle, const char* strkey, float x, float y, bool leftTop, bool blend, BYTE alpha)
{
	renderInfo rdInfo;
	ZeroMemory(&rdInfo, sizeof(renderInfo));
	rdInfo.strkey = strkey;
	rdInfo.x = x;
	rdInfo.y = y;
	rdInfo.leftTop = leftTop;
	rdInfo.blend = blend;
	rdInfo.isFrame = true;
	rdInfo.alpha = alpha;
	rdInfo.frameX = -1;
	rdInfo.frameY = -1;
	_mRenderList.push_back(make_pair(middle, rdInfo));
}

void renderManager::pushBackFrameRenderInfo(float middle, const char* strkey, float x, float y,  int frameX, int frameY, bool leftTop, bool blend, BYTE alpha)
{
	renderInfo rdInfo;
	ZeroMemory(&rdInfo, sizeof(renderInfo));
	rdInfo.strkey = strkey;
	rdInfo.x = x;
	rdInfo.y = y;
	rdInfo.leftTop = leftTop;
	rdInfo.blend = blend;
	rdInfo.isFrame = true;
	rdInfo.alpha = alpha;
	rdInfo.frameX = frameX;
	rdInfo.frameY = frameY;
	_mRenderList.push_back(make_pair(middle, rdInfo));
}

void renderManager::pushBackRenderInfo(float middle, const char* strkey, float x, float y, bool leftTop, bool blend,  BYTE alpha)
{
	renderInfo rdInfo;
	ZeroMemory(&rdInfo, sizeof(renderInfo));
	rdInfo.strkey = strkey;
	rdInfo.x = x;
	rdInfo.y = y;
	rdInfo.leftTop = leftTop;
	rdInfo.blend = blend;
	rdInfo.isFrame = false;
	rdInfo.alpha = alpha;

	_mRenderList.push_back(make_pair(middle, rdInfo));
}

void renderManager::pushBackAniRenderInfo(float middle, image* imgname, float x, float y, animation* ani, bool leftTop, bool blend, BYTE alpha)
{
	
	renderInfo rdInfo;
	ZeroMemory(&rdInfo, sizeof(renderInfo));
	rdInfo.img = imgname;
	rdInfo.ani = ani;
	rdInfo.x = x;
	rdInfo.y = y;
	rdInfo.isAni = true;
	rdInfo.isFrame = false;
	rdInfo.leftTop = leftTop;
	rdInfo.blend = blend;
	rdInfo.alpha = alpha;

	_mRenderList.push_back(make_pair(middle, rdInfo));
}

void renderManager::mergeSort(vector<pair<float, renderInfo>>& v, int s, int e)
{
	if (s >= e) return;

	int m = (s + e) / 2;
	// divide
	mergeSort(v, s, m); // s ~ m
	mergeSort(v, m + 1, e); // m+1 ~ e

	// conquer
	merge(v, s, e, m);
}

void renderManager::merge(vector<pair<float, renderInfo>>& v, int s, int e, int m)
{
	vector<pair<float, renderInfo>> ret(e+1);
	int ret_idx = 0;
	int firstidx = s;
	int secondidx = m + 1;

	while (firstidx <= m && secondidx <= e)
	{
		if (v[firstidx].first < v[secondidx].first) ret[ret_idx++] = v[firstidx++];
		else ret[ret_idx++] = v[secondidx++];
	}

	while (firstidx <= m) ret[ret_idx++] = v[firstidx++];
	while (secondidx <= e) ret[ret_idx++] = v[secondidx++];

	for (int k = s, ret_idx = 0; k <= e; k++, ret_idx++) 
		v[k] = ret[ret_idx];
}

