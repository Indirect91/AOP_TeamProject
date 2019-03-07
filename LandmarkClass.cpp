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
	//if (KEYMANAGER->isStayKeyDown('B'))
	//{
	//	isSave = true;
	//	isFire = true;
	//}

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
	//Ȯ�ο� ���Ű
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), RelativeCameraRect(savePointRc));
		Rectangle(getMemDC(), RelativeCameraRect(savePointFireRc));
	}

	//���̺� ����Ʈ
	savePointRc = RectMakeCenter(savePX, savePY, 30, 126);
	savePointImg->frameRender(getMemDC(), savePointRc.left - CAMERA.getCRc().left, savePointRc.top - CAMERA.getCRc().top, frameX1, 0);

	//���̺� ����Ʈ�� �浹������ ������ �Ҳ�
	if (isFire == true)
	{
		savePointFireRc = RectMakeCenter(savePX, savePY - 90, 50, 105);
		savePointFireImg->frameRender(getMemDC(), savePointFireRc.left - CAMERA.getCRc().left, savePointFireRc.top - CAMERA.getCRc().top, frameX2, 0);
	}
}

//===================================
//	## �������� ##
//===================================
//=============�ʱ�ȭ=============
HRESULT treasureBox::init(float _x, float _y, bool _isRight, string _collisionStage)
{
	//��������
	treasureBoxImg = IMAGEMANAGER->findImage("��������");

	isOpen = false;
	isRight = _isRight;

	treasureX = _x;
	treasureY = _y;

	imgCount = 0;
	if (isRight == true)
	{
		frameY = 0;
		frameX = 0;
	}
	else if (isRight == false)
	{
		frameY = 1;
		frameX = 2;
	}

	//����
	collisionStage = _collisionStage;

	jewelNum = rand() % 4 + 3;

	//���� ����ü �ʱ�ȭ �� ���Ϳ� ���
	for (int i = 0; i < jewelNum; i++)
	{
		jewel.jewelImg = IMAGEMANAGER->findImage("����");
		jewel.jewelType = rand() % 13;

		jewel.jewelX = treasureX;
		jewel.jewelY = treasureY - 20;
		jewel.jAngle = rand() % 30 + 75;
		jewel.jGravity = 0;
		jewel.jSpeed = 8;
		jewel.jewelPrice = 1;

		jewel.jewelRc = RectMakeCenter(jewel.jewelX, jewel.jewelY, 16, 16);

		jewelV.push_back(jewel);
	}


	return S_OK;
}
//=============����=============
void treasureBox::release(void)
{
}
//=============������Ʈ=============
void treasureBox::update(void)
{
	//Ȯ���� ���� �ӽ÷� ���� Ű
	//if (KEYMANAGER->isStayKeyDown('N'))
	//{
	//	isOpen = true;
	//}

	if (isOpen == true)
	{
		imgCount++;
		if (imgCount % 5 == 0)
		{
			if (isRight == true)
			{
				frameX++;
				if (frameX > 2)
				{
					frameX = 2;
				}
			}
			else if (isRight == false)
			{
				frameX--;
				if (frameX < 0)
				{
					frameX = 0;
				}
			}
		}
	}

	//���ڸ� �������� ������ Ƣ���
	if (isOpen == true)
	{
		for (int i = 0; i < jewelV.size(); i++)
		{
			jewelV[i].jGravity += 0.25f;
			jewelV[i].jewelX += cosf(jewelV[i].jAngle * PI / 180) * jewelV[i].jSpeed;
			jewelV[i].jewelY += -sinf(jewelV[i].jAngle * PI / 180) * jewelV[i].jSpeed + jewelV[i].jGravity;
		}
	}

	//���� �ȼ� �浹
	for (int i = 0; i < jewelV.size(); i++)
	{
		//�ٴ��浹
		COLORREF colorBottom = GetPixel(IMAGEMANAGER->findImage(collisionStage)->getMemDC(), jewelV[i].jewelX, jewelV[i].jewelRc.bottom);
		int rBottom = GetRValue(colorBottom);
		int gBottom = GetGValue(colorBottom);
		int bBottom = GetBValue(colorBottom);

		if (rBottom == 255 && gBottom == 255 && bBottom == 0)
		{
			jewelV[i].jGravity = 0;
			jewelV[i].jSpeed = 0;
			jewelV[i].jewelY = jewelV[i].jewelRc.bottom - 8;

		}

		//���� �� �浹
		COLORREF colorLeft = GetPixel(IMAGEMANAGER->findImage(collisionStage)->getMemDC(), jewelV[i].jewelRc.left, jewelV[i].jewelY);
		int rLeft = GetRValue(colorLeft);
		int gLeft = GetGValue(colorLeft);
		int bLeft = GetBValue(colorLeft);

		if (rLeft == 0 && gLeft == 255 && bLeft == 0)
		{
			jewelV[i].jewelX = jewelV[i].jewelRc.left + 8;
		}

		//������ �� �浹
		COLORREF colorRight = GetPixel(IMAGEMANAGER->findImage(collisionStage)->getMemDC(), jewelV[i].jewelRc.right, jewelV[i].jewelY);
		int rRight = GetRValue(colorLeft);
		int gRight = GetGValue(colorLeft);
		int bRight = GetBValue(colorLeft);

		if (rRight == 0 && gRight == 0 && bRight == 255)
		{
			jewelV[i].jewelX = jewelV[i].jewelRc.right - 8;
		}

		jewelV[i].jewelRc = RectMakeCenter(jewelV[i].jewelX, jewelV[i].jewelY, 16, 16);

	}

	//�׸���
	treasureBoxRc = RectMakeCenter(treasureX, treasureY, 60, 44);
}
//=============����=============
void treasureBox::render(void)
{
	//��������
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), treasureBoxRc);
	}
	treasureBoxImg->frameRender(getMemDC(), treasureBoxRc.left - CAMERA.getCRc().left, treasureBoxRc.top - CAMERA.getCRc().top, frameX, frameY);

	//����
	if (isOpen == true)
	{
		if (KEYMANAGER->isToggleKey('T'))
		{
			for (int i = 0; i < jewelV.size(); i++)
			{
				Rectangle(getMemDC(), jewelV[i].jewelRc);
			}
		}

		for (int i = 0; i < jewelV.size(); i++)
		{
			jewelV[i].jewelImg->frameRender(getMemDC(), jewelV[i].jewelRc.left - CAMERA.getCRc().left, jewelV[i].jewelRc.top - CAMERA.getCRc().top, jewelV[i].jewelType, 0);
		}
	}
}
