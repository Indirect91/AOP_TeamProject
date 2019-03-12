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
#include "UniClass.h"

//플레이어가 에너미를 밟음
void CollisionClass::playerStepEnemy()
{
	//문어랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy1V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &cEnemyMPtr->getEEnemy1V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy1V()[i]->getIsDie() == false)
		{
			//플레이어 조건
			cPlayerPtr->setGravity(-5.0f);				//플레이어가 적을 밟으면 띄워준다
			if (KEYMANAGER->isStayKeyDown('K'))
			{
				cPlayerPtr->setGravity(-10.0f);		//점프 키를 누르면 더 높게 뛴다.
			}
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
			cPlayerPtr->setGravity(-5.0f);				//플레이어가 적을 밟으면 띄워준다
			if (KEYMANAGER->isStayKeyDown('K'))
			{
				cPlayerPtr->setGravity(-12.0f);		//점프 키를 누르면 더 높게 뛴다.
			}
			//enemy조건
			cEnemyMPtr->getEEnemy2V()[i]->setIsDie(true);
		}

	}

	//크리스탈이랑 충돌(Bottom 센서랑 충돌)
	for (int i = 0; i < cEnemyMPtr->getEEnemy3V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &cEnemyMPtr->getEEnemy3V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy3V()[i]->getIsDie() == false)
		{
			//플레이어 조건
			cPlayerPtr->setGravity(-5.0f);				//플레이어가 적을 밟으면 띄워준다
			if (KEYMANAGER->isStayKeyDown('K'))
			{
				cPlayerPtr->setGravity(-12.0f);		//점프 키를 누르면 더 높게 뛴다.
			}
			cPlayerPtr->setChangeForm(false);		//젤리 상태일 경우 크리스탈을 밟으면 인간 핍으로 변신!!

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
			cPlayerPtr->setGravity(-5.0f);

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
		if (!cPlayerPtr->getInvincible())
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEEnemy1V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy1V()[i]->getIsDie() == false)
			{
				//플레이어 조건
				if (cPlayerPtr->getIsLeft())
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setX(75);
				}
				else
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setX(-75);
				}
				//enemy조건
				//exit(0);
			}
		}
	}
	if (!cPlayerPtr->getInvincible())
	{
		//벌레랑 충돌
		for (int i = 0; i < cEnemyMPtr->getEEnemy2V().size(); i++)
		{

			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEEnemy2V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy2V()[i]->getIsDie() == false)
			{
				//플레이어 조건
				if (cPlayerPtr->getIsLeft())
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setX(75);
				}
				else
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setX(-75);
				}

				cPlayerPtr->setInvincibleCount(100);

				//enemy조건
				//exit(0);
			}
		}
	}
	//크리스탈이랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy3V().size(); i++)
	{
		if (!cPlayerPtr->getInvincible())
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEEnemy3V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy3V()[i]->getIsDie() == false)
			{
				//플레이어 조건
				if (cPlayerPtr->getIsLeft())
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setX(75);
				}
				else
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setX(-75);
				}

				cPlayerPtr->setInvincibleCount(100);
				//enemy조건
				//exit(0);
			}
		}
	}

	//유령이랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy4V().size(); i++)
	{
		if (!cPlayerPtr->getInvincible())
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEEnemy4V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy4V()[i]->getIsDie() == false)
			{
				//플레이어 조건
				if (cPlayerPtr->getIsLeft())
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setX(75);
				}
				else
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setX(-75);
				}

				cPlayerPtr->setInvincibleCount(100);
				//enemy조건
				//exit(0);
			}
		}
	}
}

//플레이어가 애너미를 공격
void CollisionClass::playerAttackEnemy()
{
	//문어랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy1V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getAttackRc(), &cEnemyMPtr->getEEnemy1V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy1V()[i]->getIsDie() == false)
		{
			//플레이어 조건

			//enemy조건
			if (cPlayerPtr->getIsAttack() == true)
			{
				cEnemyMPtr->getEEnemy1V()[i]->setIsDie(true);
			}
			//exit(0);
		}
	}

	//벌레랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy2V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getAttackRc(), &cEnemyMPtr->getEEnemy2V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy2V()[i]->getIsDie() == false)
		{
			//플레이어 조건

			//enemy조건
			if (cPlayerPtr->getIsAttack() == true)
			{
				cEnemyMPtr->getEEnemy2V()[i]->setIsDie(true);
			}
			//exit(0);
		}
	}

	//크리스탈이랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy3V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getAttackRc(), &cEnemyMPtr->getEEnemy3V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy3V()[i]->getIsDie() == false)
		{
			//플레이어 조건

			//enemy조건
			if (cPlayerPtr->getIsAttack() == true)
			{
				cEnemyMPtr->getEEnemy3V()[i]->setIsDie(true);
			}
			//exit(0);
		}
	}

	//유령이랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy4V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getAttackRc(), &cEnemyMPtr->getEEnemy4V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy4V()[i]->getIsDie() == false)
		{
			//플레이어 조건

			//enemy조건
			if (cPlayerPtr->getIsAttack() == true)
			{
				cEnemyMPtr->getEEnemy4V()[i]->setIsDie(true);
			}
			//exit(0);
		}
	}
}

