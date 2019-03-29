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
#include "FlowerClass.h"
#include "BossClass.h"

//플레이어가 에너미를 밟음
void CollisionClass::playerStepEnemy()
{
	if (!cPlayerPtr->getInvincible())
	{
		//문어랑 충돌
		for (int i = 0; i < cEnemyMPtr->getEEnemy1V().size(); i++)
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &cEnemyMPtr->getEEnemy1V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy1V()[i]->getIsDie() == false)
			{
				SOUNDMANAGER->play("에너미사망", TXTDATA.refSFXSound());
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
				SOUNDMANAGER->play("에너미사망", TXTDATA.refSFXSound());
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
				SOUNDMANAGER->play("진화", TXTDATA.refSFXSound());
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
				SOUNDMANAGER->play("에너미사망", TXTDATA.refSFXSound());
				//플레이어 조건
				cPlayerPtr->setGravity(-5.0f);

				//enemy조건
				cEnemyMPtr->getEEnemy4V()[i]->setIsDie(true);
			}
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
				SOUNDMANAGER->play("플레이어피격", TXTDATA.refSFXSound());
				cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
				//플레이어 조건
				if (cPlayerPtr->getIsLeft())
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setLeftRepulsionPower(4.0f);
				}
				else
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setRightRepulsionPower(4.0f);
				}

				cPlayerPtr->setInvincibleCount(60);
				//enemy조건
				//exit(0);
			}
		}
		else
		{
			cPlayerPtr->setTestCount(cPlayerPtr->getTestCount() + 1);

			if (cPlayerPtr->getInvincibleCount() < 61)
			{
				if (cPlayerPtr->getTestCount() % 10 == 0)
				{
					cPlayerPtr->setInvincibleCountAlpha(cPlayerPtr->getInvincibleCountAlpha() + 125);
				}
			}
		}
	}

	//벌레랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy2V().size(); i++)
	{
		if (!cPlayerPtr->getInvincible())		//false일때만 충돌
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEEnemy2V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy2V()[i]->getIsDie() == false)
			{
				SOUNDMANAGER->play("플레이어피격", TXTDATA.refSFXSound());
				cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
				//플레이어 조건
				if (cPlayerPtr->getIsLeft())
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setLeftRepulsionPower(4.0f);
				}
				else
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setRightRepulsionPower(4.0f);
				}

				cPlayerPtr->setInvincibleCount(60);

				//enemy조건
				//exit(0);
			}
		}
		else
		{
			cPlayerPtr->setTestCount(cPlayerPtr->getTestCount() + 1);
			if (cPlayerPtr->getInvincibleCount() < 61)
			{
				if (cPlayerPtr->getTestCount() % 10 == 0)
				{
					cPlayerPtr->setInvincibleCountAlpha(cPlayerPtr->getInvincibleCountAlpha() + 1);
				}
			}
		}
	}
	//크리스탈이랑 충돌
	for (int i = 0; i < cEnemyMPtr->getEEnemy3V().size(); i++)
	{

		if (!cPlayerPtr->getInvincible())
		{
			cPlayerPtr->setTestCount(0);
			cPlayerPtr->setInvincibleCountAlpha(0);
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEEnemy3V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy3V()[i]->getIsDie() == false)
			{
				SOUNDMANAGER->play("플레이어피격", TXTDATA.refSFXSound());
				cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
				//플레이어 조건
				if (cPlayerPtr->getIsLeft())
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setLeftRepulsionPower(5.0f);
				}
				else
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setRightRepulsionPower(5.0f);
				}

				cPlayerPtr->setInvincibleCount(60);
				//enemy조건
				//exit(0);
			}
		}
		else
		{
			cPlayerPtr->setTestCount(cPlayerPtr->getTestCount() + 1);

			if (cPlayerPtr->getInvincibleCount() < 61)
			{
				if (cPlayerPtr->getTestCount() % 10 == 0)
				{
					cPlayerPtr->setInvincibleCountAlpha(cPlayerPtr->getInvincibleCountAlpha() + 1);

					if (cPlayerPtr->getInvincibleCountAlpha() >= 255)
					{
						cPlayerPtr->setInvincibleCountAlpha(255);
					}
				}
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
				SOUNDMANAGER->play("플레이어피격", TXTDATA.refSFXSound());
				cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
				//플레이어 조건
				if (cPlayerPtr->getIsLeft())
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setRightRepulsionPower(5.0f);
				}
				else
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setLeftRepulsionPower(5.0f);
				}

				cPlayerPtr->setInvincibleCount(60);
				//enemy조건
				//exit(0);
			}
		}
		else
		{
			cPlayerPtr->setTestCount(cPlayerPtr->getTestCount() + 1);

			if (cPlayerPtr->getInvincibleCount() < 61)
			{
				if (cPlayerPtr->getTestCount() % 10 == 0)
				{
					cPlayerPtr->setInvincibleCountAlpha(cPlayerPtr->getInvincibleCountAlpha() + 125);
				}
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
				SOUNDMANAGER->play("에너미사망", TXTDATA.refSFXSound());
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
				SOUNDMANAGER->play("에너미사망", TXTDATA.refSFXSound());
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
				SOUNDMANAGER->play("에너미사망", TXTDATA.refSFXSound());
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
				SOUNDMANAGER->play("에너미사망", TXTDATA.refSFXSound());
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
					cPlayerPtr->setLeftRepulsionPower(4.0f);
				}
				else
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setRightRepulsionPower(4.0f);
				}

				cPlayerPtr->setInvincibleCount(60);
			}
		}
	}
	else
	{
		cPlayerPtr->setTestCount(cPlayerPtr->getTestCount() + 1);

		if (cPlayerPtr->getInvincibleCount() < 61)
		{
			if (cPlayerPtr->getTestCount() % 10 == 0)
			{
				cPlayerPtr->setInvincibleCountAlpha(cPlayerPtr->getInvincibleCountAlpha() + 125);
			}
		}
	}

	if (!cPlayerPtr->getInvincible())
	{
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
					cPlayerPtr->setLeftRepulsionPower(4.0f);
				}
				else
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setRightRepulsionPower(4.0f);
				}

				cPlayerPtr->setInvincibleCount(60);
			}
		}
	}
	else
	{
		cPlayerPtr->setTestCount(cPlayerPtr->getTestCount() + 1);

		if (cPlayerPtr->getInvincibleCount() < 61)
		{
			if (cPlayerPtr->getTestCount() % 10 == 0)
			{
				cPlayerPtr->setInvincibleCountAlpha(cPlayerPtr->getInvincibleCountAlpha() + 125);
			}
		}
	}
}

