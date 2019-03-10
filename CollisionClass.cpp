#include "stdafx.h"
#include "CollisionClass.h"
#include "PlayerClass.h"
#include "EnemyClass.h"
#include "EnemyManagerClass.h"
#include "PetsClass.h"
#include "FieldManagerClass.h"
#include "LandmarkClass.h"
#include "bullet.h"

//�÷��̾ ���ʹ̸� ����
void CollisionClass::playerStepEnemy()
{
	//����� �浹
	for (int i = 0; i < cEnemyMPtr->getEEnemy1V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &cEnemyMPtr->getEEnemy1V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy1V()[i]->getIsDie() == false)
		{
			//�÷��̾� ����
			cPlayerPtr->setGravity(-5);

			//enemy����
			cEnemyMPtr->getEEnemy1V()[i]->setIsDie(true);
		}
	}

	//������ �浹
	for (int i = 0; i < cEnemyMPtr->getEEnemy2V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &cEnemyMPtr->getEEnemy2V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy2V()[i]->getIsDie() == false)
		{
			//�÷��̾� ����
			cPlayerPtr->setGravity(-5);

			//enemy����
			cEnemyMPtr->getEEnemy2V()[i]->setIsDie(true);
		}
	}

	//ũ����Ż�̶� �浹
	for (int i = 0; i < cEnemyMPtr->getEEnemy3V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &cEnemyMPtr->getEEnemy3V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy3V()[i]->getIsDie() == false)
		{
			//�÷��̾� ����
			cPlayerPtr->setGravity(-5);

			//enemy����
			cEnemyMPtr->getEEnemy3V()[i]->setIsDie(true);
		}
	}

	//�����̶� �浹
	for (int i = 0; i < cEnemyMPtr->getEEnemy4V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &cEnemyMPtr->getEEnemy4V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy4V()[i]->getIsDie() == false)
		{
			//�÷��̾� ����
			cPlayerPtr->setGravity(-5);

			//enemy����
			cEnemyMPtr->getEEnemy4V()[i]->setIsDie(true);
		}
	}
}

//�÷��̾ ���ʹ̶� �ε���
void CollisionClass::playerCrashedEnemy()
{
	//����� �浹
	for (int i = 0; i < cEnemyMPtr->getEEnemy1V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEEnemy1V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy1V()[i]->getIsDie() == false)
		{
			//�÷��̾� ����

			//enemy����
			//exit(0);
		}
	}

	//������ �浹
	for (int i = 0; i < cEnemyMPtr->getEEnemy2V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEEnemy2V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy2V()[i]->getIsDie() == false)
		{
			//�÷��̾� ����

			//enemy����
			//exit(0);
		}
	}

	//ũ����Ż�̶� �浹
	for (int i = 0; i < cEnemyMPtr->getEEnemy3V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEEnemy3V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy3V()[i]->getIsDie() == false)
		{
			//�÷��̾� ����

			//enemy����
			//exit(0);
		}
	}

	//ũ����Ż�̶� �浹
	for (int i = 0; i < cEnemyMPtr->getEEnemy4V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEEnemy4V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy4V()[i]->getIsDie() == false)
		{
			//�÷��̾� ����

			//enemy����
			//exit(0);
		}
	}
}

//�÷��̾ �Ѿ˿� ����
void CollisionClass::playerCrashedEBullet()
{
	for (int i = 0; i < cEnemyMPtr->getEBullet().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEBullet()[i]->getVBullet()[0].rc))
		{
			//�Ѿ� ����
			cEnemyMPtr->getEBullet()[i]->getVBullet()[0].fire = false;

			break;
		}
	}
}
//�Ѿ��� ���� ����
void CollisionClass::bulletCrashedWall()
{

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
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cTreasureBoxPtrV)[i]->getTreasureBoxRc()) && KEYMANAGER->isStayKeyDown('J'))
		{
			//�������� ����
			(*cTreasureBoxPtrV)[i]->setIsOpen(true);
		}
	}
}

//�÷��̾ ������ �ֿ�
void CollisionClass::playerGetJewel()
{
	for (int i = 0; i < cTreasureBoxPtrV->size(); i++) //��������
	{
		if ((*cTreasureBoxPtrV)[i]->getIsOpen() == false) continue;

		for (int j = 0; j < (*cTreasureBoxPtrV)[i]->getJewels().size(); j++) //����
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cTreasureBoxPtrV)[i]->getJewels()[j].jewelRc))
			{
				//�������� ���� ����
				//(*cTreasureBoxPtrV)[i]->getJewels().erase((*cTreasureBoxPtrV)[i]->getJewels().begin() + j); -�̰��� �׳� ���������� ��
				(*cTreasureBoxPtrV)[i]->getJewels()[j].isJewelGet = true;

				break;
			}
		}
	}
}

//������ ���ư�
void CollisionClass::jewelIsBelieveCanFly()
{
	for (int i = 0; i < cTreasureBoxPtrV->size(); i++) //��������
	{
		if ((*cTreasureBoxPtrV)[i]->getIsOpen() == false) continue;

		for (int j = 0; j < (*cTreasureBoxPtrV)[i]->getJewels().size(); j++) //����
		{
			int getJangle = GetAngle((*cTreasureBoxPtrV)[i]->getJewels()[j].jewelX, (*cTreasureBoxPtrV)[i]->getJewels()[i].jewelY, 1083, 67); //�ڿ� ���ڴ� �ӽ�UI�� ��ǥ�� �Է��� ����
			(*cTreasureBoxPtrV)[i]->getJewels()[j].jewelX += cosf(getJangle * PI / 180) * 3.f;
			(*cTreasureBoxPtrV)[i]->getJewels()[j].jewelY += -sinf(getJangle * PI / 180) * 3.f;

			if ((*cTreasureBoxPtrV)[i]->getJewels()[j].jewelX > 1083 && (*cTreasureBoxPtrV)[i]->getJewels()[j].jewelY < 67)
			{
				(*cTreasureBoxPtrV)[i]->getJewels().erase((*cTreasureBoxPtrV)[i]->getJewels().begin() + j);
			}
			
		}
	}
}
