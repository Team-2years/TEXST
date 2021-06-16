#pragma once
#include "gameNode.h"
#include "pickUpItem.h"
#include "coin.h"
#include "bomb.h"
#include "sparkBomb.h"
#include "key.h"
#include "heart.h"
#include "isaac.h"
#include "item.h"

class itemManager : public gameNode
{
private:
    // 픽업아이템의 벡터
    vector<pickUpItem*>				_vPick;
    vector<pickUpItem*>::iterator	_viPick;
    // 아이템의 벡터
    vector<item*>                   _vItem;
    vector<item*>::iterator         _viItem;
    // 터뜨릴 폭탄의 벡터
    vector<pickUpItem*>             _vBomb;
    vector<pickUpItem*>::iterator   _viBomb;
    // 충돌처리할 렉트
    RECT _temp;

    //
    bool _spaceItem;
public:
    itemManager() {}
    ~itemManager() {}

    virtual HRESULT init();
    virtual void release();
    virtual void update(isaac* _isaac);
    virtual void render();

    // 픽업 아이템 충돌 처리
    void isPickCollision(isaac* _isaac);
    // 아이템 충돌 처리
    void isItemCollision(isaac* _isaac);
    // 충돌처리할 폭탄 배열 넘길때 사용
    vector<pickUpItem*>* getVBomb() { return &_vBomb; }
    // 액티브 아이템 효과 처리
    void activeItemEffect(const char* itemName);
    void setCoin(int x, int y);
    void setBomb(int x, int y);
    void setKey(int x, int y);
    void setHeart(int x, int y);
    void setItem(const char* itemName, int x, int y, itemVal iv);
    void setItem(int x, int y);
    void setSparkBomb(int x, int y);
};

