#include "stdafx.h"
#include "FlowerClass.h"
#include "bullet.h"
#include "PlayerClass.h"
HRESULT FlowerClass::init(FlowerTile Stage)
{
	StageNumber = Stage;
	switch (StageNumber)
	{
	case FlowerClass::FlowerTile::Stage1:
		break;
	case FlowerClass::FlowerTile::BossStage:
		Count = 0;
		isHit = false;
		fireBollPtr = new bullet;
		fireBollPtr->init("ÃÑ¾Ë", 100, 640);
		fireBollLeftPtr = new bullet;
		fireBollLeftPtr->init("ÃÑ¾Ë", 100, 124);
		fireBollRightPtr = new bullet;
		fireBollRightPtr->init("ÃÑ¾Ë", 100, 124);
		fireBollLefttwoPtr = new bullet;
		fireBollLefttwoPtr->init("ÃÑ¾Ë", 100, 816);
		fireBollRighttwoPtr = new bullet;
		fireBollRighttwoPtr->init("ÃÑ¾Ë", 100, 944);
		fireBollDownOnePtr = new bullet;
		fireBollDownOnePtr->init("ÃÑ¾Ë", 100, 169);
		fireBollDownTwoPtr = new bullet;
		fireBollDownTwoPtr->init("ÃÑ¾Ë", 100, 160);
		fireBollUpOnePtr = new bullet;
		fireBollUpOnePtr->init("ÃÑ¾Ë", 100, 169);
		fireBollUpTwoPtr = new bullet;
		fireBollUpTwoPtr->init("ÃÑ¾Ë", 100, 169);
		fireBollUpthreePtr = new bullet;
		fireBollUpthreePtr->init("ÃÑ¾Ë", 100, 84);
		////////////////////////////////////////////////////////////////////////////
		// ## ¹Ù´Ú ²É ÇÔÁ¤##
		////////////////////////////////////////////////////////////////////////////
				//²É 1¹ø
		for (int i = 0; i < 3; i++)
		{
			flowerone = new Flower;
			flowerone->rc = RectMake(2045 + (i * 44), 640, 44, 41);
			FlowerList.push_back(flowerone);
		}
		//²É 2¹ø
		for (int i = 0; i < 3; i++)
		{
			flowertwo = new Flower;
			flowertwo->rc = RectMake(2345 + (i * 44), 640, 44, 44);
			FlowerList.push_back(flowertwo);
		}
		//²É 3¹ø
		for (int i = 0; i < 4; i++)
		{
			flowerthree = new Flower;
			flowerthree->rc = RectMake(2646 + (i * 44), 641, 44, 43);
			FlowerList.push_back(flowerthree);
		}
		//²É 4¹ø
		for (int i = 0; i < 3; i++)
		{
			flowerfour = new Flower;
			flowerfour->rc = RectMake(2945 + (i * 44), 642, 44, 42);
			FlowerList.push_back(flowerfour);
		}
		//²É 5¹ø
		for (int i = 0; i < 4; i++)
		{
			flowerfive = new Flower;
			flowerfive->rc = RectMake(3291 + (i * 44), 640, 44, 41);
			FlowerList.push_back(flowerfive);
		}
		///////////////////////////////////////////////////////////////////////////
		// ## ¿ÞÂÊ º® ²É ÇÔÁ¤ ##
		///////////////////////////////////////////////////////////////////////////
		LeftCountone = 0;
		LeftCounttwo = 0;
		LeftCountthree = 0;
		LeftCountfour = 0;
		for (int i = 0; i < 4; i++)
		{
			flwoerLeftone = new Flower;
			flwoerLeftone->rc = RectMake(6324, 1068 + (i * 128), 43, 44);
			FlowerListLeft.push_back(flwoerLeftone);
		}

		LeftTwoCountone = 0;
		LeftTwoCounttwo = 0;
		for (int i = 0; i < 2; i++)
		{
			flowerLefttwo = new Flower;
			flowerLefttwo->rc = RectMake(5639, 1628 + (i * 84), 43, 44);
			FlowerListLefttwo.push_back(flowerLefttwo);
		}
		///////////////////////////////////////////////////////////////////////////
		// ## ¿À¸¥ÂÊ º® ²É ÇÔÁ¤ ##
		///////////////////////////////////////////////////////////////////////////
		RightCountone = 0;
		RightCounttwo = 0;
		RightCountthree = 0;
		RightCountfour = 0;
		for (int i = 0; i < 4; i++)
		{
			flowerRightone = new Flower;
			flowerRightone->rc = RectMake(6492, 1066 + (i * 128), 43, 44);
			FlowerListRight.push_back(flowerRightone);
		}

		RightTwoCountone = 0;
		RightTwoCounttwo = 0;
		for (int i = 0; i < 2; i++)
		{
			flowerRighttwo = new Flower;
			flowerRighttwo->rc = RectMake(6620, 2053 + (i * 84), 43, 44);
			FlowerListRighttwo.push_back(flowerRighttwo);
		}
		///////////////////////////////////////////////////////////////////////////
		// ## ¾Æ·¡ º® ²É ÇÔÁ¤ ##
		///////////////////////////////////////////////////////////////////////////
		DownoneCount = 0;
		DowntwoCount = 0;
		for (int i = 0; i < 8; i++)
		{
			flowerDownone = new Flower;
			flowerDownone->rc = RectMake(7386 + (i * 43), 1709, 43, 44);
			FlowerListDownoen.push_back(flowerDownone);
			flowerDowntwo = new Flower;
			flowerDowntwo->rc = RectMake(7386 + (i * 43), 1401, 43, 44);
			FlowerListDowntwo.push_back(flowerDowntwo);
		}
		///////////////////////////////////////////////////////////////////////////
		// ## À§º® ²É ÇÔÁ¤ ##
		///////////////////////////////////////////////////////////////////////////
		UponeCount = 0;
		UptwoCount = 0;
		for (int i = 0; i < 2; i++)
		{
			flowerUpone = new Flower;
			flowerUptwo = new Flower;
			flowerUpone->rc = RectMake(7390 + (i * 43), 938, 43, 44);
			flowerUptwo->rc = RectMake(7647 + (i * 43), 938, 43, 44);
			FlowerListUpone.push_back(flowerUpone);
			FlowerListUptwo.push_back(flowerUptwo);
		}
		///////////////////////////////////////////////////////////////////////////
		// ## À§º® ²É ÇÔÁ¤ ##
		///////////////////////////////////////////////////////////////////////////
		UpthreeCount = 0;
		for (int i = 0; i < 4; i++)
		{
			flowerUpthree = new Flower;
			flowerUpthree->rc = RectMake(7476 + (i * 43), 938, 43, 44);
			FlowerListUpthree.push_back(flowerUpthree);
		}
		break;
	}
	return S_OK;
}

