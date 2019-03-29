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

//�÷��̾ ���ʹ̸� ����
void CollisionClass::playerStepEnemy()
{
	if (!cPlayerPtr->getInvincible())
	{
		//����� �浹
		for (int i = 0; i < cEnemyMPtr->getEEnemy1V().size(); i++)
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &cEnemyMPtr->getEEnemy1V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy1V()[i]->getIsDie() == false)
			{
				SOUNDMANAGER->play("���ʹ̻��", TXTDATA.refSFXSound());
				//�÷��̾� ����
				cPlayerPtr->setGravity(-5.0f);				//�÷��̾ ���� ������ ����ش�
				if (KEYMANAGER->isStayKeyDown('K'))
				{
					cPlayerPtr->setGravity(-10.0f);		//���� Ű�� ������ �� ���� �ڴ�.
				}
				//enemy����
				cEnemyMPtr->getEEnemy1V()[i]->setIsDie(true);
			}
		}

		//������ �浹
		for (int i = 0; i < cEnemyMPtr->getEEnemy2V().size(); i++)
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &cEnemyMPtr->getEEnemy2V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy2V()[i]->getIsDie() == false)
			{
				SOUNDMANAGER->play("���ʹ̻��", TXTDATA.refSFXSound());
				//�÷��̾� ����
				cPlayerPtr->setGravity(-5.0f);				//�÷��̾ ���� ������ ����ش�
				if (KEYMANAGER->isStayKeyDown('K'))
				{
					cPlayerPtr->setGravity(-12.0f);		//���� Ű�� ������ �� ���� �ڴ�.
				}
				//enemy����
				cEnemyMPtr->getEEnemy2V()[i]->setIsDie(true);
			}

		}

		//ũ����Ż�̶� �浹(Bottom ������ �浹)
		for (int i = 0; i < cEnemyMPtr->getEEnemy3V().size(); i++)
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &cEnemyMPtr->getEEnemy3V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy3V()[i]->getIsDie() == false)
			{
				SOUNDMANAGER->play("��ȭ", TXTDATA.refSFXSound());
				//�÷��̾� ����
				cPlayerPtr->setGravity(-5.0f);				//�÷��̾ ���� ������ ����ش�
				if (KEYMANAGER->isStayKeyDown('K'))
				{
					cPlayerPtr->setGravity(-12.0f);		//���� Ű�� ������ �� ���� �ڴ�.
				}
				cPlayerPtr->setChangeForm(false);		//���� ������ ��� ũ����Ż�� ������ �ΰ� ������ ����!!

				//enemy����
				cEnemyMPtr->getEEnemy3V()[i]->setIsDie(true);
			}
		}

		//�����̶� �浹
		for (int i = 0; i < cEnemyMPtr->getEEnemy4V().size(); i++)
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getSensorRcBottom(), &cEnemyMPtr->getEEnemy4V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy4V()[i]->getIsDie() == false)
			{
				SOUNDMANAGER->play("���ʹ̻��", TXTDATA.refSFXSound());
				//�÷��̾� ����
				cPlayerPtr->setGravity(-5.0f);

				//enemy����
				cEnemyMPtr->getEEnemy4V()[i]->setIsDie(true);
			}
		}
	}
}

