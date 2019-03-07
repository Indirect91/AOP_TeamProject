#include "stdafx.h"
#include "CollisionClass.h"
#include "PlayerClass.h"
#include "EnemyClass.h"
#include "EnemyManagerClass.h"
#include "PetsClass.h"
#include "FieldManagerClass.h"
#include "LandmarkClass.h"

//플레이어가 에너미를 밟음
void CollisionClass::playerStepEnemy()
{
	for (int i = 0; i < cEnemyPtrV->size(); i++)
	{
		if ((*cEnemyPtrV)[i]->getWhichEnemy() == 1) //문어
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &(*cEnemyPtrV)[i]->getEEnemy1()->getEnemyRc()) && (*cEnemyPtrV)[i]->getEEnemy1()->getIsDie() == false)
			{
				//player 조건
				cPlayerPtr->setGravity(-5);

				//enemy 조건
				(*cEnemyPtrV)[i]->getEEnemy1()->setIsDie(true);
			}
		}
		else if ((*cEnemyPtrV)[i]->getWhichEnemy() == 2) //벌레
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &(*cEnemyPtrV)[i]->getEEnemy2()->getEnemyRc()) && (*cEnemyPtrV)[i]->getEEnemy2()->getIsDie() == false)
			{
				//player 조건
				cPlayerPtr->setGravity(-5);

				//enemy 조건
				(*cEnemyPtrV)[i]->getEEnemy2()->setIsDie(true);
			}
		}
		else if ((*cEnemyPtrV)[i]->getWhichEnemy() == 3) //크리스탈
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &(*cEnemyPtrV)[i]->getEEnemy3()->getEnemyRc()) && (*cEnemyPtrV)[i]->getEEnemy3()->getIsDie() == false)
			{
				//player 조건
				cPlayerPtr->setGravity(-5);

				//enemy 조건
				(*cEnemyPtrV)[i]->getEEnemy3()->setIsDie(true);
			}
		}
	}
}

//플레이어가 에너미랑 부딪힘
void CollisionClass::playerCrashedEnemy()
{
	for (int i = 0; i < cEnemyPtrV->size(); i++)
	{
		if ((*cEnemyPtrV)[i]->getWhichEnemy() == 1) //문어
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cEnemyPtrV)[i]->getEEnemy1()->getEnemyRc()) && (*cEnemyPtrV)[i]->getEEnemy1()->getIsDie() == false)
			{
				//player 조건

				//enemy 조건
				//exit(0);
			}
		}
		else if ((*cEnemyPtrV)[i]->getWhichEnemy() == 2) //벌레
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cEnemyPtrV)[i]->getEEnemy2()->getEnemyRc()) && (*cEnemyPtrV)[i]->getEEnemy2()->getIsDie() == false)
			{
				//player 조건

				//enemy 조건
				//exit(0);
			}
		}
		else if ((*cEnemyPtrV)[i]->getWhichEnemy() == 3) //크리스탈
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cEnemyPtrV)[i]->getEEnemy3()->getEnemyRc()) && (*cEnemyPtrV)[i]->getEEnemy3()->getIsDie() == false)
			{
				//player 조건

				//enemy 조건
				//exit(0);
			}
		}
	}
}

//플레이어가 펫을 발견
void CollisionClass::playerFindPets()
{
	for (int i = 0; i < cPetsPtrV->size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cPetsPtrV)[i]->getPetRc()))
		{
			//pets 조건
			(*cPetsPtrV)[i]->setIsPetCatch(true);
		}
	}
}

//플레이어가 세이브 포인트를 지남
void CollisionClass::playerSavePoint()
{
	if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cSavePointPtr->getSavePointRc()))
	{
		//savePoint 조건
		cSavePointPtr->setIsFire(true);
		cSavePointPtr->setIsSave(true);
	}
}

//플레이어가 보물상자를 발견
void CollisionClass::playerFindTreasureBox()
{
	for (int i = 0; i < cTreasureBoxPtrV->size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cTreasureBoxPtrV)[i]->getTreasureBoxRc()) && KEYMANAGER->isOnceKeyDown('K'))
		{
			(*cTreasureBoxPtrV)[i]->setIsOpen(true);
		}
	}
}

void CollisionClass::playerGetJewel()
{
	for (int i = 0; i < cTreasureBoxPtrV->size(); i++)
	{
		if ((*cTreasureBoxPtrV)[i]->getIsOpen() == false) continue;

		for (int j = 0; j < (*cTreasureBoxPtrV)[i]->getJewels().size(); j++)
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cTreasureBoxPtrV)[i]->getJewels()[j].jewelRc))
			{

				(*cTreasureBoxPtrV)[i]->getJewels().erase((*cTreasureBoxPtrV)[i]->getJewels().begin() + j);
				break;
			}
		}
	}
}
