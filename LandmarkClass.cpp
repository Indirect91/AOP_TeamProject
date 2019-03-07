#include "stdafx.h"
#include "LandmarkClass.h"

//===================================
//	## 세이브 포인트 ##
//===================================
//=============초기화=============
HRESULT savePoint::init(float _x, float _y)
{
	savePointImg = IMAGEMANAGER->findImage("세이브 포인트");

	savePointFireImg = IMAGEMANAGER->findImage("세이브 빛");

	savePX = _x;
	savePY = _y;

	isSave = false;
	isFire = false;
	frameX1 = frameX2 = 0;

	imgCount = 0;

	return S_OK;
}
//=============해제=============
void savePoint::release(void)
{
}
//=============업데이트=============
void savePoint::update(void)
{
	//프레임 확인을 위한 임시로 넣은 키
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
//=============렌더=============
void savePoint::render(void)
{
	//확인용 토글키
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), RelativeCameraRect(savePointRc));
		Rectangle(getMemDC(), RelativeCameraRect(savePointFireRc));
	}

	//세이브 포인트
	savePointRc = RectMakeCenter(savePX, savePY, 30, 126);
	savePointImg->frameRender(getMemDC(), savePointRc.left - CAMERA.getCRc().left, savePointRc.top - CAMERA.getCRc().top, frameX1, 0);

	//세이브 포인트랑 충돌했을때 나오는 불꽃
	if (isFire == true)
	{
		savePointFireRc = RectMakeCenter(savePX, savePY - 90, 50, 105);
		savePointFireImg->frameRender(getMemDC(), savePointFireRc.left - CAMERA.getCRc().left, savePointFireRc.top - CAMERA.getCRc().top, frameX2, 0);
	}
}

//===================================
//	## 보물상자 ##
//===================================
//=============초기화=============
HRESULT treasureBox::init(float _x, float _y, bool _isRight, string _collisionStage)
{
	//보물상자
	treasureBoxImg = IMAGEMANAGER->findImage("보물상자");

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

	//보석
	collisionStage = _collisionStage;

	jewelNum = rand() % 4 + 3;

	//보석 구조체 초기화 및 벡터에 담기
	for (int i = 0; i < jewelNum; i++)
	{
		jewel.jewelImg = IMAGEMANAGER->findImage("보석");
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
//=============해제=============
void treasureBox::release(void)
{
}
//=============업데이트=============
void treasureBox::update(void)
{
	//확인을 위해 임시로 넣은 키
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

	//상자를 열었을때 보석이 튀어나옴
	if (isOpen == true)
	{
		for (int i = 0; i < jewelV.size(); i++)
		{
			jewelV[i].jGravity += 0.25f;
			jewelV[i].jewelX += cosf(jewelV[i].jAngle * PI / 180) * jewelV[i].jSpeed;
			jewelV[i].jewelY += -sinf(jewelV[i].jAngle * PI / 180) * jewelV[i].jSpeed + jewelV[i].jGravity;
		}
	}

	//보석 픽셀 충돌
	for (int i = 0; i < jewelV.size(); i++)
	{
		//바닥충돌
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

		//왼쪽 벽 충돌
		COLORREF colorLeft = GetPixel(IMAGEMANAGER->findImage(collisionStage)->getMemDC(), jewelV[i].jewelRc.left, jewelV[i].jewelY);
		int rLeft = GetRValue(colorLeft);
		int gLeft = GetGValue(colorLeft);
		int bLeft = GetBValue(colorLeft);

		if (rLeft == 0 && gLeft == 255 && bLeft == 0)
		{
			jewelV[i].jewelX = jewelV[i].jewelRc.left + 8;
		}

		//오른쪽 벽 충돌
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

	//그리기
	treasureBoxRc = RectMakeCenter(treasureX, treasureY, 60, 44);
}
//=============렌더=============
void treasureBox::render(void)
{
	//보물상자
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), treasureBoxRc);
	}
	treasureBoxImg->frameRender(getMemDC(), treasureBoxRc.left - CAMERA.getCRc().left, treasureBoxRc.top - CAMERA.getCRc().top, frameX, frameY);

	//보석
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
