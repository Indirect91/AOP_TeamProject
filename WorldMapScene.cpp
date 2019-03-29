#include "stdafx.h"
#include "WorldMapScene.h"

void WorldMapScene::movePipRight()
{
	rightCounter++;

	if (rightCounter <= 60)
	{
		//isLeft = false;
		WorldPip->setX(WorldPip->getX() + 1);
	}
	else if (rightCounter > 60)
	{
		right = false;
	}

}

void WorldMapScene::movePipLeft()
{
	leftCounter++;

	if (leftCounter <= 60)
	{
		//isLeft = true;
		WorldPip->setX(WorldPip->getX() - 1);
	}
	else if (leftCounter > 60)
	{
		left = false;
	}
}

void WorldMapScene::movePipDown()
{

	downCounter++;

	if (downCounter <= 30)
	{
		WorldPip->setY(WorldPip->getY() + 1);
	}
	else if (downCounter > 30)
	{
		down = false;
	}

}

void WorldMapScene::movePipUp()
{
	upCounter++;

	if (upCounter <= 30)
	{
		WorldPip->setY(WorldPip->getY() - 1);
	}
	else if (upCounter > 30)
	{
		up = false;
	}
}

HRESULT WorldMapScene::init(void)
{
	//if(!(SOUNDMANAGER->isPlaySound("타이틀"))) 
		SOUNDMANAGER->play("타이틀");
	WorldMap = IMAGEMANAGER->findImage("WorldMap");
	MenuBar = IMAGEMANAGER->findImage("WorldMapLow");
	StageBar = IMAGEMANAGER->findImage("WorldMapHigh");
	WorldPip = IMAGEMANAGER->findImage("WorldMapPipIdle");
	WorldPip->setX(595);
	WorldPip->setY(494);
	isLeft = false;
	WorldPipRun = IMAGEMANAGER->findImage("WorldMapPipRun");

	StageBar->setX(WINSIZEX / 2 - StageBar->getWidth() / 2);
	StageBar->setY(40);

	MenuBar->setX(WINSIZEX / 2 - MenuBar->getWidth() / 2);
	MenuBar->setY(WINSIZEY - 140);

	worldMapZoom = 1.f;
	pipZoom = 1.f;
	totalAlpha = 0;

	firstPhase = false;
	SecondPhase = false;
	FinalPhase = false;
	zoomToggle = false;
	zooming = false;
	counter = 0;

	up = false;
	down = false;
	right = false;
	left = false;

	idlePipIndex = 2;
	runPipIndex = 2;
	isLeft = FALSE;


	return S_OK;
}

void WorldMapScene::release(void)
{
	//뉴할당 받은거 없으니 비워둡니다
}

