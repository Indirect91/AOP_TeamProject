#include "stdafx.h"
#include "CollisionClass.h"
#include "PlayerClass.h"
#include "EnemyClass.h"
#include "EnemyManagerClass.h"
#include "PetsClass.h"
#include "FieldManagerClass.h"
#include "LandmarkClass.h"
#include "bullet.h"
#include "UIClass.h"

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

	//ũ����Ż�̶� �浹(Bottom ������ �浹)
	for (int i = 0; i < cEnemyMPtr->getEEnemy3V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &cEnemyMPtr->getEEnemy3V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy3V()[i]->getIsDie() == false)
		{
			//�÷��̾� ����

			cPlayerPtr->setGravity(-8);
			if (KEYMANAGER->isStayKeyDown('K'))
			{
				cPlayerPtr->setGravity(-15);
			}
			cPlayerPtr->setChangeForm(false);

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

void CollisionClass::playerAttackEnemy()
{
	//����� �浹
	for (int i = 0; i < cEnemyMPtr->getEEnemy1V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getAttackRc(), &cEnemyMPtr->getEEnemy1V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy1V()[i]->getIsDie() == false)
		{
			//�÷��̾� ����

			//enemy����
			if (cPlayerPtr->getIsAttack() == true)
			{
				cEnemyMPtr->getEEnemy1V()[i]->setIsDie(true);
			}
			//exit(0);
		}
	}

	//������ �浹
	for (int i = 0; i < cEnemyMPtr->getEEnemy2V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getAttackRc(), &cEnemyMPtr->getEEnemy2V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy2V()[i]->getIsDie() == false)
		{
			//�÷��̾� ����

			//enemy����
			if (cPlayerPtr->getIsAttack() == true)
			{
				cEnemyMPtr->getEEnemy2V()[i]->setIsDie(true);
			}
			//exit(0);
		}
	}

	//ũ����Ż�̶� �浹
	for (int i = 0; i < cEnemyMPtr->getEEnemy3V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getAttackRc(), &cEnemyMPtr->getEEnemy3V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy3V()[i]->getIsDie() == false)
		{
			//�÷��̾� ����

			//enemy����
			if (cPlayerPtr->getIsAttack() == true)
			{
				cEnemyMPtr->getEEnemy3V()[i]->setIsDie(true);
			}
			//exit(0);
		}
	}

	//�����̶� �浹
	for (int i = 0; i < cEnemyMPtr->getEEnemy4V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getAttackRc(), &cEnemyMPtr->getEEnemy4V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy4V()[i]->getIsDie() == false)
		{
			//�÷��̾� ����

			//enemy����
			if (cPlayerPtr->getIsAttack() == true)
			{
				cEnemyMPtr->getEEnemy4V()[i]->setIsDie(true);
			}
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
void CollisionClass::playerFindPets(int _wherePet)
{
	wherePet = _wherePet;

	for (int i = 0; i < cPetsPtrV->size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cPetsPtrV)[i]->getPetRc()) && (*cPetsPtrV)[i]->getIsPetFind() == false)
		{
			//pets ����
			//��������1
			if ((*cPetsPtrV)[i]->getWhichPet() == PetsClass::PetsTypes::seal && SCENEMANAGER->getCurrent() == "Stage1")
			{
				(*cPetsPtrV)[i]->setIsPetFind(true);
				cUIPtr->setCheckSealS1_IsCheck(true);

				TXTDATA.getCurrentPipData()->isFindSealS1 = true;
			}
			if ((*cPetsPtrV)[i]->getWhichPet() == PetsClass::PetsTypes::bat && SCENEMANAGER->getCurrent() == "Stage1")
			{
				(*cPetsPtrV)[i]->setIsPetFind(true);
				cUIPtr->setCheckBatS1_IsCheck(true);

				TXTDATA.getCurrentPipData()->isFindBatS1 = true;
			}
			if ((*cPetsPtrV)[i]->getWhichPet() == PetsClass::PetsTypes::shark && SCENEMANAGER->getCurrent() == "Stage1")
			{
				(*cPetsPtrV)[i]->setIsPetFind(true);
				cUIPtr->setCheckSharkS1_IsCheck(true);

				TXTDATA.getCurrentPipData()->isFindSharkS1 = true;
			}
			//���� ��������
			if ((*cPetsPtrV)[i]->getWhichPet() == PetsClass::PetsTypes::seal && SCENEMANAGER->getCurrent() == "BossStage")
			{
				(*cPetsPtrV)[i]->setIsPetFind(true);
				cUIPtr->setCheckSealB_IsCheck(true);

				TXTDATA.getCurrentPipData()->isFindSealB = true;
			}
			if ((*cPetsPtrV)[i]->getWhichPet() == PetsClass::PetsTypes::bat && SCENEMANAGER->getCurrent() == "BossStage")
			{
				(*cPetsPtrV)[i]->setIsPetFind(true);
				cUIPtr->setCheckBatB_IsCheck(true);

				TXTDATA.getCurrentPipData()->isFindBatB = true;
			}
			if ((*cPetsPtrV)[i]->getWhichPet() == PetsClass::PetsTypes::shark && SCENEMANAGER->getCurrent() == "BossStage")
			{
				(*cPetsPtrV)[i]->setIsPetFind(true);
				cUIPtr->setCheckSharkB_IsCheck(true);

				TXTDATA.getCurrentPipData()->isFindSharkB = true;
			}

		}
	}
}


//�÷��̾ Ŭ���� ����Ʈ�� ����
void CollisionClass::playerClearPoint()
{
	if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cClearPointPtr->getClearPointRc()))
	{
		//clearPoint ����
		exit(0);
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
			if ((*cTreasureBoxPtrV)[i]->getJewels()[j].isJewelGet == false && (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cTreasureBoxPtrV)[i]->getJewels()[j].jewelRc)))
			{
				(*cTreasureBoxPtrV)[i]->getJewels()[j].isJewelGet = true;
			}

			if (((*cTreasureBoxPtrV)[i]->getJewels()[j].jewelX > 900 + CAMERA.getCRc().left && (*cTreasureBoxPtrV)[i]->getJewels()[j].jewelY < 100 + CAMERA.getCRc().top && (*cTreasureBoxPtrV)[i]->getJewels()[j].jewelVisible == true))
			{
				(*cTreasureBoxPtrV)[i]->getJewels()[j].jewelVisible = false;
			}

			if ((*cTreasureBoxPtrV)[i]->getJewels()[j].isJewelGet == true && (*cTreasureBoxPtrV)[i]->getJewels()[j].jewelVisible == true)
			{
				(*cTreasureBoxPtrV)[i]->getJewels()[j].jGravity = 0;
				float getJangle = GetAngle((*cTreasureBoxPtrV)[i]->getJewels()[j].jewelX, (*cTreasureBoxPtrV)[i]->getJewels()[i].jewelY, 1083 + CAMERA.getCRc().left, 67 + CAMERA.getCRc().top); //�ڿ� ���ڴ� �ӽ�UI�� ��ǥ�� �Է��� ����
				(*cTreasureBoxPtrV)[i]->getJewels()[j].jewelX += cosf(getJangle) * (*cTreasureBoxPtrV)[i]->getJewels()[j].jSpeed;
				(*cTreasureBoxPtrV)[i]->getJewels()[j].jewelY += -sinf(getJangle) * (*cTreasureBoxPtrV)[i]->getJewels()[j].jSpeed;
				(*cTreasureBoxPtrV)[i]->getJewels()[j].jSpeed += 0.5;
			}
		}
	}
}