void FlowerClass::release(void)
{
	//¹Ù´Ú ²É ÇØÁ¦
	fireBollPtr->release();
	SAFE_DELETE(fireBollPtr);
	//¿ÞÂÊ ²É ÇØÁ¦
	fireBollLeftPtr->release();
	SAFE_DELETE(fireBollLeftPtr);
	//¿À¸¥ÂÊ ²É ÇØÁ¦
	fireBollRightPtr->release();
	SAFE_DELETE(fireBollRightPtr);
	//¿ÞÂÊ µÎ¹øÂ° ²É ÇØÁ¦
	fireBollLefttwoPtr->release();
	SAFE_DELETE(fireBollLefttwoPtr);
	//¿À¸¥ÂÊ µÎ¹øÂ° ²É ÇØÁ¦
	fireBollRighttwoPtr->release();
	SAFE_DELETE(fireBollRighttwoPtr);
	//¹Ù´Ú ²É 2¹øÂ° ÇØÁ¦
	fireBollDownOnePtr->release();
	SAFE_DELETE(fireBollDownOnePtr);
	fireBollDownTwoPtr->release();
	SAFE_DELETE(fireBollDownTwoPtr);
	//À§¿¡²É ¿Ü°¢ ÇØÁ¦
	fireBollUpOnePtr->release();
	SAFE_DELETE(fireBollUpOnePtr);
	fireBollUpTwoPtr->release();
	SAFE_DELETE(fireBollUpTwoPtr);
	//À§¿¡²É Áß½É ÇØÁ¦
}