//�÷��̾ ���ʹ̶� �ε���
void CollisionClass::playerCrashedEnemy()
{
	//����� �浹
	for (int i = 0; i < cEnemyMPtr->getEEnemy1V().size(); i++)
	{
		if (!cPlayerPtr->getInvincible())
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEEnemy1V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy1V()[i]->getIsDie() == false)
			{
				SOUNDMANAGER->play("�÷��̾��ǰ�", TXTDATA.refSFXSound());
				cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
				//�÷��̾� ����
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
				//enemy����
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

	//������ �浹
	for (int i = 0; i < cEnemyMPtr->getEEnemy2V().size(); i++)
	{
		if (!cPlayerPtr->getInvincible())		//false�϶��� �浹
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEEnemy2V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy2V()[i]->getIsDie() == false)
			{
				SOUNDMANAGER->play("�÷��̾��ǰ�", TXTDATA.refSFXSound());
				cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
				//�÷��̾� ����
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

				//enemy����
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
	//ũ����Ż�̶� �浹
	for (int i = 0; i < cEnemyMPtr->getEEnemy3V().size(); i++)
	{

		if (!cPlayerPtr->getInvincible())
		{
			cPlayerPtr->setTestCount(0);
			cPlayerPtr->setInvincibleCountAlpha(0);
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEEnemy3V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy3V()[i]->getIsDie() == false)
			{
				SOUNDMANAGER->play("�÷��̾��ǰ�", TXTDATA.refSFXSound());
				cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
				//�÷��̾� ����
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
				//enemy����
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

	//�����̶� �浹
	for (int i = 0; i < cEnemyMPtr->getEEnemy4V().size(); i++)
	{
		if (!cPlayerPtr->getInvincible())
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEEnemy4V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy4V()[i]->getIsDie() == false)
			{
				SOUNDMANAGER->play("�÷��̾��ǰ�", TXTDATA.refSFXSound());
				cPlayerPtr->setPipHp(cPlayerPtr->getPipHp() - 1);
				//�÷��̾� ����
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
				//enemy����
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

//�÷��̾ �ֳʹ̸� ����
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
				SOUNDMANAGER->play("���ʹ̻��", TXTDATA.refSFXSound());
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
				SOUNDMANAGER->play("���ʹ̻��", TXTDATA.refSFXSound());
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
				SOUNDMANAGER->play("���ʹ̻��", TXTDATA.refSFXSound());
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
				SOUNDMANAGER->play("���ʹ̻��", TXTDATA.refSFXSound());
			}
			//exit(0);
		}
	}
}

//�÷��̾�� ��ֹ� �浹
void CollisionClass::playerDamegeThorn()
{
	if (!cPlayerPtr->getInvincible())
	{
		//1�������� ���ö� �浹
		for (int i = 0; i < cFieldPtr->thornPtr->getThornStage1().size(); i++)
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->thornPtr->getThornStage1()[i]))
			{
				//�÷��̾� ����
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
		//���� �������� ���ö� �浹
		for (int i = 0; i < cFieldPtr->thornPtr->getThornBossStage().size(); i++)
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->thornPtr->getThornBossStage()[i]))
			{
				//�÷��̾� ����
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

//�÷��̾ �����Ҷ� Ÿ�ϰ� �浹
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

//�÷��̾�� ������ Ÿ�� �浹
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

//�÷��̾��� ���� ����Ʈ�� �ֳʹ� �浹
void CollisionClass::playerChangeEnemyCrash()
{
	//����� �浹
	if (cPlayerPtr->getIsBomb())
	{
		for (int i = 0; i < cEnemyMPtr->getEEnemy1V().size(); i++)
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getEnemyCrashRc(), &cEnemyMPtr->getEEnemy1V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy1V()[i]->getIsDie() == false)
			{
				//�÷��̾� ����

				//enemy����
				cEnemyMPtr->getEEnemy1V()[i]->setIsDie(true);
			}
		}

		//������ �浹
		for (int i = 0; i < cEnemyMPtr->getEEnemy2V().size(); i++)
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getEnemyCrashRc(), &cEnemyMPtr->getEEnemy2V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy2V()[i]->getIsDie() == false)
			{
				//�÷��̾� ����

				//enemy����
				cEnemyMPtr->getEEnemy2V()[i]->setIsDie(true);
			}
		}

		//ũ����Ż�̶� �浹
		for (int i = 0; i < cEnemyMPtr->getEEnemy3V().size(); i++)
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getEnemyCrashRc(), &cEnemyMPtr->getEEnemy3V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy3V()[i]->getIsDie() == false)
			{
				//�÷��̾� ����

				//enemy����
				cEnemyMPtr->getEEnemy3V()[i]->setIsDie(true);
			}
		}

		//�����̶� �浹
		for (int i = 0; i < cEnemyMPtr->getEEnemy4V().size(); i++)
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getEnemyCrashRc(), &cEnemyMPtr->getEEnemy4V()[i]->getEnemyRc()) && cEnemyMPtr->getEEnemy4V()[i]->getIsDie() == false)
			{
				//�÷��̾� ����

				//enemy����
				cEnemyMPtr->getEEnemy4V()[i]->setIsDie(true);
			}
		}
	}
}