//플레이어가 변신할때 타일과 충돌
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

//플레이어와 숨겨진 타일 충돌
void CollisionClass::playerCollisionHideTile()
{
	if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->hideTilePtr->getHideBlock()))
	{
		if(cFieldPtr->hideTilePtr->refImageCount()>100)
			cFieldPtr->hideTilePtr->refImageCount()-=5;
	}
	else if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->hideTilePtr->getHideBlockTwo()))
	{
		if (cFieldPtr->hideTilePtr->refImageCount() > 100)
			cFieldPtr->hideTilePtr->refImageCount() -= 5;
	}
	else if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->hideTilePtr->getGrass()))
	{
		if (cFieldPtr->hideTilePtr->refImageCount() > 100)
			cFieldPtr->hideTilePtr->refImageCount() -= 5;
	}
	else if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->hideTilePtr->getBossTile1()))
	{
		if (cFieldPtr->hideTilePtr->refImageCount() > 100)
			cFieldPtr->hideTilePtr->refImageCount() -= 5;
	}
	else if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->hideTilePtr->getBossTile2()))
	{
		if (cFieldPtr->hideTilePtr->refImageCount() > 100)
			cFieldPtr->hideTilePtr->refImageCount() -= 5;
	}
	else
	{
		if (cFieldPtr->hideTilePtr->refImageCount() < 250)
			cFieldPtr->hideTilePtr->refImageCount() += 5;
	}

}