void FlowerClass::update()
{
	switch (StageNumber)
	{
	case FlowerClass::FlowerTile::Stage1:
		break;
	case FlowerClass::FlowerTile::BossStage:
		//¹Ù´Ú²É Ä«¿îÆ®
		Count++;
		//¿ÞÂÊ ²É °¢°¢ÀÇ Ä«¿îÆ®
		LeftCountone++;
		LeftCounttwo++;
		LeftCountthree++;
		LeftCountfour++;
		//¿À¸¥ÂÊ ²É °¢°¢ÀÇ Ä«¿îÆ®
		RightCountone++;
		RightCounttwo++;
		RightCountthree++;
		RightCountfour++;
		//¿ÞÂÊ ²É µÎ¹øÂ° Ä«¿îÆ®
		LeftTwoCountone++;
		LeftTwoCounttwo++;
		//¿À¸¥ÂÊ ²É µÎ¹øÂ° Ä«¿îÆ®
		RightTwoCountone++;
		RightTwoCounttwo++;
		//¹Ù´Ú 2¹øÂ° ²É Ä«¿îÆ®
		DownoneCount++;
		DowntwoCount++;
		//À§¿¡²É ¿Ü°¢ Ä«¿îÆ®
		UponeCount++;
		UptwoCount++;
		//À§¿¡²É Áß½É Ä«¿îÆ®
		UpthreeCount++;
		//ÃÑ¾Ë ¾÷µ¥ÀÌÆ®
		fireBollPtr->update();
		fireBollLeftPtr->update();
		fireBollRightPtr->update();
		fireBollLefttwoPtr->update();
		fireBollRighttwoPtr->update();
		fireBollDownOnePtr->update();
		fireBollDownTwoPtr->update();
		fireBollUpOnePtr->update();
		fireBollUpTwoPtr->update();
		fireBollUpthreePtr->update();
		//¹ß»çÇÔ¼ö
		flowerOne();
		break;
	}


}

void FlowerClass::render()
{
	switch (StageNumber)
	{
	case FlowerClass::FlowerTile::Stage1:
		break;
	case FlowerClass::FlowerTile::BossStage:
		for (int i = 0; i < FlowerList.size(); i++)
		{
			Rectangle(getMemDC(), RelativeCameraRect(FlowerList[i]->rc));
		}
		for (int i = 0; i < FlowerListLeft.size(); i++)
		{
			Rectangle(getMemDC(), RelativeCameraRect(FlowerListLeft[i]->rc));
		}
		for (int i = 0; i < FlowerListRight.size(); i++)
		{
			Rectangle(getMemDC(), RelativeCameraRect(FlowerListRight[i]->rc));
		}
		for (int i = 0; i < FlowerListLefttwo.size(); i++)
		{
			Rectangle(getMemDC(), RelativeCameraRect(FlowerListLefttwo[i]->rc));
		}
		for (int i = 0; i < FlowerListRighttwo.size(); i++)
		{
			Rectangle(getMemDC(), RelativeCameraRect(FlowerListRighttwo[i]->rc));
		}
		for (int i = 0; i < FlowerListDownoen.size(); i++)
		{
			Rectangle(getMemDC(), RelativeCameraRect(FlowerListDownoen[i]->rc));
		}
		for (int i = 0; i < FlowerListDowntwo.size(); i++)
		{
			Rectangle(getMemDC(), RelativeCameraRect(FlowerListDowntwo[i]->rc));
		}
		for (int i = 0; i < FlowerListUpone.size(); i++)
		{
			Rectangle(getMemDC(), RelativeCameraRect(FlowerListUpone[i]->rc));
		}
		for (int i = 0; i < FlowerListUptwo.size(); i++)
		{
			Rectangle(getMemDC(), RelativeCameraRect(FlowerListUptwo[i]->rc));
		}
		for (int i = 0; i < FlowerListUpthree.size(); i++)
		{
			Rectangle(getMemDC(), RelativeCameraRect(FlowerListUpthree[i]->rc));
		}

		fireBollPtr->render();
		fireBollLeftPtr->render();
		fireBollRightPtr->render();
		fireBollLefttwoPtr->render();
		fireBollRighttwoPtr->render();
		fireBollDownOnePtr->render();
		fireBollDownTwoPtr->render();
		fireBollUpOnePtr->render();
		fireBollUpTwoPtr->render();
		fireBollUpthreePtr->render();
		break;
	}

}