//�÷��̾�� ������ �浹
void CollisionClass::playerJumpJump()
{
	if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->uniPtr->getJumpRCone())
		|| IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->uniPtr->getJumpRCtwo()))
	{
		SOUNDMANAGER->play("������", TXTDATA.refSFXSound());
		//�ΰ� �� ����
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
		//���� �� ����
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

//�÷��̾� vs ���� �浹
void CollisionClass::playerBossCollision()
{

}

//�÷��̾ �Ѿ˿� ����
void CollisionClass::playerCrashedEBullet()
{
	if (!cPlayerPtr->getInvincible())
	{
		for (int i = 0; i < cEnemyMPtr->getEBullet().size(); i++)
		{
			if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cEnemyMPtr->getEBullet()[i]->getVBullet()[0].rc) && cEnemyMPtr->getEBullet()[i]->getVBullet()[0].fire == true)
			{
				SOUNDMANAGER->play("�÷��̾��ǰ�", TXTDATA.refSFXSound());
				//�÷��̾� ����
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

				//�Ѿ� ����
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
					SOUNDMANAGER->play("�÷��̾��ǰ�", TXTDATA.refSFXSound());
					//�÷��̾� ����
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

					//�Ѿ� ����
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}

			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollLeftPtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollLeftPtr()->getVBullet()[i].rc))
				{
					SOUNDMANAGER->play("�÷��̾��ǰ�", TXTDATA.refSFXSound());
					//�÷��̾� ����
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

					//�Ѿ� ����
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}

			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollRightPtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollRightPtr()->getVBullet()[i].rc))
				{
					SOUNDMANAGER->play("�÷��̾��ǰ�", TXTDATA.refSFXSound());
					//�÷��̾� ����
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

					//�Ѿ� ����
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}

			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollLeftTwoPtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollLeftTwoPtr()->getVBullet()[i].rc))
				{
					SOUNDMANAGER->play("�÷��̾��ǰ�", TXTDATA.refSFXSound());
					//�÷��̾� ����
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

					//�Ѿ� ����
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}

			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollRightTwoPtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollRightTwoPtr()->getVBullet()[i].rc))
				{
					SOUNDMANAGER->play("�÷��̾��ǰ�", TXTDATA.refSFXSound());
					//�÷��̾� ����
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

					//�Ѿ� ����
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}

			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollUpOnePtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollUpOnePtr()->getVBullet()[i].rc)
					&& cFieldPtr->flowerPtr->getFireBollUpOnePtr()->getVBullet()[i].fire == true)
				{
					SOUNDMANAGER->play("�÷��̾��ǰ�", TXTDATA.refSFXSound());
					//�÷��̾� ����
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

					//�Ѿ� ����
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}

			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollUpTwoPtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollUpTwoPtr()->getVBullet()[i].rc)
					&& cFieldPtr->flowerPtr->getFireBollUpTwoPtr()->getVBullet()[i].fire == true)
				{
					SOUNDMANAGER->play("�÷��̾��ǰ�", TXTDATA.refSFXSound());
					//�÷��̾� ����
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

					//�Ѿ� ����
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}

			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollUpThreePtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollUpThreePtr()->getVBullet()[i].rc)
					&& cFieldPtr->flowerPtr->getFireBollUpThreePtr()->getVBullet()[i].fire == true)
				{
					SOUNDMANAGER->play("�÷��̾��ǰ�", TXTDATA.refSFXSound());
					//�÷��̾� ����
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

					//�Ѿ� ����
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}

			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollDownOnePtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollDownOnePtr()->getVBullet()[i].rc)
					&& cFieldPtr->flowerPtr->getFireBollDownOnePtr()->getVBullet()[i].fire == true)
				{
					SOUNDMANAGER->play("�÷��̾��ǰ�", TXTDATA.refSFXSound());
					//�÷��̾� ����
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

					//�Ѿ� ����
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}

			for (int i = 0; i < cFieldPtr->flowerPtr->getFireBollDownTwoPtr()->getVBullet().size(); i++)
			{
				if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cFieldPtr->flowerPtr->getFireBollDownTwoPtr()->getVBullet()[i].rc)
					&& cFieldPtr->flowerPtr->getFireBollDownTwoPtr()->getVBullet()[i].fire == true)
				{
					SOUNDMANAGER->play("�÷��̾��ǰ�", TXTDATA.refSFXSound());
					//�÷��̾� ����
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

					//�Ѿ� ����
					//cFieldPtr->flowerPtr->flowerPtr->getFireBollPtr()->getVBullet()[i].fire = false;
					break;
				}
			}
		}
	}
}
//�Ѿ��� ���� ����
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

