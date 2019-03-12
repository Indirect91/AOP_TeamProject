#include "stdafx.h"
#include "EnemyClass.h"

//===================================
//	## 떠다니는 문어 enemy ##
//===================================
#pragma region 떠다니는 문어
//=============초기화=============
HRESULT flyOctopus::init(float _enemyX, float _enemyY)
{
	enemyImage = IMAGEMANAGER->findImage("enemy-떠다니는 문어");

	enemyX = _enemyX;
	enemyY = _enemyY;
	isDie = false;

	dieCount = 1.f;
	dieCountX = 1.f;
	firstStep = false;

	reviveCount = 0;

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
	//죽었을때 다시 되살아나게
	if (isDie == true)
	{
		if (firstStep == false)
		{
			dieCount -= 0.1f;
			dieCountX += 0.1f;
			if (dieCount < 0.5f)
			{
				dieCount = 0;
				firstStep = true;
			}
		}
		else
		{
			dieCount += 0.07f;
			dieCountX -= 0.05f;
			if (dieCountX < 0)
			{
				dieCountX = 0;
				dieCount = 1.5f;
			}
		}

		reviveCount++;
		if (reviveCount % 180 == 0)
		{
			reviveCount = 0;

			imgCount = 0;
			frameX = 0;
			frameY = 0;

			isDie = false;
		}
	}
	else
	{
		//dieCount = 1.f;

		dieCountX += 0.1f;
		dieCount -= 0.05f;
		if (dieCountX > 1.f)
		{
			dieCountX = 1.f;
			dieCount = 1.f;
			firstStep = false;
		}
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

	enemyRc = RectMakeCenter(enemyX, enemyY, 47, 66);

}
//=============렌더=============
void flyOctopus::render(void)
{
	//렉트 확인용 토글키
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), RelativeCameraRect(enemyRc));
	}

	enemyImage->stretchFrameRenderCenterXDownY(getMemDC(), enemyRc.left - CAMERA.getCRc().left, enemyRc.top - CAMERA.getCRc().top, frameX, frameY, dieCountX, dieCount);

}
#pragma endregion 떠다니는 문어

///===================================
//	## 기어다니는 벌레 enemy ##
//===================================
#pragma region 기어다니는 벌레
//=============초기화=============
HRESULT crawlBug::init(float _x, float _y, float _scaleLeftX, float _scaleRightX)
{
	enemyImage = IMAGEMANAGER->findImage("enemy-기어다니는 벌레");

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

	scaleLeftX = _scaleLeftX;
	scaleRightX = _scaleRightX;

	dieCount = 1.f;
	dieCountX = 1.f;

	firstStep = true;

	return S_OK;
}
//=============해제=============
void crawlBug::release(void)
{
}
//=============업데이트=============
void crawlBug::update(void)
{
	//죽었을때 다시 되살아나게
	if (isDie == true)
	{
		if (firstStep == false)
		{
			dieCount -= 0.1f;
			dieCountX += 0.1f;
			if (dieCount < 0.5f)
			{
				dieCount = 0;
				firstStep = true;
			}
		}
		else
		{
			dieCount += 0.07f;
			dieCountX -= 0.05f;
			if (dieCountX < 0)
			{
				dieCountX = 0;
				dieCount = 1.5f;
			}
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

		dieCountX += 0.1f;
		dieCount -= 0.05f;
		if (dieCountX > 1.f)
		{
			dieCountX = 1.f;
			dieCount = 1.f;
			firstStep = false;
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

	//좌우 이동
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

	enemyRc = RectMakeCenter(enemyX, enemyY, 47, 24);

}
//=============렌더=============
void crawlBug::render(void)
{
	//렉트 확인용 토글키
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), RelativeCameraRect(enemyRc));
	}

	enemyImage->stretchFrameRenderCenterXDownY(getMemDC(), enemyRc.left - CAMERA.getCRc().left, enemyRc.top - CAMERA.getCRc().top, frameX, frameY, dieCountX, dieCount);
	//enemyImage->frameRender(getMemDC(), enemyRc.left - CAMERA.getCRc().left, enemyRc.top - CAMERA.getCRc().top, frameX, frameY);

}

#pragma endregion 기어다니는 벌레

//===================================
//	## 날아다니는 크리스탈 enemy ##
//===================================
#pragma region 날아다니는 크리스탈
//=============초기화=============
HRESULT flyCrystal::init(float _x, float _y, float _scaleLeftX, float _scaleRightX)
{
	enemyImage = IMAGEMANAGER->findImage("enemy-떠다니는 크리스탈");

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

	scaleLeftX = _scaleLeftX;
	scaleRightX = _scaleRightX;

	dieCount = 225;

	return S_OK;
}
//=============해제=============
void flyCrystal::release(void)
{
}
//=============업데이트=============
void flyCrystal::update(void)
{
	//죽었을때 다시 되살아나게
	if (isDie == true)
	{
		reviveCount++;

		if (reviveCount < 61)
		{
			if (reviveCount % 5 == 0)
			{
				dieCount += 125;
			}
		}
		else
		{
			dieCount = 0;
		}

		if (reviveCount % 180 == 0)
		{
			enemyX = saveX;
			enemyY = saveY;

			imgCount = 0;
			frameX = 0;
			frameY = 0;
			dieCount = 225;

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

	//좌우 이동
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

	enemyRc = RectMakeCenter(enemyX, enemyY, 90, 61);
}
//=============렌더=============
void flyCrystal::render(void)
{
	//렉트 확인용 토글키
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), RelativeCameraRect(enemyRc));
	}

	//죽어있지 않을때만 보이게
	enemyImage->alphaFrameRender(getMemDC(), enemyRc.left - CAMERA.getCRc().left, enemyRc.top - 11 - CAMERA.getCRc().top, frameX, frameY, dieCount);

}

#pragma endregion 날아다니는 크리스탈

//===================================
//	## 둥둥이 유령 enemy ##
//===================================
#pragma region 둥둥이 유령
//=============초기화=============
HRESULT flyGhost::init(float _x, float _y)
{
	enemyImage = IMAGEMANAGER->findImage("enemy-둥둥이 유령");

	enemyX = _x;
	enemyY = _y;
	enemySpeed = 0;
	isDie = false;
	reviveCount = 0;

	imgCount = 0;
	frameX = 0;
	frameY = 0;

	return S_OK;
}

void flyGhost::release(void)
{
}

void flyGhost::update(void)
{
	//죽었을때 다시 되살아나게
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

	//이미지 프레임
	imgCount++;
	if (imgCount % 10 == 0)
	{
		frameX++;
		if (frameX > 3)
		{
			frameX = 0;
		}
		imgCount = 0;
	}

	enemyRc = RectMakeCenter(enemyX, enemyY, 59, 70);
}

void flyGhost::render(void)
{
	//렉트 확인용 토글키
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), RelativeCameraRect(enemyRc));
	}

	//죽어있지 않을때만 보이게
	if (isDie == false)
	{
		enemyImage->frameRender(getMemDC(), enemyRc.left - CAMERA.getCRc().left, enemyRc.top - CAMERA.getCRc().top, frameX, frameY);
	}
}

#pragma endregion 둥둥이 유령