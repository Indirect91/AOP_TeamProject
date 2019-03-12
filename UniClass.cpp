#include "stdafx.h"
#include "UniClass.h"
/*******************************************************************************************
## BreakTileClass ##
********************************************************************************************/
HRESULT BreakTileClass::init(BreakTile stage)
{
	StageNumber = stage;
	switch (StageNumber)
	{
	case BreakTileClass::BreakTile::Stage1:
		for (int i = 0; i < 8; i++)
		{
			tile = new Tile;
			tile->block = IMAGEMANAGER->findImage("무너지는타일");
			tile->point.x = 8716;
			tile->point.y = 469;
			tile->rc = RectMake(tile->point.x + (i * 41), tile->point.y, 41, 37);
			tile->isTouch = false;
			tile->isMode = true;
			tile->TouchCount = 4;
			tile->Count = 1;
			tile->FrameCount = 0;
			tile->FrameX = 0;
			tile->FrameY = 0;
			TileListone.push_back(tile);
		}
		for (int i = 0; i < 4; i++)
		{
			tile = new Tile;
			tile->block = IMAGEMANAGER->findImage("무너지는타일");
			tile->point.x = 9800;
			tile->point.y = 493;
			tile->rc = RectMake(tile->point.x + (i * 43), tile->point.y, 43, 37);
			tile->isMode = true;
			tile->isTouch = false;
			tile->TouchCount = 4;
			tile->Count = 1;
			tile->FrameCount = 0;
			tile->FrameX = 0;
			tile->FrameY = 0;
			TileListtwo.push_back(tile);
		}
		for (int i = 0; i < 4; i++)
		{
			tile = new Tile;
			tile->block = IMAGEMANAGER->findImage("무너지는타일");
			tile->point.x = 10083;
			tile->point.y = 430;
			tile->rc = RectMake(tile->point.x + (i * 43), tile->point.y, 43, 37);
			tile->isMode = true;
			tile->isTouch = false;
			tile->TouchCount = 4;
			tile->Count = 1;
			tile->FrameCount = 0;
			tile->FrameX = 0;
			tile->FrameY = 0;
			TileListthree.push_back(tile);
		}
		for (int i = 0; i < 8; i++)
		{
			tile = new Tile;
			tile->block = IMAGEMANAGER->findImage("무너지는타일");
			tile->point.x = 12179;
			tile->point.y = 407;
			tile->rc = RectMake(tile->point.x + (i * 43), tile->point.y, 43, 37);
			tile->isMode = true;
			tile->isTouch = false;
			tile->TouchCount = 4;
			tile->Count = 1;
			tile->FrameCount = 0;
			tile->FrameX = 0;
			tile->FrameY = 0;
			TileListfour.push_back(tile);
		}
		for (int i = 0; i < 8; i++)
		{
			tile = new Tile;
			tile->block = IMAGEMANAGER->findImage("무너지는타일");
			tile->point.x = 12350;
			tile->point.y = 259;
			tile->rc = RectMake(tile->point.x + (i * 43), tile->point.y, 43, 37);
			tile->isMode = true;
			tile->isTouch = false;
			tile->TouchCount = 4;
			tile->Count = 1;
			tile->FrameCount = 0;
			tile->FrameX = 0;
			tile->FrameY = 0;
			TileListfive.push_back(tile);
		}
		break;
	case BreakTileClass::BreakTile::BossStage:
		for (int i = 0; i < 4; i++)
		{
			tile = new Tile;
			tile->block = IMAGEMANAGER->findImage("무너지는타일");
			tile->point.x = 2479;
			tile->point.y = 344;
			tile->rc = RectMake(tile->point.x + (i * 43), tile->point.y, 43, 37);
			tile->isMode = true;
			tile->isTouch = false;
			tile->TouchCount = 4;
			tile->Count = 1;
			tile->FrameCount = 0;
			tile->FrameX = 0;
			tile->FrameY = 0;
			TileListBossone.push_back(tile);
		}
		for (int i = 0; i < 4; i++)
		{
			tile = new Tile;
			tile->block = IMAGEMANAGER->findImage("무너지는타일");
			tile->point.x = 3066;
			tile->point.y = 344;
			tile->rc = RectMake(tile->point.x + (i * 43), tile->point.y, 43, 37);
			tile->isMode = true;
			tile->isTouch = false;
			tile->TouchCount = 4;
			tile->Count = 1;
			tile->FrameCount = 0;
			tile->FrameX = 0;
			tile->FrameY = 0;
			TileListBosstwo.push_back(tile);
		}
		for (int i = 0; i < 9; i++)
		{
			tile = new Tile;
			tile->block = IMAGEMANAGER->findImage("무너지는타일");
			tile->point.x = 8452;
			tile->point.y = 2310;
			tile->rc = RectMake(tile->point.x + (i * 43), tile->point.y, 43, 37);
			tile->isMode = true;
			tile->isTouch = false;
			tile->TouchCount = 4;
			tile->Count = 1;
			tile->FrameCount = 0;
			tile->FrameX = 0;
			tile->FrameY = 0;
			TileListBossthree.push_back(tile);
		}
		for (int i = 0; i < 9; i++)
		{
			tile = new Tile;
			tile->block = IMAGEMANAGER->findImage("무너지는타일");
			tile->point.x = 8452;
			tile->point.y = 2310;
			tile->rc = RectMake(tile->point.x + (i * 43), tile->point.y, 43, 37);
			tile->isMode = true;
			tile->isTouch = false;
			tile->TouchCount = 4;
			tile->Count = 1;
			tile->FrameCount = 0;
			tile->FrameX = 0;
			tile->FrameY = 0;
			TileListBossfour.push_back(tile);
		}

		for (int i = 0; i < 1; i++)
		{
			TileListStage.push_back(&TileListone);
			TileListStage.push_back(&TileListtwo);
			TileListStage.push_back(&TileListthree);
			TileListStage.push_back(&TileListfour);
			TileListStage.push_back(&TileListfive);
		}
		break;
	}

	return S_OK;
}

