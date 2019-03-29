#include "stdafx.h"
#include "BossClass.h"
#include "PlayerClass.h"

//=============초기화=============
HRESULT BossClass::init(void)
{
	bossIdleImg = IMAGEMANAGER->findImage("boss-대기");
	bossShoutImg = IMAGEMANAGER->findImage("boss-고함");
	bossChangeImg = IMAGEMANAGER->findImage("boss-변신");
	bossWalkImg = IMAGEMANAGER->findImage("boss-걷기");
	bossRunImg = IMAGEMANAGER->findImage("boss-달리기");
	bossAttack1Img = IMAGEMANAGER->findImage("boss-공격1");
	bossAttack2Img = IMAGEMANAGER->findImage("boss-공격2");
	bossAttackedImg = IMAGEMANAGER->findImage("boss-피격");
	bossDieImg = IMAGEMANAGER->findImage("boss-죽음");

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
//=============해제=============
void BossClass::release(void)
{
}
//=============업데이트=============
void BossClass::update(void)
{
	//플레이어가 떨어졌을때 시작하게 할것임
	if (bPlayerPtr->getRect().bottom > 2285 && isStart == false && isMeet == false)
	{
		frameX = 0;
		bossState = change;
		isMeet = true;
	}

	//전투시작
	if (isStart == true)
	{
		//보스가 플레이어에 따라 이동
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

	//보스를 밟았을때
	if (IntersectRect(&bEmpty, &bPlayerPtr->getSensorRcBottom(), &bossRc) && bossState != attacked && bossState != die && bossState != end)
	{
		//플레이어 조건
		bPlayerPtr->setGravity(-6.f);

		//보스조건
		bossHp -= 1;
		if (bossHp > 0)
		{
			//체력에 따라 속도 다르게
			bossSpeed += 2.f;
			imgCount = 0;
			if (isRight == false) frameX = 0;
			else if (isRight == true) frameX = 3;
			bossState = attacked;
		}
	}

	//보스 체력이 0
	if (bossHp == 0 && bossState != die && bossState != end)
	{
		if (isRight == false) frameX = 0;
		else if (isRight == true) frameX = 24;
		bossSpeed = 0;
		bossState = die;
	}

	//보스랑 플레이어랑 충돌해서 보스가 공격함
	if (IntersectRect(&bEmpty, &bPlayerPtr->getSensorRcLeft(), &bossAttackRc)
		&& bossState != attack1 && bossState != attacked && bossState != die && bossState != end ||
		IntersectRect(&bEmpty, &bPlayerPtr->getSensorRcRight(), &bossAttackRc)
		&& bossState != attack1 && bossState != attacked && bossState != die && bossState != end)
	{
		bPlayerPtr->setPipHp(bPlayerPtr->getPipHp() - 1);
		//플레이어 조건
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

		//보스 조건
		imgCount = 0;
		if (isRight == false) frameX = 0;
		else if (isRight == true) frameX = 6;
		bossState = attack1;
	}





	//보스 애니메이션
	imgCount++;
	switch (bossState)
	{
		//대기
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
		//고함
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
		//변신
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
		//걷기
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
		//달리기
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
		//공격1-휘두르기
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
		//공격2-내려찍기
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
		//공격당함
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
		//죽음
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
//=============렌더=============
void BossClass::render(void)
{
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), RelativeCameraRect(bossRc));
		Rectangle(getMemDC(), RelativeCameraRect(bossAttackRc));
	}

	/*
	240, 182
	대기 : 96,92
	고함 : 312, 204
	걷기 : 258, 210
	변신 : 264, 366
	공격1 : 510, 228
	공격2 : 306,240
	피격 : 246, 210
	죽음 : 408, 210
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
	//TextOutInt(getMemDC(), 200, 10, "체력", bossHp);
	//TextOutInt(getMemDC(), 200, 30, "보스", isDie);
}
