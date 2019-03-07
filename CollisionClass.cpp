#include "stdafx.h"
#include "CollisionClass.h"
#include "PlayerClass.h"
#include "EnemyClass.h"
#include "EnemyManagerClass.h"
#include "PetsClass.h"
#include "FieldManagerClass.h"
#include "LandmarkClass.h"

//�÷��̾ ���ʹ̸� ����
void CollisionClass::playerStepEnemy()
{
	for (int i = 0; i < cEnemyPtrV->size(); i++)
	{
		if ((*cEnemyPtrV)[i]->getWhichEnemy() == 1) //����
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &(*cEnemyPtrV)[i]->getEEnemy1()->getEnemyRc()) && (*cEnemyPtrV)[i]->getEEnemy1()->getIsDie() == false)
			{
				//player ����
				cPlayerPtr->setGravity(-5);

				//enemy ����
				(*cEnemyPtrV)[i]->getEEnemy1()->setIsDie(true);
			}
		}
		else if ((*cEnemyPtrV)[i]->getWhichEnemy() == 2) //����
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &(*cEnemyPtrV)[i]->getEEnemy2()->getEnemyRc()) && (*cEnemyPtrV)[i]->getEEnemy2()->getIsDie() == false)
			{
				//player ����
				cPlayerPtr->setGravity(-5);

				//enemy ����
				(*cEnemyPtrV)[i]->getEEnemy2()->setIsDie(true);
			}
		}
		else if ((*cEnemyPtrV)[i]->getWhichEnemy() == 3) //ũ����Ż
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &(*cEnemyPtrV)[i]->getEEnemy3()->getEnemyRc()) && (*cEnemyPtrV)[i]->getEEnemy3()->getIsDie() == false)
			{
				//player ����
				cPlayerPtr->setGravity(-5);

				//enemy ����
				(*cEnemyPtrV)[i]->getEEnemy3()->setIsDie(true);
			}
		}
	}
}

//�÷��̾ ���ʹ̶� �ε���
void CollisionClass::playerCrashedEnemy()
{
	for (int i = 0; i < cEnemyPtrV->size(); i++)
	{
		if ((*cEnemyPtrV)[i]->getWhichEnemy() == 1) //����
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cEnemyPtrV)[i]->getEEnemy1()->getEnemyRc()) && (*cEnemyPtrV)[i]->getEEnemy1()->getIsDie() == false)
			{
				//player ����

				//enemy ����
				//exit(0);
			}
		}
		else if ((*cEnemyPtrV)[i]->getWhichEnemy() == 2) //����
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cEnemyPtrV)[i]->getEEnemy2()->getEnemyRc()) && (*cEnemyPtrV)[i]->getEEnemy2()->getIsDie() == false)
			{
				//player ����

				//enemy ����
				//exit(0);
			}
		}
		else if ((*cEnemyPtrV)[i]->getWhichEnemy() == 3) //ũ����Ż
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cEnemyPtrV)[i]->getEEnemy3()->getEnemyRc()) && (*cEnemyPtrV)[i]->getEEnemy3()->getIsDie() == false)
			{
				//player ����

				//enemy ����
				//exit(0);
			}
		}
	}
}

//�÷��̾ ���� �߰�
void CollisionClass::playerFindPets()
{
	for (int i = 0; i < cPetsPtrV->size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cPetsPtrV)[i]->getPetRc()))
		{
			//pets ����
			(*cPetsPtrV)[i]->setIsPetCatch(true);
		}
	}
}

//�÷��̾ ���̺� ����Ʈ�� ����
void CollisionClass::playerSavePoint()
{
	if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cSavePointPtr->getSavePointRc()))
	{
		//savePoint ����
		cSavePointPtr->setIsFire(true);
		cSavePointPtr->setIsSave(true);
	}
}

//�÷��̾ �������ڸ� �߰�
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
