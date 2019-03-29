#include "stdafx.h"
#include "BossClass.h"
#include "PlayerClass.h"

//=============�ʱ�ȭ=============
HRESULT BossClass::init(void)
{
	bossIdleImg = IMAGEMANAGER->findImage("boss-���");
	bossShoutImg = IMAGEMANAGER->findImage("boss-����");
	bossChangeImg = IMAGEMANAGER->findImage("boss-����");
	bossWalkImg = IMAGEMANAGER->findImage("boss-�ȱ�");
	bossRunImg = IMAGEMANAGER->findImage("boss-�޸���");
	bossAttack1Img = IMAGEMANAGER->findImage("boss-����1");
	bossAttack2Img = IMAGEMANAGER->findImage("boss-����2");
	bossAttackedImg = IMAGEMANAGER->findImage("boss-�ǰ�");
	bossDieImg = IMAGEMANAGER->findImage("boss-����");

	bossSpeed = 1.f;
	bossGravity = 0;
	bossX = 9200;
	bossY = 2219;
	bossHp = 3;

	bossState = idle;
	isMeet = false;
	isStart = false;
	isRight = false;
	isDie = false;

	attCount = 0;
	imgCount = 0;
	frameX = 0;
	frameY = 0;
	alphaFrame = 255;

	bEmpty = { 0 };

	return S_OK;
}
//=============����=============
void BossClass::release(void)
{
}
//=============������Ʈ=============
void BossClass::update(void)
{
	//�÷��̾ ���������� �����ϰ� �Ұ���
	if (bPlayerPtr->getRect().bottom > 2285 && isStart == false && isMeet == false)
	{
		frameX = 0;
		bossState = change;
		isMeet = true;
	}

	//��������
	if (isStart == true)
	{
		//������ �÷��̾ ���� �̵�
		if (bossX > bPlayerPtr->getX())
		{
			if (bossState != attack1 && bossState != attacked) isRight = false;
			if (bossRc.left > 8369 && bossState != attack1 && bossState != attacked) bossX -= bossSpeed;
		}
		else if (bossX < bPlayerPtr->getX())
		{
			if (bossState != attack1 && bossState != attacked) isRight = true;
			if (bossRc.right < 9443 && bossState != attack1 && bossState != attacked) bossX += bossSpeed;
		}
	}

	//������ �������
	if (IntersectRect(&bEmpty, &bPlayerPtr->getSensorRcBottom(), &bossRc) && bossState != attacked && bossState != die && bossState != end)
	{
		//�÷��̾� ����
		bPlayerPtr->setGravity(-6.f);

		//��������
		bossHp -= 1;
		if (bossHp > 0)
		{
			//ü�¿� ���� �ӵ� �ٸ���
			bossSpeed += 2.f;
			imgCount = 0;
			if (isRight == false) frameX = 0;
			else if (isRight == true) frameX = 3;
			bossState = attacked;
		}
	}

	//���� ü���� 0
	if (bossHp == 0 && bossState != die && bossState != end)
	{
		if (isRight == false) frameX = 0;
		else if (isRight == true) frameX = 24;
		bossSpeed = 0;
		bossState = die;
	}

	//������ �÷��̾�� �浹�ؼ� ������ ������
	if (IntersectRect(&bEmpty, &bPlayerPtr->getSensorRcLeft(), &bossAttackRc)
		&& bossState != attack1 && bossState != attacked && bossState != die && bossState != end ||
		IntersectRect(&bEmpty, &bPlayerPtr->getSensorRcRight(), &bossAttackRc)
		&& bossState != attack1 && bossState != attacked && bossState != die && bossState != end)
	{
		bPlayerPtr->setPipHp(bPlayerPtr->getPipHp() - 1);
		//�÷��̾� ����
		if (bPlayerPtr->getIsLeft())
		{
			bPlayerPtr->setY(5);
			bPlayerPtr->setGravity(-5.0f);
			bPlayerPtr->setX(75);
		}
		else
		{
			bPlayerPtr->setY(5);
			bPlayerPtr->setGravity(-5.0f);
			bPlayerPtr->setX(-75);
		}
		bPlayerPtr->setInvincibleCount(60);

		//���� ����
		imgCount = 0;
		if (isRight == false) frameX = 0;
		else if (isRight == true) frameX = 6;
		bossState = attack1;
	}





	//���� �ִϸ��̼�
	imgCount++;
	switch (bossState)
	{
		//���
	case BossClass::idle:
		if (imgCount % 7 == 0)
		{
			if (isRight == false)
			{
				frameY = 0;
				frameX++;
				if (frameX > 8) frameX = 0;

			}
		}
		break;
		//����
	case BossClass::shout:
		if (imgCount % 7 == 0)
		{
			if (isRight == false)
			{
				frameY = 0;
				frameX++;
				if (frameX > 6)
				{
					frameX = 0;
					bossState = walk;
					isStart = true;
				}

			}
			else if (isRight == true)
			{
				frameY = 1;
				frameX--;
				if (frameX < 0)
				{
					frameX = 10;
					bossState = walk;
					isStart = true;
				}
			}

		}
		break;
		//����
	case BossClass::change:
		if (imgCount % 7 == 0)
		{
			frameY = 0;
			frameX++;
			if (frameX > 8)
			{
				frameX = 0;
				bossState = attack2;
			}
		}
		break;
		//�ȱ�
	case BossClass::walk:
		if (imgCount % 7 == 0)
		{
			if (isRight == false)
			{
				frameY = 0;
				frameX++;
				if (frameX > 10) frameX = 0;
			}
			else if (isRight == true)
			{
				frameY = 1;
				frameX--;
				if (frameX < 0) frameX = 10;
			}
		}
		break;
		//�޸���
	case BossClass::run:
		if (imgCount % 7 == 0)
		{
			if (isRight == false)
			{
				frameY = 0;
				frameX++;
				if (frameX > 7) frameX = 0;
			}
			else if (isRight == true)
			{
				frameY = 1;
				frameX--;
				if (frameX < 0) frameX = 7;
			}
			break;
		}
		//����1-�ֵθ���
	case BossClass::attack1:
		if (imgCount % 7 == 0)
		{
			if (isRight == false)
			{
				frameY = 0;
				frameX++;
				if (frameX > 6)
				{
					frameX = 0;

					if (bossHp == 1) bossState = run;
					else bossState = walk;
				}
			}
			else if (isRight == true)
			{
				frameY = 1;
				frameX--;
				if (frameX < 0)
				{
					frameX = 6;

					if (bossHp == 1) bossState = run;
					else bossState = walk;
				}
			}
		}
		break;
		//����2-�������
	case BossClass::attack2:
		if (imgCount % 7 == 0)
		{
			frameY = 0;
			frameX++;
			if (frameX > 13)
			{
				frameX = 0;
				if (isStart == false) bossState = shout;
				else bossState = walk;
			}
		}
		break;
		//���ݴ���
	case BossClass::attacked:
		if (imgCount % 7 == 0)
		{
			if (isRight == false)
			{
				frameY = 0;
				frameX++;
				if (frameX > 3)
				{
					frameX = 3;
					alphaFrame += 125;
					attCount++;
					if (attCount % 7 == 0)
					{
						frameX = 0;
						alphaFrame = 255;
						if (bossHp == 1) bossState = run;
						else bossState = walk;
					}
				}
			}
			else if (isRight == true)
			{
				frameY = 1;
				frameX--;
				if (frameX < 0)
				{
					frameX = 0;
					alphaFrame += 125;
					attCount++;
					if (attCount % 12 == 0)
					{
						frameX = 10;
						alphaFrame = 255;
						if (bossHp == 1) bossState = run;
						else bossState = walk;
					}
				}
			}
		}
		break;
		//����
	case BossClass::die:
		if (imgCount % 7 == 0)
		{
			if (isRight == false)
			{
				frameY = 0;
				frameX++;
				if (frameX > 24)
				{
					isDie = true;
					frameX = 24;
				}
			}
			else if (isRight == true)
			{
				frameY = 1;
				frameX--;
				if (frameX < 0)
				{
					isDie = true;
					frameX = 0;
				}
			}
		}
		break;

	case BossClass::end:
		break;
	}


	bossRc = RectMakeCenter(bossX, bossY, 240, 182);
	if (isRight == false) bossAttackRc = RectMakeCenter(bossRc.left - 40, bossY, 80, 166);
	else if (isRight == true) bossAttackRc = RectMakeCenter(bossRc.right + 40, bossY, 80, 166);
}
//=============����=============
void BossClass::render(void)
{
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), RelativeCameraRect(bossRc));
		Rectangle(getMemDC(), RelativeCameraRect(bossAttackRc));
	}

	/*
	240, 182
	��� : 96,92
	���� : 312, 204
	�ȱ� : 258, 210
	���� : 264, 366
	����1 : 510, 228
	����2 : 306,240
	�ǰ� : 246, 210
	���� : 408, 210
	*/

	switch (bossState)
	{
	case BossClass::idle:
		bossIdleImg->frameRender(getMemDC(), bossRc.left + 72 - CAMERA.getCRc().left, bossRc.top + 90 - CAMERA.getCRc().top, frameX, frameY);
		break;

	case BossClass::shout:
		bossShoutImg->frameRender(getMemDC(), bossRc.left - 36 - CAMERA.getCRc().left, bossRc.top - 22 - CAMERA.getCRc().top, frameX, frameY);
		break;

	case BossClass::change:
		bossChangeImg->frameRender(getMemDC(), bossRc.left - 12 - CAMERA.getCRc().left, bossRc.top - 184 - CAMERA.getCRc().top, frameX, frameY);
		break;

	case BossClass::walk:
		bossWalkImg->frameRender(getMemDC(), bossRc.left - 9 - CAMERA.getCRc().left, bossRc.top - 28 - CAMERA.getCRc().top, frameX, frameY);
		break;

	case BossClass::run:
		bossRunImg->frameRender(getMemDC(), bossRc.left - 9 - CAMERA.getCRc().left, bossRc.top - 28 - CAMERA.getCRc().top, frameX, frameY);
		break;

	case BossClass::attack1:
		if (isRight == false) bossAttack1Img->frameRender(getMemDC(), bossAttackRc.left - CAMERA.getCRc().left, bossAttackRc.top - 46 - CAMERA.getCRc().top, frameX, frameY);
		if (isRight == true) bossAttack1Img->frameRender(getMemDC(), bossRc.left - 170 - CAMERA.getCRc().left, bossRc.top - 46 - CAMERA.getCRc().top, frameX, frameY);
		break;

	case BossClass::attack2:
		if (isRight == false) bossAttack2Img->frameRender(getMemDC(), bossAttackRc.left - CAMERA.getCRc().left, bossAttackRc.top - 46 - CAMERA.getCRc().top, frameX, frameY);
		if (isRight == true) bossAttack2Img->frameRender(getMemDC(), bossRc.left - 170 - CAMERA.getCRc().left, bossRc.top - 46 - CAMERA.getCRc().top, frameX, frameY);
		break;

	case BossClass::attacked:
		bossAttackedImg->alphaFrameRender(getMemDC(), bossRc.left - 3 - CAMERA.getCRc().left, bossRc.top - 28 - CAMERA.getCRc().top, frameX, frameY, alphaFrame);
		break;

	case BossClass::die:
		bossDieImg->frameRender(getMemDC(), bossRc.left - 84 - CAMERA.getCRc().left, bossRc.top - 28 - CAMERA.getCRc().top, frameX, frameY);
		break;
	}

	//char strA[124];
	//TextOutInt(getMemDC(), 200, 10, "ü��", bossHp);
	//TextOutInt(getMemDC(), 200, 30, "����", isDie);
}
