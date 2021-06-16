#include "stdafx.h"
#include "grid.h"

HRESULT grid::init()
{
	return S_OK;
}

void grid::release()
{
}

void grid::update()
{
}

void grid::render()
{
	for (int i = 0; i < 12; i++) 
	{
		if (KEYMANAGER->isToggleKey(VK_TAB))
		Rectangle(getMemDC(),_wall[i].rc);
	}
	rendDoor();
	for (int i = 0; i < MAX_GRID; i++)
	{
		if (KEYMANAGER->isToggleKey(VK_TAB))
			Rectangle(getMemDC(), _grid[i].rc);
		if (_grid[i].gridv == GRIDROCK)
		RENDERMANAGER->pushBackFrameRenderInfo(_grid[i].y + 23, "rocks", _grid[i].x - 4, _grid[i].y - 18, _grid[i].frameX, _grid[i].frameY);
		if (_grid[i].gridv == GRIDDESTROYEDROCK) 
			RENDERMANAGER->pushBackFrameRenderInfo(0, "rocks", _grid[i].x - 4, _grid[i].y - 18, 3, 0);
		
	}
}

// 벽 만들기
void grid::makeWall(float x, float y)
{
	tagTILE wall;
	ZeroMemory(&wall, sizeof(tagTILE));
	wall.rc = RectMake(x, y, 440, 111);
	_wall[0] = wall;
	wall.rc = RectMake(x+440+56, y, 440, 111);
	_wall[1] = wall;
	wall.rc = RectMake(x, y, 936, 54);
	_wall[2] = wall;

	wall.rc = RectMake(x, y, 102, 279);
	_wall[3] = wall;
	wall.rc = RectMake(x, y + 279 + 56, 102, 279);
	_wall[4] = wall;
	wall.rc = RectMake(x, y, 46, 614);
	_wall[5] = wall;

	wall.rc = RectMake(x, y + 510 - 7, 440, 111);
	_wall[6] = wall;
	wall.rc = RectMake(x + 440 + 56, y + 510 - 7, 440, 111);
	_wall[7] = wall;
	wall.rc = RectMake(x, y + 510 + 54, 936, 54);
	_wall[8] = wall;

	wall.rc = RectMake(x + 834, y, 102, 279);
	_wall[9] = wall;
	wall.rc = RectMake(x + 834, y + 279 + 56, 102, 279);
	_wall[10] = wall;
	wall.rc = RectMake(x + 834 + 56, y, 46, 614);
	_wall[11] = wall;
	
}

// 문만들기 
void grid::makeDoor(float x, float y)
{
	tagTILE door;
	ZeroMemory(&door, sizeof(tagTILE));
	// 위
	door.gridv = GRIDDOOR;
	door.rc = RectMake(x, y, 936, 111);
	door.isOpen = true;
	door.x = x + 440 - 37;
	door.y = y + 24;
	door.frameY = 0;
	door.doorInt = 0;
	_door[0] = door;
	// 아래
	door.gridv = GRIDDOOR;
	door.rc = RectMake(x, y + 510 - 7, 936, 111);
	door.isOpen = true;
	door.x = x + 440 - 37;
	door.y = y + 510  - 16;
	door.frameY = 1;

	_door[1] = door;

	// 왼쪽
	door.gridv = GRIDDOOR;
	door.rc = RectMake(x, y, 102, 614);
	door.isOpen = true;
	door.x = x + 24;
	door.y = y + 244;
	door.frameY = 0;

	_door[2] = door;
	// 오른쪽
	door.gridv = GRIDDOOR;
	door.rc = RectMake(x + 834, y, 102, 614);
	door.isOpen = true;
	door.x = x + 816;
	door.y = y + 244;
	door.frameY = 1;

	_door[3] = door;
}

// 그리드 구성
void grid::makeGrid(float x, float y)
{
	x += 104;
	y += 111;

	for (int i = 0; i < MAX_GRID; i++)
	{
		tagTILE tgrid;
		ZeroMemory(&tgrid, sizeof(tagTILE));
		tgrid.gridv = GRIDEMPTY;
		tgrid.x = x + ((i % GRID_WIDTH) * 56);
		tgrid.y = y + ((i / GRID_WIDTH) * 56);
		tgrid.rc = RectMake(tgrid.x, tgrid.y, 56, 56);
		tgrid.frameY = 0;
		tgrid.frameX = 0;
		_grid[i] = tgrid;
	}
}

// 돌만들기
void grid::makeRock(int x, int y)
{
	int idx = x + y * GRID_WIDTH;
	_grid[idx].frameX = RND->getFromIntTo(0, 3);
	_grid[idx].gridv = GRIDROCK;
}

// 돌무더기 만들기
void grid::makeRocks(int x1, int y1, int x2, int y2)
{
	for (int i = x1; i < x2+1; i++) 
	{
		for (int j = y1; j < y2+1; j++)
		{
			int idx = i + j * GRID_WIDTH;
			_grid[idx].frameX = RND->getFromIntTo(0, 3);
			_grid[idx].gridv = GRIDROCK;
		}
	}
	
}

