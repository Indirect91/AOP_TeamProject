#include "stdafx.h"
#include "BreakTileClass.h"
#include "PlayerClass.h"
HRESULT BreakTileClass::init(BreakTile stage)
{

	switch (stage)
	{
	case BreakTileClass::BreakTile::Stage1:
		for (int i = 0; i < 8; i++)
		{
			tile.point.x = 8716;
			tile.point.y = 469;
			tile.rc = RectMake(tile.point.x + (i * 41), tile.point.y, 41, 37);
			tile.isTouch = false;
			tile.isMode = true;
			tile.TouchCount = 4;
			tile.Count = 1;
			TileList.push_back(tile);
		}
		break;
	case BreakTileClass::BreakTile::BossStage:
		break;
	}	

	return S_OK;
}

void BreakTileClass::release(void)
{
}

void BreakTileClass::update(PlayerClass * player)
{

	//for (int i = 0; i < TileList.size(); i++)
	//{
	//	RECT temp;
	//	if (IntersectRect(&temp,&TileList[i].rc,&player->getRect()))
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

void BreakTileClass::render(void)
{
	//for (int i = 0; i < TileList.size(); i++)
	//{
	//	Rectangle(getMemDC(), RelativeCameraRect(TileList[i].rc));
	//
	//}
}