void FlowerClass::flowerOne()
{
	//¹Ù´Ú ²É Ä«¿îÆ® (100ÃÊ´ç ÀüºÎ 1¹ø¾¿ ½î±â)
	if (Count % 100 == 0)
	{
		for (int i = 0; i < FlowerList.size(); i++)
		{
			fireBollPtr->fire(FlowerList[i]->rc.left + 22, FlowerList[i]->rc.top, PI / 2, 5.0f);
		}
	}
	//¿ÞÂÊ ²É Ä«¿îÆ® (°¢°¢ ½Ã°£Â÷·Î ½î°Ô ¸¸µé±â)
	if (LeftCountone % 100 == 0)
	{
		fireBollLeftPtr->fire(FlowerListLeft[0]->rc.right, FlowerListLeft[0]->rc.top + 22, 0, 5.0f);
	}
	if (LeftCounttwo % 110 == 0)
	{
		fireBollLeftPtr->fire(FlowerListLeft[1]->rc.right, FlowerListLeft[1]->rc.top + 22, 0, 5.0f);
		LeftCounttwo = 10;
	}
	if (LeftCountthree % 120 == 0)
	{
		fireBollLeftPtr->fire(FlowerListLeft[2]->rc.right, FlowerListLeft[2]->rc.top + 22, 0, 5.0f);
		LeftCountthree = 20;
	}
	if (LeftCountfour % 130 == 0)
	{
		fireBollLeftPtr->fire(FlowerListLeft[3]->rc.right, FlowerListLeft[3]->rc.top + 22, 0, 5.0f);
		LeftCountfour = 30;
	}

	//¿À¸¥ÂÊ ²É Ä«¿îÆ® (°¢°¢ ½Ã°£Â÷·Î ½î°Ô ¸¸µé±â)
	if (RightCountone % 100 == 0)
	{
		fireBollRightPtr->fire(FlowerListRight[0]->rc.left, FlowerListRight[0]->rc.top + 22, PI, 5.0f);

	}
	if (RightCounttwo % 110 == 0)
	{
		fireBollRightPtr->fire(FlowerListRight[1]->rc.left, FlowerListRight[1]->rc.top + 22, PI, 5.0f);
		RightCounttwo = 10;
	}
	if (RightCountthree % 120 == 0)
	{
		fireBollRightPtr->fire(FlowerListRight[2]->rc.left, FlowerListRight[2]->rc.top + 22, PI, 5.0f);
		RightCountthree = 20;
	}
	if (RightCountfour % 130 == 0)
	{
		fireBollRightPtr->fire(FlowerListRight[3]->rc.left, FlowerListRight[3]->rc.top + 22, PI, 5.0f);
		RightCountfour = 30;
	}
	//¿ÞÂÊ µÎ¹øÂ° ²É Ä«¿îÆ®
	if (LeftTwoCountone % 170 == 0)
	{
		fireBollLefttwoPtr->fire(FlowerListLefttwo[0]->rc.right, FlowerListLefttwo[0]->rc.top + 22, 0, 5.0f);
	}
	if (LeftTwoCounttwo % 210 == 0)
	{
		fireBollLefttwoPtr->fire(FlowerListLefttwo[1]->rc.right, FlowerListLefttwo[1]->rc.top + 22, 0, 5.0f);
		LeftTwoCounttwo = 40;
	}
	//¿À¸¥ÂÊ µÎ¹øÂ° ²É Ä«¿îÆ®
	if (RightTwoCountone % 170 == 0)
	{
		fireBollRighttwoPtr->fire(FlowerListRighttwo[0]->rc.left, FlowerListRighttwo[0]->rc.top + 22, PI, 5.0f);
	}
	if (RightTwoCounttwo % 210 == 0)
	{
		fireBollRighttwoPtr->fire(FlowerListRighttwo[1]->rc.left, FlowerListRighttwo[1]->rc.top + 22, PI, 5.0f);
		RightTwoCounttwo = 40;
	}

	if (DownoneCount % 150 == 0)
	{
		for (int i = 0; i < FlowerListDownoen.size(); i++)
		{
			fireBollDownOnePtr->fire(FlowerListDownoen[i]->rc.left + 22, FlowerListDownoen[i]->rc.top, PI / 2, 5.0f);
		}

	}

	if (DowntwoCount % 150 == 0)
	{
		for (int i = 0; i < FlowerListDowntwo.size(); i++)
		{
			fireBollDownTwoPtr->fire(FlowerListDowntwo[i]->rc.left + 22, FlowerListDowntwo[i]->rc.top, PI / 2, 5.0f);
		}
	}

	if (UponeCount % 150 == 0)
	{
		for (int i = 0; i < FlowerListUpone.size(); i++)
		{
			fireBollUpOnePtr->fire(FlowerListUpone[i]->rc.left + 22, FlowerListUpone[i]->rc.bottom, PI + PI / 2, 5.0f);
		}
		for (int i = 0; i < FlowerListUptwo.size(); i++)
		{
			fireBollUpTwoPtr->fire(FlowerListUptwo[i]->rc.left + 22, FlowerListUptwo[i]->rc.bottom, PI + PI / 2, 5.0f);
		}

	}

	if (UpthreeCount % 150 == 0)
	{
		for (int i = 0; i < FlowerListUpthree.size(); i++)
		{
			fireBollUpthreePtr->fire(FlowerListUpthree[i]->rc.left + 22, FlowerListUpthree[i]->rc.bottom, PI + PI / 2, 5.0f);
		}

	}
}