void WorldMapScene::update(void)
{
	counter++;

	if (counter % 3 == 0)
	{
		runPipIndex++;
		idlePipIndex++;

		if (runPipIndex > 15) runPipIndex = 0;

		if (idlePipIndex > 12) idlePipIndex = 0;
	}




	if (!FinalPhase && totalAlpha != 255) totalAlpha += 15;
	if (counter > 18) firstPhase = true;

	if (firstPhase)
	{
		if (KEYMANAGER->isStayKeyDown(VK_RETURN))
		{
			if ((WorldPip->getX() == 595 && WorldPip->getY() == 494))
			{
				SOUNDMANAGER->pause("타이틀");
				SOUNDMANAGER->play("세이브", TXTDATA.refSFXSound());
				TXTDATA.getCurrentPipData()->pipCinematic = 1;
				SCENEMANAGER->loadScene("Village");
			}
			else if ((WorldPip->getX() == 655 && WorldPip->getY() == 494))
			{
				SOUNDMANAGER->play("세이브", TXTDATA.refSFXSound());
				TXTDATA.getCurrentPipData()->pipCinematic = 1;
				SOUNDMANAGER->pause("타이틀");
				SCENEMANAGER->loadScene("Stage1");
			}
			else if ((WorldPip->getX() == 715 && WorldPip->getY() == 524))
			{
				SOUNDMANAGER->play("세이브", TXTDATA.refSFXSound());
				TXTDATA.getCurrentPipData()->pipCinematic = 1;
				SOUNDMANAGER->pause("타이틀");
				SCENEMANAGER->loadScene("BossStage");
			}
		}




		if ((KEYMANAGER->isStayKeyDown('Y')) && zooming == false && zoomToggle == false)
		{
			zoomToggle = true;
		}
		else if (KEYMANAGER->isStayKeyDown('Y') && zooming == false && zoomToggle == true)
		{
			zoomToggle = false;
		}

		if (worldMapZoom <= 1.00f || worldMapZoom >= 2.0f) zooming = false;

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
			if (worldMapZoom < 3.00f)
			{
				worldMapZoom += 0.05f;
				zooming = true;
			}
		}

		if (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown('A'))
		{
			if ((WorldPip->getX() == 655 && WorldPip->getY() == 494) || (WorldPip->getX() == 715 && WorldPip->getY() == 524))
			{
				isLeft = true;
				left = true;
				leftCounter = 0;
			}
		}
		else if (KEYMANAGER->isStayKeyDown('D') || KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if ((WorldPip->getX() == 595 && WorldPip->getY() == 494) || (WorldPip->getX() == 655 && WorldPip->getY() == 524))
			{
				isLeft = false;
				right = true;
				rightCounter = 0;
			}
		}
		if (KEYMANAGER->isStayKeyDown('W') || KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if ((WorldPip->getX() == 655 && WorldPip->getY() == 524))
			{
				up = true;
				upCounter = 0;
			}

		}
		else if (KEYMANAGER->isStayKeyDown('S') || KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if ((WorldPip->getX() == 655 && WorldPip->getY() == 494))
			{
				down = true;
				downCounter = 0;
			}

		}
	}

	if (up)
	{
		movePipUp();
	}
	else if (down)
	{
		movePipDown();
	}
	else if (right)
	{
		movePipRight();
	}
	else if (left)
	{
		movePipLeft();
	}



	CAMERA.cameraFollow(WorldPip->getX(), WorldPip->getY());

	pipZoom = worldMapZoom * 0.3f;


}

void WorldMapScene::render(void)
{
	if (!firstPhase) WorldMap->alphaRender(getMemDC(), totalAlpha);
	else
		WorldMap->zoomCenterXCenterY(getMemDC(), CAMERA.getCX(), CAMERA.getCY(), worldMapZoom);


	//StageBar->stretchRender(getMemDC(), StageBar->getX(), StageBar->getY());
	MenuBar->stretchRender(getMemDC(), MenuBar->getX(), MenuBar->getY());
	if (right == 0 && left == 0 && up == 0 && down == 0)
		WorldPip->stretchFrameRender(getMemDC(), WorldPip->getX() - CAMERA.getCRc().left, WorldPip->getY() - CAMERA.getCRc().top, idlePipIndex, !isLeft, pipZoom);
	else
		WorldPipRun->stretchFrameRender(getMemDC(), WorldPip->getX() - CAMERA.getCRc().left, WorldPip->getY() - CAMERA.getCRc().top, runPipIndex, isLeft, pipZoom);

	//TextOutfloat(getMemDC(), 10, 10, "핍위치X", WorldPip->getX());
	//TextOutfloat(getMemDC(), 10, 30, "핍위치Y", WorldPip->getY());
	//TextOutfloat(getMemDC(), 10, 50, "카메라left", CAMERA.getCRc().left);
	//TextOutfloat(getMemDC(), 10, 70, "카메라top", CAMERA.getCRc().top);
	//TextOutfloat(getMemDC(), 10, 90, "저장", CAMERA.getCX() - 1366 / 2 / worldMapZoom);

}