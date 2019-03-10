#include "stdafx.h"
#include "CollisionClass.h"
#include "PlayerClass.h"
#include "EnemyClass.h"
#include "EnemyManagerClass.h"
#include "PetsClass.h"
#include "FieldManagerClass.h"
#include "LandmarkClass.h"
#include "bullet.h"

//플레이어가 에너미를 밟음
void CollisionClass::playerStepEnemy()
{
	//문어랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy1V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &cEnemyMPtr->getEEnemy1V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy1V()[i]->getIsDie() == false)
		{
			//플레이어 조건
			cPlayerPtr->setGravity(-5);

			//enemy조건
			cEnemyMPtr->getEEnemy1V()[i]->setIsDie(true);
		}
	}

	//벌레랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy2V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &cEnemyMPtr->getEEnemy2V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy2V()[i]->getIsDie() == false)
		{
			//플레이어 조건
			cPlayerPtr->setGravity(-5);

			//enemy조건
			cEnemyMPtr->getEEnemy2V()[i]->setIsDie(true);
		}
	}

	//크리스탈이랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy3V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &cEnemyMPtr->getEEnemy3V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy3V()[i]->getIsDie() == false)
		{
			//플레이어 조건
			cPlayerPtr->setGravity(-5);

			//enemy조건
			cEnemyMPtr->getEEnemy3V()[i]->setIsDie(true);
		}
	}

	//유령이랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy4V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &cEnemyMPtr->getEEnemy4V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy4V()[i]->getIsDie() == false)
		{
			//플레이어 조건
			cPlayerPtr->setGravity(-5);

			//enemy조건
			cEnemyMPtr->getEEnemy4V()[i]->setIsDie(true);
		}
	}
}

//플레이어가 에너미랑 부딪힘
void CollisionClass::playerCrashedEnemy()
{
	//문어랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy1V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEEnemy1V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy1V()[i]->getIsDie() == false)
		{
			//플레이어 조건

			//enemy조건
			//exit(0);
		}
	}

	//벌레랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy2V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEEnemy2V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy2V()[i]->getIsDie() == false)
		{
			//플레이어 조건

			//enemy조건
			//exit(0);
		}
	}

	//크리스탈이랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy3V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEEnemy3V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy3V()[i]->getIsDie() == false)
		{
			//플레이어 조건

			//enemy조건
			//exit(0);
		}
	}

	//크리스탈이랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy4V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEEnemy4V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy4V()[i]->getIsDie() == false)
		{
			//플레이어 조건

			//enemy조건
			//exit(0);
		}
	}
}

//플레이어가 총알에 맞음
void CollisionClass::playerCrashedEBullet()
{
	for (int i = 0; i < cEnemyMPtr->getEBullet().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEBullet()[i]->getVBullet()[0].rc))
		{
			//총알 조건
			cEnemyMPtr->getEBullet()[i]->getVBullet()[0].fire = false;

			break;
		}
	}
}
//총알이 벽에 맞음
void CollisionClass::bulletCrashedWall()
{

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
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cTreasureBoxPtrV)[i]->getTreasureBoxRc()) && KEYMANAGER->isStayKeyDown('J'))
		{
			//보물상자 조건
			(*cTreasureBoxPtrV)[i]->setIsOpen(true);
		}
	}
}

//플레이어가 보석을 주움
void CollisionClass::playerGetJewel()
{
	for (int i = 0; i < cTreasureBoxPtrV->size(); i++) //보물상자
	{
		if ((*cTreasureBoxPtrV)[i]->getIsOpen() == false) continue;

		for (int j = 0; j < (*cTreasureBoxPtrV)[i]->getJewels().size(); j++) //보석
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cTreasureBoxPtrV)[i]->getJewels()[j].jewelRc))
			{
				//보물상자 보석 조건
				//(*cTreasureBoxPtrV)[i]->getJewels().erase((*cTreasureBoxPtrV)[i]->getJewels().begin() + j); -이것은 그냥 지워버리는 것
				(*cTreasureBoxPtrV)[i]->getJewels()[j].isJewelGet = true;

				break;
			}
		}
	}
}

//보석이 날아감
void CollisionClass::jewelIsBelieveCanFly()
{
	for (int i = 0; i < cTreasureBoxPtrV->size(); i++) //보물상자
	{
		if ((*cTreasureBoxPtrV)[i]->getIsOpen() == false) continue;

		for (int j = 0; j < (*cTreasureBoxPtrV)[i]->getJewels().size(); j++) //보석
		{
			int getJangle = GetAngle((*cTreasureBoxPtrV)[i]->getJewels()[j].jewelX, (*cTreasureBoxPtrV)[i]->getJewels()[i].jewelY, 1083, 67); //뒤에 숫자는 임시UI쪽 좌표를 입력한 것임
			(*cTreasureBoxPtrV)[i]->getJewels()[j].jewelX += cosf(getJangle * PI / 180) * 3.f;
			(*cTreasureBoxPtrV)[i]->getJewels()[j].jewelY += -sinf(getJangle * PI / 180) * 3.f;

			if ((*cTreasureBoxPtrV)[i]->getJewels()[j].jewelX > 1083 && (*cTreasureBoxPtrV)[i]->getJewels()[j].jewelY < 67)
			{
				(*cTreasureBoxPtrV)[i]->getJewels().erase((*cTreasureBoxPtrV)[i]->getJewels().begin() + j);
			}
			
		}
	}
}
