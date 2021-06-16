#include "stdafx.h"
#include "item.h"

HRESULT item::init(const char* itemName, float x, float y, itemVal it)
{
	_x = x;
	_y = y;
	_itemY = _y - 45;
	_count = 0;
	_itemName = itemName;
	_imageName = IMAGEMANAGER->findImage(_itemName);
	_itemVal = it;
	_itemRect = RectMakeCenter(_x, _itemY, _imageName->getWidth(), _imageName->getHeight() );
	_rc = RectMakeCenter(_x, _y + 20, _imageName->getWidth()-10, _imageName->getHeight() - 40);
	return S_OK;
}

void item::release()
{
}

void item::update()
{
	if (_itemFrameCount > 0) 
	{
		_itemFrameCount--;
	}
	if (_count > 120)
		_count = 0;
	else if (_count > 60)
		_itemY -= 0.1;
	else if (_count > 0)
		_itemY += 0.1;
	_count++;
	_itemRect = RectMakeCenter(_x, _itemY, _imageName->getWidth(), _imageName->getHeight());
}

void item::render()
{
	if (KEYMANAGER->isToggleKey(VK_TAB)) 
	{
		Rectangle(getMemDC(), _rc);
	}
	
	if (_itemVal != EMPTY) {
		RENDERMANAGER->pushBackRenderInfo((_rc.top + _rc.bottom) / 2, _itemName, _itemRect.left, _itemRect.top);
		RENDERMANAGER->pushBackRenderInfo((_rc.top + _rc.bottom) / 2, "itemShadow", _rc.left + 12, _rc.top - 15);
	}
	RENDERMANAGER->pushBackRenderInfo((_rc.top + _rc.bottom) / 2, "prop", _rc.left - 5, _rc.top - 30);

}
