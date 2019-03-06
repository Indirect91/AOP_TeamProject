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

	enemyRc = RectMakeCenter(enemyX - CAMERA.getCRc().left, enemyY - CAMERA.getCRc().top, 47, 66);

}
//=============����=============
void flyOctopus::render(void)
{
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), enemyRc);
	}
	enemyImage->frameRender(getMemDC(), enemyRc.left, enemyRc.top, frameX, frameY);

}
#pragma endregion ���ٴϴ� ����

//===================================
//	## ���ٴϴ� ���� enemy ##
//===================================
#pragma region ���ٴϴ� ����
//=============�ʱ�ȭ=============
HRESULT crawlBug::init(void)
{
	enemyImage = IMAGEMANAGER->findImage("enemy-���ٴϴ� ����");

	enemyX = 0;
	enemyY = 0;
	enemySpeed = 1.f;
	isRight = false;
	isDie = false;

	imgCount = 0;
	frameX = 0;
	frameY = 0;

	scaleLeftX = 0;
	scaleRightX = 0;

	return S_OK;
}
//=============����=============
void crawlBug::release(void)
{
}
//=============������Ʈ=============
void crawlBug::update(void)
{
	//�¿� �̵�
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

	enemyRc = RectMakeCenter(enemyX - CAMERA.getCRc().left, enemyY - CAMERA.getCRc().top, 47, 24);

}
//=============����=============
void crawlBug::render(void)
{
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), enemyRc);
	}

	enemyImage->frameRender(getMemDC(), enemyRc.left, enemyRc.top, frameX, frameY);

}

#pragma endregion ���ٴϴ� ����

//===================================
//	## ���ƴٴϴ� ũ����Ż enemy ##
//===================================
#pragma region ���ƴٴϴ� ũ����Ż
//=============�ʱ�ȭ=============
HRESULT flyCrystal::init(void)
{
	enemyImage = IMAGEMANAGER->findImage("enemy-���ٴϴ� ũ����Ż");

	enemyX = 0;
	enemyY = 0;
	enemySpeed = 1.f;
	isRight = false;
	isDie = false;

	imgCount = 0;
	frameX = 0;
	frameY = 0;
	stayCount;

	scaleLeftX = 0;
	scaleRightX = 0;

	return S_OK;
}
//=============����=============
void flyCrystal::release(void)
{
}
//=============������Ʈ=============
void flyCrystal::update(void)
{
	//�¿� �̵�
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
		stayCount = 0;

	}
	else if (enemyX > scaleRightX)
	{
		isRight = false;
		stayCount = 0;

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

	enemyRc = RectMakeCenter(enemyX - CAMERA.getCRc().left, enemyY - CAMERA.getCRc().top, 90, 83);
}
//=============����=============
void flyCrystal::render(void)
{
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), enemyRc);
	}

	enemyImage->frameRender(getMemDC(), enemyRc.left, enemyRc.top, frameX, frameY);
}

#pragma endregion ���ƴٴϴ� ũ����Ż