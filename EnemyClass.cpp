#include "stdafx.h"
#include "EnemyClass.h"

//===================================
//	## ���ٴϴ� ���� enemy ##
//===================================
#pragma region ���ٴϴ� ����
//=============�ʱ�ȭ=============
HRESULT flyOctopus::init(void)
{
	enemyImage = IMAGEMANAGER->findImage("enemy-���ٴϴ� ����");

	enemyX = 0;
	enemyY = 0;
	enemySpeed = 0;
	isDie = false;
	reviveCount = 0;

	imgCount = 0;
	frameX = 0;
	frameY = 0;

	return S_OK;
}
//=============����=============
void flyOctopus::release(void)
{
}
//=============������Ʈ=============
void flyOctopus::update(void)
{
	//�׾����� �ٽ� �ǻ�Ƴ���
	if (isDie == true)
	{
		reviveCount++;

		if (reviveCount % 180 == 0)
		{
			enemySpeed = 0;
			reviveCount = 0;

			imgCount = 0;
			frameX = 0;
			frameY = 0;

			isDie = false;
		}
	}

	//�̹��� ������
	imgCount++;
	if (imgCount % 5 == 0)
	{
		frameX++;
		if (frameX > 19)
		{
			frameX = 0;
		}
		imgCount = 0;
	}

	enemyRc = RectMakeCenter(enemyX, enemyY, 47, 66);

}
//=============����=============
void flyOctopus::render(void)
{
	//��Ʈ Ȯ�ο� ���Ű
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), RelativeCameraRect(enemyRc));
	}

	//�׾����� �������� ���̰�
	if (isDie == false)
	{
		enemyImage->frameRender(getMemDC(), enemyRc.left - CAMERA.getCRc().left, enemyRc.top - CAMERA.getCRc().top, frameX, frameY);
	}

}
#pragma endregion ���ٴϴ� ����

//===================================
//	## ���ٴϴ� ���� enemy ##
//===================================
#pragma region ���ٴϴ� ����
//=============�ʱ�ȭ=============
HRESULT crawlBug::init(float _x, float _y)
{
	enemyImage = IMAGEMANAGER->findImage("enemy-���ٴϴ� ����");

	saveX = _x;
	saveY = _y;
	enemyX = saveX;
	enemyY = saveY;
	enemySpeed = 1.f;
	isRight = true;
	isDie = false;
	reviveCount = 0;
	isRevive = false;

	imgCount = 0;
	frameX = 0;
	frameY = 0;

	scaleLeftX = 0;
	scaleRightX = 0;

	dieCount = 1.f;

	return S_OK;
}
//=============����=============
void crawlBug::release(void)
{
}
//=============������Ʈ=============
void crawlBug::update(void)
{
	//�׾����� �ٽ� �ǻ�Ƴ���
	if (isDie == true)
	{
		dieCount -= 0.1f;
		if (dieCount < 0)
		{
			dieCount = 0;
		}

		reviveCount++;
		if (reviveCount % 180 == 0)
		{
			enemyX = saveX;
			enemyY = saveY;

			reviveCount = 0;

			imgCount = 0;
			frameX = 0;
			frameY = 0;

			isRevive = true;
			isDie = false;
		}
	}
	else
	{
		//dieCount = 1.f;

		dieCount += 0.1f;
		if (dieCount > 1.f)
		{
			dieCount = 1.f;
		}
	}

	if (isRevive == true)
	{
		reviveCount++;

		if (reviveCount % 60 == 0)
		{
			isRevive = false;
		}
	}

	//�¿� �̵�
	if (isRevive == false)
	{
		if (isRight == true)
		{
			enemyX += enemySpeed;
			frameY = 0;
		}
		else if (isRight == false)
		{
			enemyX -= enemySpeed;
			frameY = 1;
		}

		if (enemyX < scaleLeftX)
		{
			isRight = true;
		}
		else if (enemyX > scaleRightX)
		{
			isRight = false;
		}
	}

	//�̹��� ������
	imgCount++;
	if (imgCount % 5 == 0)
	{
		frameX++;
		if (frameX > 19)
		{
			frameX = 0;
		}
		imgCount = 0;
	}

	enemyRc = RectMakeCenter(enemyX, enemyY, 47, 24);

}
//=============����=============
void crawlBug::render(void)
{
	//��Ʈ Ȯ�ο� ���Ű
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), RelativeCameraRect(enemyRc));
	}

	//�׾����� �������� ���̰�
	enemyImage->stretchFrameRender(getMemDC(), enemyRc.left - CAMERA.getCRc().left, enemyRc.top - CAMERA.getCRc().top, frameX, frameY, dieCount);
	//enemyImage->frameRender(getMemDC(), enemyRc.left - CAMERA.getCRc().left, enemyRc.top - CAMERA.getCRc().top, frameX, frameY);
	
}

