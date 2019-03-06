#include "stdafx.h"
#include "EnemyClass.h"

//===================================
//	## 떠다니는 문어 enemy ##
//===================================
#pragma region 떠다니는 문어
//=============초기화=============
HRESULT flyOctopus::init(void)
{
	enemyImage = IMAGEMANAGER->findImage("enemy-떠다니는 문어");

	enemyX = 0;
	enemyY = 0;
	enemySpeed = 0;
	isDie = false;

	imgCount = 0;
	frameX = 0;
	frameY = 0;

	return S_OK;
}
//=============해제=============
void flyOctopus::release(void)
{
}
//=============업데이트=============
void flyOctopus::update(void)
{
	//이미지 프레임
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
//=============렌더=============
void flyOctopus::render(void)
{
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), enemyRc);
	}
	enemyImage->frameRender(getMemDC(), enemyRc.left, enemyRc.top, frameX, frameY);

}
#pragma endregion 떠다니는 문어

//===================================
//	## 기어다니는 벌레 enemy ##
//===================================
#pragma region 기어다니는 벌레
//=============초기화=============
HRESULT crawlBug::init(void)
{
	enemyImage = IMAGEMANAGER->findImage("enemy-기어다니는 벌레");

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
//=============해제=============
void crawlBug::release(void)
{
}
//=============업데이트=============
void crawlBug::update(void)
{
	//좌우 이동
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

	//이미지 프레임
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
//=============렌더=============
void crawlBug::render(void)
{
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), enemyRc);
	}

	enemyImage->frameRender(getMemDC(), enemyRc.left, enemyRc.top, frameX, frameY);

}

#pragma endregion 기어다니는 벌레

//===================================
//	## 날아다니는 크리스탈 enemy ##
//===================================
#pragma region 날아다니는 크리스탈
//=============초기화=============
HRESULT flyCrystal::init(void)
{
	enemyImage = IMAGEMANAGER->findImage("enemy-떠다니는 크리스탈");

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
//=============해제=============
void flyCrystal::release(void)
{
}
//=============업데이트=============
void flyCrystal::update(void)
{
	//좌우 이동
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

	//이미지 프레임
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
//=============렌더=============
void flyCrystal::render(void)
{
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), enemyRc);
	}

	enemyImage->frameRender(getMemDC(), enemyRc.left, enemyRc.top, frameX, frameY);
}

#pragma endregion 날아다니는 크리스탈