void BreakTileClass::release(void)
{
}

void BreakTileClass::update(void)
{

	switch (StageNumber)
	{
	case BreakTileClass::BreakTile::Stage1:
		//스테이지 1번 업데이트
		for (int i = 0; i < TileListone.size(); i++)
		{
			TileListone[i]->FrameCount++;
			if (TileListone[i]->FrameCount % 10 == 0)
			{
				TileListone[i]->FrameX++;
			}

		}
		for (int i = 0; i < TileListtwo.size(); i++)
		{
			TileListtwo[i]->FrameCount++;
			if (TileListtwo[i]->FrameCount % 10 == 0)
			{
				TileListtwo[i]->FrameX++;
			}
		}
		for (int i = 0; i < TileListthree.size(); i++)
		{
			TileListthree[i]->FrameCount++;
			if (TileListthree[i]->FrameCount % 10 == 0)
			{
				TileListthree[i]->FrameX++;
			}
		}
		for (int i = 0; i < TileListfour.size(); i++)
		{
			TileListfour[i]->FrameCount++;
			if (TileListfour[i]->FrameCount % 10 == 0)
			{
				TileListfour[i]->FrameX++;
			}
		}
		for (int i = 0; i < TileListfive.size(); i++)
		{
			TileListfive[i]->FrameCount++;
			if (TileListfive[i]->FrameCount % 10 == 0)
			{
				TileListfive[i]->FrameX++;
			}
		}
		break;
	case BreakTileClass::BreakTile::BossStage:
		for (int i = 0; i < TileListBossone.size(); i++)
		{
			TileListBossone[i]->FrameCount++;
			if (TileListBossone[i]->FrameCount % 10 == 0)
			{
				TileListBossone[i]->FrameX++;
			}
		}
		for (int i = 0; i < TileListBosstwo.size(); i++)
		{
			TileListBosstwo[i]->FrameCount++;
			if (TileListBosstwo[i]->FrameCount % 10 == 0)
			{
				TileListBosstwo[i]->FrameX++;
			}
		}
		for (int i = 0; i < TileListBossthree.size(); i++)
		{
			TileListBossthree[i]->FrameCount++;
			if (TileListBossthree[i]->FrameCount % 10 == 0)
			{
				TileListBossthree[i]->FrameX++;
			}
		}
		for (int i = 0; i < TileListBossfour.size(); i++)
		{
			TileListBossfour[i]->FrameCount++;
			if (TileListBossfour[i]->FrameCount % 10 == 0)
			{
				TileListBossfour[i]->FrameX++;
			}
		}
		break;
	}



	//콜리전 클래스로 이동시켜야 합니다. 플레이어 충돌시 전 코드가 작동되기 때문에 여기있으면 의미없음

	//for (int i = 0; i < TileList.size(); i++)
	//{
	//	RECT temp;
	//	if (IntersectRect(&temp, &TileList[i].rc, &player->getRect()))
	//	{
	//		TileList[i].isTouch = true;
	//	}
	//	if (TileList[i].isTouch == true)
	//	{
	//		TileList[i].Count++;
	//	}
	//}
	//
	//
	//for (int i = 0; i < TileList.size(); i++)
	//{
	//
	//	if (TileList[i].Count > 50)
	//	{
	//
	//		if (TileList[i].isTouch == true)
	//		{
	//			TileList[i].rc.top += 5;
	//			TileList[i].rc.bottom += 5;
	//		}
	//	}
	//
	//
	//}
	//
	//for (int i = 0; i < TileList.size(); i++)
	//{
	//	for (int j = 0; j < TileList.size(); j++)
	//	{
	//		if (TileList[i].rc.top > TileList[j].rc.bottom)
	//		{
	//			TileList[j].isTouch = true;
	//		}
	//
	//	}
	//
	//}

}

