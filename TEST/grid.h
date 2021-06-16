#pragma once
#include "gameNode.h"

// 그리드 높이 너비
#define GRID_WIDTH 13
#define GRID_HEIGHT 7
// 최대 그리드
#define MAX_GRID GRID_WIDTH * GRID_HEIGHT

// 그리드에 어떤 값이 담기고 있뉘?
enum GridVal
{
    GRIDEMPTY,
    GRIDROCK,
    GRIDDOOR,
    GRIDBOSSDOOR,
    GRIDPOT,
    GRIDPOOP,
    GRIDDESTROYEDROCK
};

struct tagTILE
{
    GridVal gridv;
    int x, y;
    int frameX;
    int frameY;
    RECT rc;
	bool isOpen;
    int doorInt;
};

class grid :
    public gameNode
{
private:
   tagTILE _wall[12];
   tagTILE _door[4];
   tagTILE _grid[91];


public:
    grid() {}
    ~grid() {}

    virtual HRESULT init();
    virtual void release();
    virtual void update();
    virtual void render();

    void makeWall(float x, float y);
	tagTILE* getWall() { return &_wall[0]; }
	void makeDoor(float x, float y);
	tagTILE* getDoor() { return &_door[0]; }
	void makeGrid(float x, float y);
	void makeRock(int x, int y);
	void makeRocks(int x1, int y1, int x2, int y2);
	tagTILE* getGrid() { return &_grid[0]; }
	void rendDoor();
};

