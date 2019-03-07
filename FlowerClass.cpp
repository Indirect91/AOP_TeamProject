#include "stdafx.h"
#include "FlowerClass.h"
#include "bullet.h"
#include "PlayerClass.h"
HRESULT FlowerClass::init(FlowerTile Stage)
{
	switch (Stage)
	{
	case FlowerClass::FlowerTile::Stage1:
		fireBollPtr = new bullet;
		fireBollPtr->init("�Ѿ�", 100, 640);
		fireBollRightPtr = new bullet;
		fireBollRightPtr->init("�Ѿ�", 100, 124);
		break;
	case FlowerClass::FlowerTile::BossStage:
		Count = 0;
		isHit = false;
		fireBollPtr = new bullet;
		fireBollPtr->init("�Ѿ�",100,640);
////////////////////////////////////////////////////////////////////////////
// ## �ٴ� �� ����##
////////////////////////////////////////////////////////////////////////////
		//�� 1��
		for (int i = 0; i < 3; i++)
		{
			flowerone = new Flower;
			flowerone->rc = RectMake(2045+(i * 44), 640, 44, 41);
			FlowerList.push_back(flowerone);
		}
		//�� 2��
		for (int i = 0; i < 3; i++)
		{
			flowertwo = new Flower;
			flowertwo->rc = RectMake(2345 + (i * 44), 640, 44, 44);
			FlowerList.push_back(flowertwo);
		}
		//�� 3��
		for (int i = 0; i < 4; i++)
		{
			flowerthree = new Flower;
			flowerthree->rc = RectMake(2646 + (i * 44), 641, 44, 43);
			FlowerList.push_back(flowerthree);
		}
		//�� 4��
		for (int i = 0; i < 3; i++)
		{
			flowerfour = new Flower;
			flowerfour->rc = RectMake(2945+(i * 44), 642, 44, 42);
			FlowerList.push_back(flowerfour);
		}
		//�� 5��
		for (int i = 0; i < 4; i++)
		{
			flowerfive = new Flower;
			flowerfive->rc = RectMake(3291 + (i * 44), 640, 44, 41);
			FlowerList.push_back(flowerfive);
		}
///////////////////////////////////////////////////////////////////////////
// ## ���� �� �� ���� ##
///////////////////////////////////////////////////////////////////////////
		fireBollRightPtr = new bullet;
		fireBollRightPtr->init("�Ѿ�",100,124);
		RightCountone = 0;
		RightCounttwo = 0;
		RightCountthree = 0;
		RightCountfour = 0;
		for (int i = 0; i < 4; i++)
		{
			flowerRightone = new Flower;
			flowerRightone->rc = RectMake(6324, 1068 + (i * 128), 43, 44);
			FlowerListRight.push_back(flowerRightone);
		}
		break;
	}
	return S_OK;
}

void FlowerClass::release(void)
{
	
	fireBollPtr->release();
	SAFE_DELETE(fireBollPtr);
	fireBollRightPtr->release();
	SAFE_DELETE(fireBollRightPtr);
	
}

void FlowerClass::update(PlayerClass * player)
{
	//�ٴڲ� ī��Ʈ
	Count++;
	//������ �� ������ ī��Ʈ
	RightCountone++;
	RightCounttwo++;
	RightCountthree++;
	RightCountfour++;
	//�Ѿ� ������Ʈ
	fireBollPtr->update();
	fireBollRightPtr->update();
	//�߻��Լ�
	flowerOne();
}

void FlowerClass::render(void)
{
	for (int i = 0; i < FlowerList.size(); i++)
	{
		Rectangle(getMemDC(), RelativeCameraRect(FlowerList[i]->rc));
	}
	for (int i = 0; i < FlowerListRight.size(); i++)
	{
		Rectangle(getMemDC(), RelativeCameraRect(FlowerListRight[i]->rc));
	}

	fireBollPtr->render();
	fireBollRightPtr->render();
}

void FlowerClass::flowerOne()
{
	if (Count % 100 ==0)
	{
		for (int i = 0; i < FlowerList.size(); i++)
		{
			fireBollPtr->fire(FlowerList[i]->rc.left + 22, FlowerList[i]->rc.top, PI / 2, 5.0f);
		}
	}

	if (RightCountone % 100 == 0)
	{
		fireBollRightPtr->fire(FlowerListRight[0]->rc.right, FlowerListRight[0]->rc.top + 22, 0, 5.0f);
	}
	if (RightCounttwo % 110 == 0)
	{
		fireBollRightPtr->fire(FlowerListRight[1]->rc.right, FlowerListRight[1]->rc.top + 22, 0, 5.0f);
		RightCounttwo = 10;
	}
	if (RightCountthree % 120 == 0)
	{
		fireBollRightPtr->fire(FlowerListRight[2]->rc.right, FlowerListRight[2]->rc.top + 22, 0, 5.0f);
		RightCountthree = 20;
	}
	if (RightCountfour % 130 == 0)
	{
		fireBollRightPtr->fire(FlowerListRight[3]->rc.right, FlowerListRight[3]->rc.top + 22, 0, 5.0f);
		RightCountfour = 30;
	}
	
}