void BreakTileClass::render()
{
	switch (StageNumber)
	{
	case BreakTileClass::BreakTile::Stage1:
		for (int i = 0; i < TileListone.size(); i++)
		{
			TileListone[i]->block->frameRender(getMemDC(), TileListone[i]->rc.left - CAMERA.getCRc().left,
				TileListone[i]->rc.top - CAMERA.getCRc().top, TileListone[i]->FrameX, TileListone[i]->FrameY);
		}
		for (int i = 0; i < TileListtwo.size(); i++)
		{
			TileListtwo[i]->block->frameRender(getMemDC(), TileListtwo[i]->rc.left - CAMERA.getCRc().left,
				TileListtwo[i]->rc.top - CAMERA.getCRc().top, TileListtwo[i]->FrameX, TileListtwo[i]->FrameY);
		}
		for (int i = 0; i < TileListthree.size(); i++)
		{
			TileListthree[i]->block->frameRender(getMemDC(), TileListthree[i]->rc.left - CAMERA.getCRc().left,
				TileListthree[i]->rc.top - CAMERA.getCRc().top, TileListthree[i]->FrameX, TileListthree[i]->FrameY);
		}
		for (int i = 0; i < TileListfour.size(); i++)
		{
			TileListfour[i]->block->frameRender(getMemDC(), TileListfour[i]->rc.left - CAMERA.getCRc().left,
				TileListfour[i]->rc.top - CAMERA.getCRc().top, TileListfour[i]->FrameX, TileListfour[i]->FrameY);
		}
		for (int i = 0; i < TileListfive.size(); i++)
		{
			TileListfive[i]->block->frameRender(getMemDC(), TileListfive[i]->rc.left - CAMERA.getCRc().left,
				TileListfive[i]->rc.top - CAMERA.getCRc().top, TileListfive[i]->FrameX, TileListfive[i]->FrameY);
		}
		break;
	case BreakTileClass::BreakTile::BossStage:
		for (int i = 0; i < TileListBossone.size(); i++)
		{
			TileListBossone[i]->block->frameRender(getMemDC(), TileListBossone[i]->rc.left - CAMERA.getCRc().left,
				TileListBossone[i]->rc.top - CAMERA.getCRc().top, TileListBossone[i]->FrameX, TileListBossone[i]->FrameY);
		}
		for (int i = 0; i < TileListBosstwo.size(); i++)
		{
			TileListBosstwo[i]->block->frameRender(getMemDC(), TileListBosstwo[i]->rc.left - CAMERA.getCRc().left,
				TileListBosstwo[i]->rc.top - CAMERA.getCRc().top, TileListBosstwo[i]->FrameX, TileListBosstwo[i]->FrameY);
		}
		for (int i = 0; i < TileListBossthree.size(); i++)
		{
			TileListBossthree[i]->block->frameRender(getMemDC(), TileListBossthree[i]->rc.left - CAMERA.getCRc().left,
				TileListBossthree[i]->rc.top - CAMERA.getCRc().top, TileListBossthree[i]->FrameX, TileListBossthree[i]->FrameY);
		}
		for (int i = 0; i < TileListBossfour.size(); i++)
		{
			TileListBossfour[i]->block->frameRender(getMemDC(), TileListBossfour[i]->rc.left - CAMERA.getCRc().left,
				TileListBossfour[i]->rc.top - CAMERA.getCRc().top, TileListBossfour[i]->FrameX, TileListBossfour[i]->FrameY);
		}
		break;
	}

}
/************************************************************************************************************
## hideTile Class
*************************************************************************************************************/

