#include "stdafx.h"
#include "LandmarkClass.h"
//===================================
//	## ���̺� ����Ʈ ##
//===================================
//=============�ʱ�ȭ=============
HRESULT savePoint::init(float _x, float _y)
{
	savePointImg = IMAGEMANAGER->findImage("���̺� ����Ʈ");

	savePointFireImg = IMAGEMANAGER->findImage("���̺� ��");

	savePX = _x;
	savePY = _y;

	isSave = false;
	isFire = false;
	frameX1 = frameX2 = 0;

	imgCount = 0;
	return S_OK;
}
//=============����=============
void savePoint::release(void)
{
}
//=============������Ʈ=============
void savePoint::update(void)
{
	//������ Ȯ���� ���� �ӽ÷� ���� Ű
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		isSave = true;
		isFire = true;
	}

	if (isSave == true)
	{
		imgCount++;
		if (imgCount % 5 == 0)
		{
			frameX1++;
			if (frameX1 > 12)
			{
				frameX1 = 1;
			}
		}

		if (isFire == true)
		{
			imgCount++;
			if (imgCount % 5 == 0)
			{
				frameX2++;
				if (frameX2 > 36)
				{
					isFire = false;
				}
			}
		}

	}
}
//=============����=============
void savePoint::render(void)
{
	//���̺� ����Ʈ
	savePointRc = RectMakeCenter(savePX - CAMERA.getCRc().left, savePY - CAMERA.getCRc().top, 30, 126);
	savePointImg->frameRender(getMemDC(), savePointRc.left, savePointRc.top, frameX1, 0);

	//���̺� ����Ʈ�� �浹������ ������ �Ҳ�
	if (isFire == true)
	{
		savePointFireRc = RectMakeCenter(savePX - CAMERA.getCRc().left, savePY - 90 - CAMERA.getCRc().top, 50, 105);
		savePointFireImg->frameRender(getMemDC(), savePointFireRc.left, savePointFireRc.top, frameX2, 0);
	}

	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), savePointRc);
		Rectangle(getMemDC(), savePointFireRc);
	}
}

//===================================
//	## �������� ##
//===================================
//=============�ʱ�ȭ=============
HRESULT treasureBox::init(float _x, float _y, bool _isRight)
{
	treasureBoxImg = IMAGEMANAGER->findImage("��������");
	
	isOpen = false;
	isRight = _isRight;

	treasureX = _x;
	treasureY = _y;

	imgCount = 0;
	frameX = frameY = 0;

	return S_OK;
}
//=============����=============
void treasureBox::release(void)
{
}
//=============������Ʈ=============
void treasureBox::update(void)
{
	if (isRight == true) frameY = 0;
	else if (isRight == false) frameY = 1;

	//Ȯ���� ���� �ӽ÷� ���� Ű
	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		isOpen = true;
	}

	if (isOpen == true)
	{
		imgCount++;
		if (imgCount % 5 == 0)
		{
			frameX++;
			if (frameX > 2)
			{
				frameX = 2;
			}
		}
	}


}
//=============����=============
void treasureBox::render(void)
{
	treasureBoxRc = RectMakeCenter(treasureX, treasureY, 30, 44);
	treasureBoxImg->frameRender(getMemDC(), treasureBoxRc.left, treasureBoxRc.top, frameX, frameY);
}
