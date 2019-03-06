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
//=============렌더=============
void savePoint::render(void)
{
	//세이브 포인트
	savePointRc = RectMakeCenter(savePX - CAMERA.getCRc().left, savePY - CAMERA.getCRc().top, 30, 126);
	savePointImg->frameRender(getMemDC(), savePointRc.left, savePointRc.top, frameX1, 0);

	//세이브 포인트랑 충돌했을때 나오는 불꽃
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
//	## 보물상자 ##
//===================================
//=============초기화=============
HRESULT treasureBox::init(float _x, float _y, bool _isRight)
{
	treasureBoxImg = IMAGEMANAGER->findImage("보물상자");
	
	isOpen = false;
	isRight = _isRight;

	treasureX = _x;
	treasureY = _y;

	imgCount = 0;
	frameX = frameY = 0;

	return S_OK;
}
//=============해제=============
void treasureBox::release(void)
{
}
//=============업데이트=============
void treasureBox::update(void)
{
	if (isRight == true) frameY = 0;
	else if (isRight == false) frameY = 1;

	//확인을 위해 임시로 넣은 키
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
//=============렌더=============
void treasureBox::render(void)
{
	treasureBoxRc = RectMakeCenter(treasureX, treasureY, 30, 44);
	treasureBoxImg->frameRender(getMemDC(), treasureBoxRc.left, treasureBoxRc.top, frameX, frameY);
}
