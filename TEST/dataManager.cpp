#include "stdafx.h"
#include "dataManager.h"

HRESULT dataManager::init()
{
	_ix = 0;
	_iy = 0;
	_tx = 0;
	_ty = 0;
	_isClearBoss = false;
	_bossHp = 0;
	_bossMaxHp = 0;
	_isaac_innereye = false;
	_isaac_lokishorns = false;
	_isaac_wirehanger = false;
	_isaac_jesusjuice = false;
	_isaac_mutantspider = false;
	_isaac_halo = false;
	return S_OK;
}
