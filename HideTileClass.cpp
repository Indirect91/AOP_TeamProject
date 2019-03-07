#include "stdafx.h"
#include "HideTileClass.h"
#include "PlayerClass.h"
HRESULT HideTileClass::init(HideTile Stage)
{
	light = IMAGEMANAGER->findImage("변신타일");
	Boom = IMAGEMANAGER->findImage("폭발");

	switch (Stage)
	{
	case HideTileClass::HideTile::Stage1:
		break;
	case HideTileClass::HideTile::BossStage:
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				hide.rc = RectMake(8834 + (j * 46), 1332 + (i * 45), 46, 45);
				hide.isTouch = true;
				HideList.push_back(hide);
			}
		}
		frameImgX = 0;
		frameImgY = 0;
		Count = 0;
		BoomFrameX = 0;
		BoomFrameY = 0;
		isBoom = true;
		break;
	}

	return S_OK;
}

void HideTileClass::release(void)
{
}

void HideTileClass::update(PlayerClass * player)
{
	Count++;
	if (Count % 5 == 0)
	{
		frameImgX++;
		if (frameImgX > 27)
		{
			frameImgX = 0;
		}
		Count = 0;
	}
	

	if (Count % 5 == 0)
	{
		BoomFrameX++;
		if (BoomFrameX > 12)
		{
			BoomFrameX = 0;
			isBoom = true;
		}
		Count = 0;
	}
	
	
	
	for (int i = 0; i < HideList.size(); i++)
	{
		if (player->getX() < 8171)
		{
			HideList[i].isTouch = true;
			isBoom = true;
			frameImgX = 0;
			BoomFrameX = 0;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('Y'))
	{
		for (int i = 0; i < HideList.size(); i++)
		{
			HideList[i].isTouch = false;
			isBoom = false;
		}
	}
	
}

void HideTileClass::render(void)
{
	for (int i = 0; i < HideList.size(); i++)
	{
		//Rectangle(getMemDC(), RelativeCameraRect(HideList[i].rc));
		if (HideList[i].isTouch == true)
		{
			light->frameRender(getMemDC(), HideList[i].rc.left - CAMERA.getCRc().left, HideList[i].rc.top - CAMERA.getCRc().top, frameImgX, frameImgY);
		}
		if (HideList[i].isTouch == false && isBoom == false)
		{
			Boom->frameRender(getMemDC(), HideList[i].rc.left - CAMERA.getCRc().left, HideList[i].rc.top - CAMERA.getCRc().top, BoomFrameX, BoomFrameY);
		}
	}
	
}