//플레이어의 변신 이펙트와 애너미 충돌
void CollisionClass::playerChangeEnemyCrash()
{
	//문어랑 충돌
	if (cPlayerPtr->getIsBomb())
	{
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
}

//플레이어와 점프대 충돌
void CollisionClass::playerJumpJump()
{
	if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->uniPtr->getJumpRCone())
		|| IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->uniPtr->getJumpRCtwo()))
	{
		SOUNDMANAGER->play("점프대", TXTDATA.refSFXSound());
		//인간 핍 상태
		if (!cPlayerPtr->getChangeForm())
		{
			cPlayerPtr->setY(10);
			cPlayerPtr->setGravity(-10);
			if (KEYMANAGER->isStayKeyDown('K'))
			{
				cPlayerPtr->setGravity(-13);
				cPlayerPtr->setSensorBottomIsJump(false);
			}
		}
		//젤리 핍 상태
		else
		{
			cPlayerPtr->setY(10);
			cPlayerPtr->setGravity(-13);
			if (KEYMANAGER->isStayKeyDown('K'))
			{
				cPlayerPtr->setGravity(-16);
				cPlayerPtr->setSensorBottomIsJump(false);
			}
		}
	}

}

//플레이어 vs 보스 충돌
void CollisionClass::playerBossCollision()
{

}

//플레이어가 총알에 맞음
void CollisionClass::playerCrashedEBullet()
{
	if (!cPlayerPtr->getInvincible())
	{
		for (int i = 0; i < cEnemyMPtr->getEBullet().size(); i++)
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEBullet()[i]->getVBullet()[0].rc) && cEnemyMPtr->getEBullet()[i]->getVBullet()[0].fire == true)
			{
				SOUNDMANAGER->play("플레이어피격", TXTDATA.refSFXSound());
				//플레이어 조건
				cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
				if (cPlayerPtr->getIsLeft())
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setLeftRepulsionPower(4.0f);
				}
				else
				{
					cPlayerPtr->setY(5);
					cPlayerPtr->setGravity(-5.0f);
					cPlayerPtr->setRightRepulsionPower(4.0f);
				}

				cPlayerPtr->setInvincibleCount(60);

				//총알 조건
				cEnemyMPtr->getEBullet()[i]->getVBullet()[0].fire = false;

				break;
			}
		}

		if (SCENEMANAGER->getCurrent() == "BossStage")
		{
			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollPtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].rc))
				{
					SOUNDMANAGER->play("플레이어피격", TXTDATA.refSFXSound());
					//플레이어 조건
					cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
					if (cPlayerPtr->getIsLeft())
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setLeftRepulsionPower(4.0f);
					}
					else
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setRightRepulsionPower(4.0f);
					}

					cPlayerPtr->setInvincibleCount(60);

					//총알 조건
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}

			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollLeftPtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollLeftPtr()->getVBullet()[i].rc))
				{
					SOUNDMANAGER->play("플레이어피격", TXTDATA.refSFXSound());
					//플레이어 조건
					cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
					if (cPlayerPtr->getIsLeft())
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setLeftRepulsionPower(4.0f);
					}
					else
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setRightRepulsionPower(4.0f);
					}

					cPlayerPtr->setInvincibleCount(60);

					//총알 조건
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}

			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollRightPtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollRightPtr()->getVBullet()[i].rc))
				{
					SOUNDMANAGER->play("플레이어피격", TXTDATA.refSFXSound());
					//플레이어 조건
					cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
					if (cPlayerPtr->getIsLeft())
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setLeftRepulsionPower(4.0f);
					}
					else
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setRightRepulsionPower(4.0f);
					}

					cPlayerPtr->setInvincibleCount(60);

					//총알 조건
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}

			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollLeftTwoPtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollLeftTwoPtr()->getVBullet()[i].rc))
				{
					SOUNDMANAGER->play("플레이어피격", TXTDATA.refSFXSound());
					//플레이어 조건
					cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
					if (cPlayerPtr->getIsLeft())
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setLeftRepulsionPower(4.0f);
					}
					else
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setRightRepulsionPower(4.0f);
					}

					cPlayerPtr->setInvincibleCount(60);

					//총알 조건
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}

			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollRightTwoPtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollRightTwoPtr()->getVBullet()[i].rc))
				{
					SOUNDMANAGER->play("플레이어피격", TXTDATA.refSFXSound());
					//플레이어 조건
					cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
					if (cPlayerPtr->getIsLeft())
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setLeftRepulsionPower(4.0f);
					}
					else
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setRightRepulsionPower(4.0f);
					}

					cPlayerPtr->setInvincibleCount(60);

					//총알 조건
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}

			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollUpOnePtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollUpOnePtr()->getVBullet()[i].rc)
					&& cFieldPtr->flowerPtr->getFireBollUpOnePtr()->getVBullet()[i].fire == true)
				{
					SOUNDMANAGER->play("플레이어피격", TXTDATA.refSFXSound());
					//플레이어 조건
					cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
					if (cPlayerPtr->getIsLeft())
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setLeftRepulsionPower(4.0f);
					}
					else
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setRightRepulsionPower(4.0f);
					}

					cPlayerPtr->setInvincibleCount(60);

					//총알 조건
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}

			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollUpTwoPtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollUpTwoPtr()->getVBullet()[i].rc)
					&& cFieldPtr->flowerPtr->getFireBollUpTwoPtr()->getVBullet()[i].fire == true)
				{
					SOUNDMANAGER->play("플레이어피격", TXTDATA.refSFXSound());
					//플레이어 조건
					cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
					if (cPlayerPtr->getIsLeft())
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setLeftRepulsionPower(4.0f);
					}
					else
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setRightRepulsionPower(4.0f);
					}

					cPlayerPtr->setInvincibleCount(60);

					//총알 조건
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}

			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollUpThreePtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollUpThreePtr()->getVBullet()[i].rc)
					&& cFieldPtr->flowerPtr->getFireBollUpThreePtr()->getVBullet()[i].fire == true)
				{
					SOUNDMANAGER->play("플레이어피격", TXTDATA.refSFXSound());
					//플레이어 조건
					cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
					if (cPlayerPtr->getIsLeft())
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setLeftRepulsionPower(4.0f);
					}
					else
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setRightRepulsionPower(4.0f);
					}

					cPlayerPtr->setInvincibleCount(60);

					//총알 조건
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}

			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollDownOnePtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollDownOnePtr()->getVBullet()[i].rc)
					&& cFieldPtr->flowerPtr->getFireBollDownOnePtr()->getVBullet()[i].fire == true)
				{
					SOUNDMANAGER->play("플레이어피격", TXTDATA.refSFXSound());
					//플레이어 조건
					cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
					if (cPlayerPtr->getIsLeft())
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setLeftRepulsionPower(4.0f);
					}
					else
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setRightRepulsionPower(4.0f);
					}

					cPlayerPtr->setInvincibleCount(60);

					//총알 조건
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}

			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollDownTwoPtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollDownTwoPtr()->getVBullet()[i].rc)
					&& cFieldPtr->flowerPtr->getFireBollDownTwoPtr()->getVBullet()[i].fire == true)
				{
					SOUNDMANAGER->play("플레이어피격", TXTDATA.refSFXSound());
					//플레이어 조건
					cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
					if (cPlayerPtr->getIsLeft())
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setLeftRepulsionPower(4.0f);
					}
					else
					{
						cPlayerPtr->setY(5);
						cPlayerPtr->setGravity(-5.0f);
						cPlayerPtr->setRightRepulsionPower(4.0f);
					}

					cPlayerPtr->setInvincibleCount(60);

					//총알 조건
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}
		}
	}
}
//총알이 벽에 맞음
void CollisionClass::bulletCrashedWall()
{

}

