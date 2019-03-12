#include "stdafx.h"
#include "WorldMapScene.h"

HRESULT WorldMapScene::init(void)
{
	WorldMap = IMAGEMANAGER->findImage("WorldMap");
	MenuBar = IMAGEMANAGER->findImage("WorldMapLow");
	StageBar = IMAGEMANAGER->findImage("WorldMapHigh");

	StageBar->setX(WINSIZEX / 2 - StageBar->getWidth() / 2);
	StageBar->setY(40);

	MenuBar->setX(WINSIZEX / 2 - MenuBar->getWidth() / 2);
	MenuBar->setY(WINSIZEY-140);

	worldMapZoom = 1.f;
	totalAlpha = 0;

	firstPhase = false;
	SecondPhase = false;
	FinalPhase = false;
	zoomToggle = false;
	zooming = false;
	counter = 0;

	return S_OK;
}

void WorldMapScene::release(void)
{
	//뉴할당 받은거 없으니 비워둡니다
}

void WorldMapScene::update(void)
{
	counter++;
	
	if (!FinalPhase && totalAlpha != 255) totalAlpha += 15;
	if (counter > 18) firstPhase = true;

	if (firstPhase)
	{
		if (KEYMANAGER->isStayKeyDown('Y') && zooming == false&& zoomToggle ==false)
		{
			zoomToggle = true;
		}
		else if (KEYMANAGER->isStayKeyDown('Y') && zooming == false && zoomToggle == true)
		{
			zoomToggle = false;
		}

		if(worldMapZoom<=1.00f || worldMapZoom>=2.0f) zooming = false;

		if (zoomToggle)
		{
			if (worldMapZoom > 1.00f)
			{
				worldMapZoom -= 0.05f;
				zooming = true;
			}
		}
		else
		{
			if (worldMapZoom < 2.00f)
			{
				worldMapZoom += 0.05f;
				zooming = true;
			}
		}
	}

}

void WorldMapScene::render(void)
{
	if(!firstPhase)
		WorldMap->alphaRender(getMemDC(), WorldMap->getX(), WorldMap->getY(), totalAlpha);
	else
		WorldMap->stretchRenderCenterXCenterY(getMemDC(), WorldMap->getX(), WorldMap->getY(), worldMapZoom);

	StageBar->stretchRender(getMemDC(), StageBar->getX(), StageBar->getY());
	MenuBar->stretchRender(getMemDC(), MenuBar->getX(), MenuBar->getY());
}