//플레이어와 장애물 충돌
void CollisionClass::playerDamegeThorn()
{
	if (!cPlayerPtr->getInvincible())
	{
		//1스테이지 가시랑 충돌
		for (int i = 0; i < cFieldPtr->thornPtr->getThornStage1().size(); i++)
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->thornPtr->getThornStage1()[i]))
			{
				//플레이어 조건
				cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
				if (cPlayerPtr->getIsLeft())
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setX(75);
				}
				else
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setX(-75);
				}

				cPlayerPtr->setInvincibleCount(100);
			}
		}
		//보스 스테이지 가시랑 충돌
		for (int i = 0; i < cFieldPtr->thornPtr->getThornBossStage().size(); i++)
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->thornPtr->getThornBossStage()[i]))
			{
				//플레이어 조건
				cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
				if (cPlayerPtr->getIsLeft())
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setX(75);

				}
				else
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setX(-75);
				}

				cPlayerPtr->setInvincibleCount(100);
			}
		}
	}
}

//플레이어가 변신할때 충돌
void CollisionClass::playerChangeTile()
{
	for (int i = 0; i < cFieldPtr->hideTilePtr->getHideTile().size(); i++)
	{
		cFieldPtr->hideTilePtr->setCount(cFieldPtr->hideTilePtr->getCount() + 1);

		if (cFieldPtr->hideTilePtr->getCount() % 20 == 0)
		{
			cFieldPtr->hideTilePtr->setBoomFrameX(cFieldPtr->hideTilePtr->getBoomFrameX() + 1);
		}
		if (cFieldPtr->hideTilePtr->getBoomFrameX() > 13 && cFieldPtr->hideTilePtr->getBoom() == true)
		{
			cFieldPtr->hideTilePtr->setBoomFrameX(0);
		}
		if (IntersectRect(&cEmpty, &cPlayerPtr->getTileDestoryRc(), &cFieldPtr->hideTilePtr->getHideTile()[i].rc))
		{
			cFieldPtr->hideTilePtr->getHideTile()[i].isTouch = false;
			cFieldPtr->hideTilePtr->setBoom(false);
			//cFieldPtr->hideTilePtr->setIsBoom(false);
			if (cFieldPtr->hideTilePtr->getHideTile()[i].isTouch == false)
			{
				cPlayerPtr->setBombTileCrashDown(true);
			}
			if (cFieldPtr->hideTilePtr->getBoomFrameX() > 13)
			{
				cFieldPtr->hideTilePtr->setBoomFrameX(13);
			}
		}
	}
}

void CollisionClass::playerCollisionHideTile()
{
	if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->hideTilePtr->getHideBlock()))
	{
		cFieldPtr->hideTilePtr->setImageCount(100);
	}
	else if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->hideTilePtr->getHideBlockTwo()))
	{
		cFieldPtr->hideTilePtr->setImageCount(100);
	}
	else if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->hideTilePtr->getGrass()))
	{
		cFieldPtr->hideTilePtr->setImageCount(100);
	}
	else cFieldPtr->hideTilePtr->setImageCount(255);

}

void CollisionClass::playerChangeEnemyCrash()
{
	//문어랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy1V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getEnemyCrashRc(), &cEnemyMPtr->getEEnemy1V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy1V()[i]->getIsDie() == false)
		{
			//플레이어 조건

			//enemy조건
			cEnemyMPtr->getEEnemy1V()[i]->setIsDie(true);
		}
	}

	//벌레랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy2V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getEnemyCrashRc(), &cEnemyMPtr->getEEnemy2V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy2V()[i]->getIsDie() == false)
		{
			//플레이어 조건

			//enemy조건
			cEnemyMPtr->getEEnemy2V()[i]->setIsDie(true);
		}
	}

	//크리스탈이랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy3V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getEnemyCrashRc(), &cEnemyMPtr->getEEnemy3V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy3V()[i]->getIsDie() == false)
		{
			//플레이어 조건

			//enemy조건
			cEnemyMPtr->getEEnemy3V()[i]->setIsDie(true);
		}
	}

	//유령이랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy4V().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getEnemyCrashRc(), &cEnemyMPtr->getEEnemy4V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy4V()[i]->getIsDie() == false)
		{
			//플레이어 조건

			//enemy조건
			cEnemyMPtr->getEEnemy4V()[i]->setIsDie(true);
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
void CollisionClass::playerFindPets(int _wherePet)
{
	wherePet = _wherePet;

	for (int i = 0; i < cPetsPtrV->size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cPetsPtrV)[i]->getPetRc()) && (*cPetsPtrV)[i]->getIsPetFind() == false)
		{
			//pets 조건
			//스테이지1
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
			//보스 스테이지
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


//플레이어가 클리어 포인트에 닿음
void CollisionClass::playerClearPoint()
{
	if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cClearPointPtr->getClearPointRc()))
	{
		//clearPoint 조건
		exit(0);
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
				float getJangle = GetAngle((*cTreasureBoxPtrV)[i]->getJewels()[j].jewelX, (*cTreasureBoxPtrV)[i]->getJewels()[i].jewelY, 1083 + CAMERA.getCRc().left, 67 + CAMERA.getCRc().top); //뒤에 숫자는 임시UI쪽 좌표를 입력한 것임
				(*cTreasureBoxPtrV)[i]->getJewels()[j].jewelX += cosf(getJangle) * (*cTreasureBoxPtrV)[i]->getJewels()[j].jSpeed;
				(*cTreasureBoxPtrV)[i]->getJewels()[j].jewelY += -sinf(getJangle) * (*cTreasureBoxPtrV)[i]->getJewels()[j].jSpeed;
				(*cTreasureBoxPtrV)[i]->getJewels()[j].jSpeed += 0.5;
			}
		}
	}
}