void CollisionClass::playerVineCut()
{
	if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &cFieldPtr->hideTilePtr->getVineRC()))
	{
		if (cFieldPtr->hideTilePtr->getIsVine() == false)
		{
			cPlayerPtr->setGravity(-0.4);
			cPlayerPtr->getSensorBottom().isTouch = true;
			//cPlayerPtr->setY();

		}
	}
	if (IntersectRect(&cEmpty, &cPlayerPtr->getAttackRc(), &cFieldPtr->hideTilePtr->getVineRC()))
	{
		cFieldPtr->hideTilePtr->setIsVine(true);
	}
}

void CollisionClass::playerBreakTileStage1()
{
	for (int i = 0; i < cFieldPtr->breakTilePtr->getTileListone().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorBottom().sensorRc, &cFieldPtr->breakTilePtr->getTileListone()[i]->rc))
		{
			cPlayerPtr->setGravity(0);
			cPlayerPtr->setRealY(cFieldPtr->breakTilePtr->getTileListone()[i]->rc.top-cPlayerPtr->getHeight());
			cPlayerPtr->getSensorBottom().isTouch = true;
			cPlayerPtr->getSensorBottom().isJump = false;
			cFieldPtr->breakTilePtr->setBoolTileone(true);
		}

		if (cFieldPtr->breakTilePtr->getBoolTileone() == true)
		{
			cFieldPtr->breakTilePtr->breakTileList(cFieldPtr->breakTilePtr->getTileListone());
		}
	}


	for (int i = 0; i < cFieldPtr->breakTilePtr->getTileListtwo().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorBottom().sensorRc, &cFieldPtr->breakTilePtr->getTileListtwo()[i]->rc))
		{
			cPlayerPtr->setGravity(0);
			cPlayerPtr->setRealY(cFieldPtr->breakTilePtr->getTileListtwo()[i]->rc.top - cPlayerPtr->getHeight());
			cPlayerPtr->getSensorBottom().isTouch = true;
			cPlayerPtr->getSensorBottom().isJump = false;
			cFieldPtr->breakTilePtr->setBoolTiletwo(true);
		}

		if (cFieldPtr->breakTilePtr->getBoolTiletwo() == true)
		{
			cFieldPtr->breakTilePtr->breakTileList(cFieldPtr->breakTilePtr->getTileListtwo());
		}
	}

	for (int i = 0; i < cFieldPtr->breakTilePtr->getTileListthree().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorBottom().sensorRc, &cFieldPtr->breakTilePtr->getTileListthree()[i]->rc))
		{
			cPlayerPtr->setGravity(0);
			cPlayerPtr->setRealY(cFieldPtr->breakTilePtr->getTileListthree()[i]->rc.top - cPlayerPtr->getHeight());
			cPlayerPtr->getSensorBottom().isTouch = true;
			cPlayerPtr->getSensorBottom().isJump = false;
			cFieldPtr->breakTilePtr->setBoolTilethree(true);
		}

		if (cFieldPtr->breakTilePtr->getBoolTilethree() == true)
		{
			cFieldPtr->breakTilePtr->breakTileList(cFieldPtr->breakTilePtr->getTileListthree());
		}
	}

	for (int i = 0; i < cFieldPtr->breakTilePtr->getTileListfour().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorBottom().sensorRc, &cFieldPtr->breakTilePtr->getTileListfour()[i]->rc))
		{
			cPlayerPtr->setGravity(0);
			cPlayerPtr->setRealY(cFieldPtr->breakTilePtr->getTileListfour()[i]->rc.top - cPlayerPtr->getHeight());
			cPlayerPtr->getSensorBottom().isTouch = true;
			cPlayerPtr->getSensorBottom().isJump = false;
			cFieldPtr->breakTilePtr->setBoolTilefour(true);
		}

		if (cFieldPtr->breakTilePtr->getBoolTilefour() == true)
		{
			cFieldPtr->breakTilePtr->breakTileList(cFieldPtr->breakTilePtr->getTileListfour());
		}
	}

	for (int i = 0; i < cFieldPtr->breakTilePtr->getTileListfive().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorBottom().sensorRc, &cFieldPtr->breakTilePtr->getTileListfive()[i]->rc))
		{
			cPlayerPtr->setGravity(0);
			cPlayerPtr->setRealY(cFieldPtr->breakTilePtr->getTileListfive()[i]->rc.top - cPlayerPtr->getHeight());
			cPlayerPtr->getSensorBottom().isTouch = true;
			cPlayerPtr->getSensorBottom().isJump = false;
			cFieldPtr->breakTilePtr->setBoolTilefive(true);
		}

		if (cFieldPtr->breakTilePtr->getBoolTilefive() == true)
		{
			cFieldPtr->breakTilePtr->breakTileList(cFieldPtr->breakTilePtr->getTileListfive());
		}
	}
}