HRESULT HideTileClass::init(HideTile Stage)
{

	StageNumber = Stage;
	light = IMAGEMANAGER->findImage("변신타일");
	Boom = IMAGEMANAGER->findImage("폭발");
	switch (StageNumber)
	{
	case HideTileClass::HideTile::Stage1:
		Grass = IMAGEMANAGER->addImage("풀밭", "상어풀밭.bmp", 170, 116, true, RGB(255, 0, 255));
		HideBlock = IMAGEMANAGER->addImage("투명벽", "숨은 벽.bmp", 189, 350, true, RGB(255, 0, 255));
		HideBlockTwo = IMAGEMANAGER->addImage("위쪽투명벽", "스테이지 1번 위쪽 숨은벽.bmp", 776, 635, true, RGB(255, 0, 255));
		HideRc = RectMake(6833, 1072, 127, 209);
		HideRcTwo = RectMake(6933, 248, 770, 630);
		GrassRC = RectMake(13640, 183, 178, 116);
		break;
	case HideTileClass::HideTile::BossStage:
		BossTile1 = IMAGEMANAGER->addImage("BossTile_1", "보스 스테이지 숨은타일 1번.bmp", 312, 250, true, RGB(255, 0, 255));
		BossTile2 = IMAGEMANAGER->addImage("BommTile_2", "보스 스테이지 숨은타일 2번.bmp", 487, 357, true, RGB(255, 0, 255));
		BossTileRCone = RectMake(3426, 401, 312, 250);
		BossTileRCtwo = RectMake(5048, 360, 487, 357);
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
	ishide = false;
	return S_OK;
}

void HideTileClass::release(void)
{
}

void HideTileClass::update(void)
{
	//콜리젼으로 이동시켜야 하는 코드

	//switch (Stage)
	//{
	//case HideTileClass::HideTile::Stage1:
	//	break;
	//case HideTileClass::HideTile::BossStage:
	//	Count++;
	//	if (Count % 5 == 0)
	//	{
	//		frameImgX++;
	//		if (frameImgX > 27)
	//		{
	//			frameImgX = 0;
	//		}
	//		Count = 0;
	//	}
	//
	//
	//	if (Count % 5 == 0)
	//	{
	//		BoomFrameX++;
	//		if (BoomFrameX > 12)
	//		{
	//			BoomFrameX = 0;
	//			isBoom = true;
	//		}
	//		Count = 0;
	//	}
	//
	//
	//
	//	for (int i = 0; i < HideList.size(); i++)
	//	{
	//		if (player->getX() < 8171)
	//		{
	//			HideList[i].isTouch = true;
	//			isBoom = true;
	//			frameImgX = 0;
	//			BoomFrameX = 0;
	//		}
	//	}
	//	if (KEYMANAGER->isOnceKeyDown('Y'))
	//	{
	//		for (int i = 0; i < HideList.size(); i++)
	//		{
	//			HideList[i].isTouch = false;
	//			isBoom = false;
	//		}
	//	}
	//
	//	break;
	//
	//}

}

void HideTileClass::render(void)
{
	switch (StageNumber)
	{
	case HideTileClass::HideTile::Stage1:

		HideBlock->alphaRender(getMemDC(), HideRc.left - (58) - CAMERA.getCRc().left, HideRc.top - (50) - CAMERA.getCRc().top, 255);
		Grass->alphaRender(getMemDC(), GrassRC.left - CAMERA.getCRc().left, GrassRC.top - CAMERA.getCRc().top, 255);
		HideBlockTwo->alphaRender(getMemDC(), HideRcTwo.left - CAMERA.getCRc().left, HideRcTwo.top - CAMERA.getCRc().top, 255);

		break;
	case HideTileClass::HideTile::BossStage:
		for (int i = 0; i < HideList.size(); i++)
		{
			//Rectangle(getMemDC(), RelativeCameraRect(BossTileRCone));
			BossTile1->alphaRender(getMemDC(), BossTileRCone.left - CAMERA.getCRc().left, BossTileRCone.top - CAMERA.getCRc().top, 255);
			BossTile2->alphaRender(getMemDC(), BossTileRCtwo.left - CAMERA.getCRc().left, BossTileRCtwo.top - CAMERA.getCRc().top, 255);
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
		break;
	}


}
/****************************************************************************************************************
## ThorntrapClass
*****************************************************************************************************************/
HRESULT ThorntrapClass::init(stageNumber Stage)
{
	StageNumber = Stage;
	switch (StageNumber)
	{
	case stageNumber::Stage1:
		//스테이지 1번 렉트
		ThornOne = RectMake(2987, 754, 141, 22);
		ThornTwo = RectMake(3502, 754, 139, 23);
		ThornThree = RectMake(5979, 624, 267, 21);
		ThornFour = RectMake(11146, 669, 137, 17);
		ThornFive = RectMake(11580, 668, 173, 22);
		ThornSix = RectMake(14182, 712, 220, 20);
		ThornSeven = RectMake(15379, 709, 221, 21);
		//스테이지 1번 벡터
		ThornList.push_back(ThornOne);
		ThornList.push_back(ThornTwo);
		ThornList.push_back(ThornThree);
		ThornList.push_back(ThornFour);
		ThornList.push_back(ThornFive);
		ThornList.push_back(ThornSix);
		ThornList.push_back(ThornSeven);
		break;

	case stageNumber::BossStage:
		ThornBossone = RectMake(4487, 456, 85, 22);
		ThornBosstwo = RectMake(4747, 456, 80, 22);
		ThornBossthree = RectMake(4727, 515, 27, 167);
		ThornBossfour = RectMake(4942, 0, 24, 468);
		ThornBossfive = RectMake(8452, 2385, 395, 10);
		ThornBosssix = RectMake(8965, 2385, 395, 10);
		ThornBossList.push_back(ThornBossone);
		ThornBossList.push_back(ThornBosstwo);
		ThornBossList.push_back(ThornBossthree);
		ThornBossList.push_back(ThornBossfour);
		ThornBossList.push_back(ThornBossfive);
		ThornBossList.push_back(ThornBosssix);
		break;
	}


	//보스스테이지 렉트


	return S_OK;
}

void ThorntrapClass::release(void)
{
}

void ThorntrapClass::update(void)
{
}

void ThorntrapClass::render(void)
{
	switch (StageNumber)
	{
	case ThorntrapClass::stageNumber::Stage1:
		//스테이지 1번 랜더
		//for (int i = 0; i < ThornList.size(); i++)
		//{
		//	Rectangle(getMemDC(), RelativeCameraRect(ThornList[i]));
		//}
		break;
	case ThorntrapClass::stageNumber::BossStage:
		//보스스테이지 렌더
		for (int i = 0; i < ThornBossList.size(); i++)
		{
			Rectangle(getMemDC(), RelativeCameraRect(ThornBossList[i]));
		}
		break;
	}

}

/*****************************************************************************************************************
## 점프대 및 잡다한 타일들 모두 만드는곳 ##
******************************************************************************************************************/
HRESULT UniClass::init(Jumpstate Stage)
{
	StageNumber = Stage;
	switch (StageNumber)
	{
	case UniClass::Jumpstate::Stage1:
		break;
	case UniClass::Jumpstate::BossStage:
		JumpOne = IMAGEMANAGER->addFrameImage("점프", "점프대.bmp", 38, 98, 1, 2, true, RGB(255, 0, 255));
		JumpTwo = IMAGEMANAGER->addFrameImage("점프2", "점프대.bmp", 38, 98, 1, 2, true, RGB(255, 0, 255));
		JumpRCone = RectMake(8331, 2260, 38, 24);
		JumpRCtwo = RectMake(9443, 2260, 38, 24);
		JumpOneX = JumpOneY = 0;
		JumpTwoX = JumpTwoY = 0;
		break;
	}
	return S_OK;
}

void UniClass::release(void)
{
}

void UniClass::update(void)
{
}

void UniClass::render(void)
{
	switch (StageNumber)
	{
	case UniClass::Jumpstate::Stage1:
		break;
	case UniClass::Jumpstate::BossStage:
		JumpOne->frameRender(getMemDC(), JumpRCone.left - CAMERA.getCRc().left, JumpRCone.top - CAMERA.getCRc().top, JumpOneX, JumpOneY);
		JumpTwo->frameRender(getMemDC(), JumpRCtwo.left - CAMERA.getCRc().left, JumpRCtwo.top - CAMERA.getCRc().top, JumpTwoX, JumpTwoY);
		break;
	}
}