// 도어 렌더
void grid::rendDoor()
{
	for (int i = 0; i < 4; i++)
	{
		if (KEYMANAGER->isToggleKey('T'))
			Rectangle(getMemDC(), _door[i].rc);
		switch (_door[i].gridv)
		{
		case GRIDEMPTY:
			break;
		case GRIDDOOR:
			if (_door[i].isOpen)
			{
				if (i < 2) 
				{
					RENDERMANAGER->pushBackFrameRenderInfo(0, "doorUD", _door[i].x, _door[i].y, 0, _door[i].frameY);
					RENDERMANAGER->pushBackFrameRenderInfo(0, "doorUD", _door[i].x, _door[i].y, 1, _door[i].frameY);
				}
				else 
				{
					RENDERMANAGER->pushBackFrameRenderInfo(0, "doorLR", _door[i].x, _door[i].y, 0, _door[i].frameY);
					RENDERMANAGER->pushBackFrameRenderInfo(0, "doorLR", _door[i].x, _door[i].y, 1, _door[i].frameY);
				}
			}
			else
			{
				if (i < 2)
				{
					RENDERMANAGER->pushBackFrameRenderInfo(0, "doorUD", _door[i].x, _door[i].y, 0, _door[i].frameY);
					RENDERMANAGER->pushBackFrameRenderInfo(0, "doorUD", _door[i].x - _door[i].doorInt, _door[i].y , 2, _door[i].frameY);
					RENDERMANAGER->pushBackFrameRenderInfo(0, "doorUD", _door[i].x + _door[i].doorInt, _door[i].y , 3, _door[i].frameY);
					RENDERMANAGER->pushBackFrameRenderInfo(0, "doorUD", _door[i].x, _door[i].y, 1, _door[i].frameY);
				}
				else 
				{
					RENDERMANAGER->pushBackFrameRenderInfo(0, "doorLR", _door[i].x, _door[i].y, 0, _door[i].frameY);
					RENDERMANAGER->pushBackFrameRenderInfo(0, "doorLR", _door[i].x , _door[i].y + _door[i].doorInt, 2, _door[i].frameY);
					RENDERMANAGER->pushBackFrameRenderInfo(0, "doorLR", _door[i].x , _door[i].y - _door[i].doorInt, 3, _door[i].frameY);
					RENDERMANAGER->pushBackFrameRenderInfo(0, "doorLR", _door[i].x, _door[i].y, 1, _door[i].frameY);
				
				}
			}
			break;
		case GRIDBOSSDOOR:
			if (_door[i].isOpen)
			{
				if (i < 2)
				{
					RENDERMANAGER->pushBackFrameRenderInfo(0, "bossdoorUD", _door[i].x, _door[i].y, 0, _door[i].frameY);
					RENDERMANAGER->pushBackFrameRenderInfo(0, "bossdoorUD", _door[i].x, _door[i].y, 1, _door[i].frameY);
				}
				else
				{
					RENDERMANAGER->pushBackFrameRenderInfo(0, "bossdoorLR", _door[i].x, _door[i].y, 0, _door[i].frameY);
					RENDERMANAGER->pushBackFrameRenderInfo(0, "bossdoorLR", _door[i].x, _door[i].y, 1, _door[i].frameY);
				}
			}
			else
			{
				if (i < 2)
				{
					RENDERMANAGER->pushBackFrameRenderInfo(0, "bossdoorUD", _door[i].x, _door[i].y, 0, _door[i].frameY);
					RENDERMANAGER->pushBackFrameRenderInfo(0, "bossdoorUD", _door[i].x - _door[i].doorInt, _door[i].y, 2, _door[i].frameY);
					RENDERMANAGER->pushBackFrameRenderInfo(0, "bossdoorUD", _door[i].x + _door[i].doorInt, _door[i].y, 3, _door[i].frameY);
					RENDERMANAGER->pushBackFrameRenderInfo(0, "bossdoorUD", _door[i].x, _door[i].y, 1, _door[i].frameY);
				}
				else
				{
					RENDERMANAGER->pushBackFrameRenderInfo(0, "bossdoorLR", _door[i].x, _door[i].y, 0, _door[i].frameY);
					RENDERMANAGER->pushBackFrameRenderInfo(0, "bossdoorLR", _door[i].x, _door[i].y + _door[i].doorInt, 2, _door[i].frameY);
					RENDERMANAGER->pushBackFrameRenderInfo(0, "bossdoorLR", _door[i].x, _door[i].y - _door[i].doorInt, 3, _door[i].frameY);
					RENDERMANAGER->pushBackFrameRenderInfo(0, "bossdoorLR", _door[i].x, _door[i].y, 1, _door[i].frameY);

				}
			}
			break;
		default:
			break;
		}
	}
}
	