void CollisionClass::playerBreakTileBossStage()
{
	for (int i = 0; i < cFieldPtr->breakTilePtr->getTileListBossone().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->breakTilePtr->getTileListBossone()[i]->rc))
		{
			cPlayerPtr->setGravity(0);
			cPlayerPtr->getSensorBottom().isTouch = true;
			cPlayerPtr->getSensorBottom().isJump = false;
			cFieldPtr->breakTilePtr->setBoolTileBossone(true);
		}

		if (cFieldPtr->breakTilePtr->getBoolTileBossone() == true)
		{
			cFieldPtr->breakTilePtr->breakTileList(cFieldPtr->breakTilePtr->getTileListBossone());
		}
	}


	for (int i = 0; i < cFieldPtr->breakTilePtr->getTileListBosstwo().size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->breakTilePtr->getTileListBosstwo()[i]->rc))
		{
			cPlayerPtr->setGravity(0);
			cPlayerPtr->getSensorBottom().isTouch = true;
			cPlayerPtr->getSensorBottom().isJump = false;
			cFieldPtr->breakTilePtr->setBoolTileBosstwo(true);
		}

		if (cFieldPtr->breakTilePtr->getBoolTileBosstwo() == true)
		{
			cFieldPtr->breakTilePtr->breakTileList(cFieldPtr->breakTilePtr->getTileListBosstwo());
		}
	}
}