#pragma endregion ���ٴϴ� ����

//===================================
//	## ���ƴٴϴ� ũ����Ż enemy ##
//===================================
#pragma region ���ƴٴϴ� ũ����Ż
//=============�ʱ�ȭ=============
HRESULT flyCrystal::init(float _x, float _y)
{
	enemyImage = IMAGEMANAGER->findImage("enemy-���ٴϴ� ũ����Ż");

	saveX = _x;
	saveY = _y;
	enemyX = saveX;
	enemyY = saveY;
	enemySpeed = 1.f;
	isRight = true;
	isDie = false;
	reviveCount = 0;
	isRevive = false;

	imgCount = 0;
	frameX = 0;
	frameY = 0;

	scaleLeftX = 0;
	scaleRightX = 0;

	dieAlpha = 225;

	return S_OK;
}
//=============����=============
void flyCrystal::release(void)
{
}
//=============������Ʈ=============
void flyCrystal::update(void)
{
	//�׾����� �ٽ� �ǻ�Ƴ���
	if (isDie == true)
	{
		reviveCount++;

		if (reviveCount < 61)
		{
			if (reviveCount % 5 == 0)
			{
				dieAlpha += 125;
			}
		}
		else
		{
			dieAlpha = 0;
		}
		
		if (reviveCount % 180 == 0)
		{
			enemyX = saveX;
			enemyY = saveY;

			imgCount = 0;
			frameX = 0;
			frameY = 0;
			dieAlpha = 225;

			reviveCount = 0;

			isRevive = true;
			isDie = false;
		}
	}

	if (isRevive == true)
	{
		reviveCount++;

		if (reviveCount % 60 == 0)
		{
			reviveCount = 0;
			isRevive = false;
		}
	}

	//�¿� �̵�
	if (isRevive == false)
	{
		if (scaleLeftX != scaleRightX)
		{
			if (isRight == true)
			{
				enemyX += enemySpeed;
				frameY = 0;
			}
			else if (isRight == false)
			{
				enemyX -= enemySpeed;
				frameY = 1;
			}

			if (enemyX < scaleLeftX)
			{
				isRight = true;
			}
			else if (enemyX > scaleRightX)
			{
				isRight = false;
			}
		}
	}
	
	//�̹��� ������
	imgCount++;
	if (imgCount % 5 == 0)
	{
		frameX++;
		if (frameX > 12)
		{
			frameX = 0;
		}
		imgCount = 0;
	}

	enemyRc = RectMakeCenter(enemyX, enemyY, 90, 83);
}
//=============����=============
void flyCrystal::render(void)
{
	//��Ʈ Ȯ�ο� ���Ű
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), RelativeCameraRect(enemyRc));
	}

	//�׾����� �������� ���̰�
	enemyImage->alphaFrameRender(getMemDC(), enemyRc.left - CAMERA.getCRc().left, enemyRc.top - CAMERA.getCRc().top, frameX, frameY, dieAlpha);
	
}

#pragma endregion ���ƴٴϴ� ũ����Ż