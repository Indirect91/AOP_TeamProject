#include "stdafx.h"
#include "BossClass.h"
#include "PlayerClass.h"

//=============�ʱ�ȭ=============
HRESULT BossClass::init(void)
{
	bossIdleImg = IMAGEMANAGER->findImage("boss-���");
	bossMoveImg = IMAGEMANAGER->findImage("boss-�ȱ�");
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
	isStart = false;
	isRight = false;
	isMove = false;
	isAttak = false;

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
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		isStart = true;
		bossState = move;
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
	if (IntersectRect(&bEmpty, &bPlayerPtr->getSensorRcBottom(), &bossRc) && bossState != attacked)
	{
		bossHp -= 1;
		bPlayerPtr->setGravity(-10);
		if (bossHp > 0)
		{
			//ü�¿� ���� �ӵ� �ٸ���
			bossSpeed += 1.5f;
			imgCount = 0;
			if (isRight == false) frameX = 0;
			else if (isRight == true) frameX = 3;
			bossState = attacked;
		}
	}

	//���� ü���� 0
	if (bossHp == 0)
	{
		if (isRight == false) frameX = 0;
		else if (isRight == true) frameX = 24;
		bossSpeed = 0;
		bossState = die;
	}

	//������ �÷��̾�� �浹�ؼ� ������ ������
	if (IntersectRect(&bEmpty, &bPlayerPtr->getRect(), &bossAttackRc)
		&& bossState != attack1 && bossState != attacked && bossState != die)
	{
		imgCount = 0;
		if (isRight == false) frameX = 0;
		else if (isRight == true) frameX = 6;
		bossState = attack1;
	}

	//���� �ִϸ��̼�
	imgCount++;
	switch (bossState)
	{
	case BossClass::idle:
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
		}
		break;

	case BossClass::move:
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
					bossState = move;
				}
			}
			else if (isRight == true)
			{
				frameY = 1;
				frameX--;
				if (frameX < 0)
				{
					frameX = 6;
					bossState = move;
				}
			}
		}
		break;

	case BossClass::attack2:
		if (imgCount % 7 == 0)
		{
			if (isRight == false)
			{
				frameY = 0;
				frameX++;
				if (frameX > 13)
				{
					frameX = 0;
					bossState = move;
				}
			}
			else if (isRight == true)
			{
				frameY = 1;
				frameX--;
				if (frameX < 0)
				{
					frameX = 13;
					bossState = move;
				}
			}
		}
		break;

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
						bossState = move;
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
						bossState = move;
					}
				}
			}
		}
		break;

	case BossClass::die:
		if (imgCount % 7 == 0)
		{
			if (isRight == false)
			{
				frameY = 0;
				frameX++;
				if (frameX > 24)
				{
					frameX = 24;
				}
			}
			else if (isRight == true)
			{
				frameY = 1;
				frameX--;
				if (frameX < 0)
				{
					frameX = 0;
				}
			}
		}
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

	��� : 240, 210
	�ȱ� : 258, 210
	����1 : 510, 228
	����2 : 306,240
	�ǰ� : 246, 210
	���� : 408, 210
	*/
	switch (bossState)
	{
	case BossClass::idle:
		bossIdleImg->frameRender(getMemDC(), bossRc.left - CAMERA.getCRc().left, bossRc.top - 28 - CAMERA.getCRc().top, frameX, frameY);
		break;

	case BossClass::move:
		bossMoveImg->frameRender(getMemDC(), bossRc.left - CAMERA.getCRc().left - 9, bossRc.top - 28 - CAMERA.getCRc().top, frameX, frameY);
		break;

	case BossClass::attack1:
		if (isRight == false) bossAttack1Img->frameRender(getMemDC(), bossAttackRc.left - CAMERA.getCRc().left, bossAttackRc.top - 46 - CAMERA.getCRc().top, frameX, frameY);
		if (isRight == true) bossAttack1Img->frameRender(getMemDC(), bossRc.left - 170 - CAMERA.getCRc().left, bossRc.top - 46 - CAMERA.getCRc().top, frameX, frameY);
		break;

	case BossClass::attack2:
		//if (isRight == false) bossAttack1Img->frameRender(getMemDC(), bossAttackRc.left - CAMERA.getCRc().left, bossAttackRc.top - 46 - CAMERA.getCRc().top, frameX, frameY);
		//if (isRight == true) bossAttack1Img->frameRender(getMemDC(), bossRc.left - 170 - CAMERA.getCRc().left, bossRc.top - 46 - CAMERA.getCRc().top, frameX, frameY);
		break;

	case BossClass::attacked:
		bossAttackedImg->alphaFrameRender(getMemDC(), bossRc.left - 3 - CAMERA.getCRc().left, bossRc.top - 28 - CAMERA.getCRc().top, frameX, frameY, alphaFrame);
		break;

	case BossClass::die:
		bossDieImg->frameRender(getMemDC(), bossRc.left - 84 - CAMERA.getCRc().left, bossRc.top - 28 - CAMERA.getCRc().top, frameX, frameY);
		break;
	}
}