//플레이어가 펫을 발견
void CollisionClass::playerFindPets(int _wherePet)
{
	wherePet = _wherePet;

	for (int i = 0; i < cPetsPtrV->size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cPetsPtrV)[i]->getPetRc()) && (*cPetsPtrV)[i]->getIsPetFind() == false)
		{
			SOUNDMANAGER->play("구출", TXTDATA.refSFXSound());
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

		vector<string> tempVec;
		char tempStr[255];

		SOUNDMANAGER->play("클리어", TXTDATA.refSFXSound());
		tempVec.push_back(_itoa(TXTDATA.getCurrentPipData()->pipMaxHP, tempStr, 10));
		tempVec.push_back(_itoa(TXTDATA.getCurrentPipData()->pipRescued, tempStr, 10));
		tempVec.push_back(_itoa(TXTDATA.getCurrentPipData()->pipMoney, tempStr, 10));
		tempVec.push_back(_itoa(TXTDATA.getCurrentPipData()->pipCinematic, tempStr, 10));
		tempVec.push_back(_itoa(TXTDATA.getCurrentPipData()->isFindSealS1, tempStr, 10));
		tempVec.push_back(_itoa(TXTDATA.getCurrentPipData()->isFindBatS1, tempStr, 10));
		tempVec.push_back(_itoa(TXTDATA.getCurrentPipData()->isFindSharkS1, tempStr, 10));
		tempVec.push_back(_itoa(TXTDATA.getCurrentPipData()->isFindSealB, tempStr, 10));
		tempVec.push_back(_itoa(TXTDATA.getCurrentPipData()->isFindBatB, tempStr, 10));
		tempVec.push_back(_itoa(TXTDATA.getCurrentPipData()->isFindSharkB, tempStr, 10));
		tempVec.push_back(TXTDATA.getCurrentPipData()->firstItem);
		tempVec.push_back(TXTDATA.getCurrentPipData()->secondItem);
		tempVec.push_back(TXTDATA.getCurrentPipData()->thirdItem);

		TXTDATA.txtSave(TXTDATA.getWhichfile(), tempVec);

		SOUNDMANAGER->pause("스테이지");
		SCENEMANAGER->loadScene("WorldMap");
	}
}

//플레이어가 세이브 포인트를 지남
void CollisionClass::playerSavePoint()
{
	if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cSavePointPtr->getSavePointRc()))
	{
		if (cSavePointPtr->getIsSave() == false)
		{
			SOUNDMANAGER->play("세이브", TXTDATA.refSFXSound());
			cPlayerPtr->setPipHp(TXTDATA.getCurrentPipData()->pipMaxHP);
		}
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
			if(!SOUNDMANAGER->isPlaySound("상자깡")) SOUNDMANAGER->play("상자깡", TXTDATA.refSFXSound());
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
			if ((*cTreasureBoxPtrV)[i]->getJewels()[j].isJewelGet == false && (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cTreasureBoxPtrV)[i]->getJewels()[j].jewelRc))&& (*cTreasureBoxPtrV)[i]->getJewels()[j].blockCollect>30)
			{
				(*cTreasureBoxPtrV)[i]->getJewels()[j].isJewelGet = true;
			}

			if (((*cTreasureBoxPtrV)[i]->getJewels()[j].jewelX > 900 + CAMERA.getCRc().left && (*cTreasureBoxPtrV)[i]->getJewels()[j].jewelY < 100 + CAMERA.getCRc().top && (*cTreasureBoxPtrV)[i]->getJewels()[j].jewelVisible == true))
			{
				(*cTreasureBoxPtrV)[i]->getJewels()[j].jewelVisible = false;
				TXTDATA.getCurrentPipData()->pipMoney += 5;
				SOUNDMANAGER->play("보석획득", TXTDATA.refSFXSound());
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