#include "stdafx.h"
#include "WorldMapScene.h"

HRESULT WorldMapScene::init(void)
{
	StageBar = IMAGEMANAGER->findImage("상단바");
	MenuBar = IMAGEMANAGER->findImage("하단바");
	WorldMap = IMAGEMANAGER->findImage("전체");
	return S_OK;
}

void WorldMapScene::release(void)
{
}

void WorldMapScene::update(void)
{
}

void WorldMapScene::render(void)
{
	WorldMap->render(getMemDC(), 0, 0);
	StageBar->render(getMemDC(), 80, 0);
	MenuBar->render(getMemDC(), 70, 700);
}