//�÷��̾ ���� �߰�
void CollisionClass::playerFindPets(int _wherePet)
{
	wherePet = _wherePet;

	for (int i = 0; i < cPetsPtrV->size(); i++)
	{
		if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cPetsPtrV)[i]->getPetRc()) && (*cPetsPtrV)[i]->getIsPetFind() == false)
		{
			SOUNDMANAGER->play("����", TXTDATA.refSFXSound());
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

		vector<string> tempVec;
		char tempStr[255];

		SOUNDMANAGER->play("Ŭ����", TXTDATA.refSFXSound());
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

		SOUNDMANAGER->pause("��������");
		SCENEMANAGER->loadScene("WorldMap");
	}
}

//�÷��̾ ���̺� ����Ʈ�� ����
void CollisionClass::playerSavePoint()
{
	if (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &cSavePointPtr->getSavePointRc()))
	{
		if (cSavePointPtr->getIsSave() == false)
		{
			SOUNDMANAGER->play("���̺�", TXTDATA.refSFXSound());
			cPlayerPtr->setPipHp(TXTDATA.getCurrentPipData()->pipMaxHP);
		}
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
			if(!SOUNDMANAGER->isPlaySound("���ڱ�")) SOUNDMANAGER->play("���ڱ�", TXTDATA.refSFXSound());
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
			if ((*cTreasureBoxPtrV)[i]->getJewels()[j].isJewelGet == false && (IntersectRect(&cEmpty, &cPlayerPtr->getRect(), &(*cTreasureBoxPtrV)[i]->getJewels()[j].jewelRc))&& (*cTreasureBoxPtrV)[i]->getJewels()[j].blockCollect>30)
			{
				(*cTreasureBoxPtrV)[i]->getJewels()[j].isJewelGet = true;
			}

			if (((*cTreasureBoxPtrV)[i]->getJewels()[j].jewelX > 900 + CAMERA.getCRc().left && (*cTreasureBoxPtrV)[i]->getJewels()[j].jewelY < 100 + CAMERA.getCRc().top && (*cTreasureBoxPtrV)[i]->getJewels()[j].jewelVisible == true))
			{
				(*cTreasureBoxPtrV)[i]->getJewels()[j].jewelVisible = false;
				TXTDATA.getCurrentPipData()->pipMoney += 5;
				SOUNDMANAGER->play("����ȹ��", TXTDATA.refSFXSound());
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