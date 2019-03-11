#include "stdafx.h"
#include "UIClass.h"

HRESULT UIClass::init(string _petsWhere)
{
	petsWhere = _petsWhere; //어느 스테이지에서 이닛했는지

	//보석
	jewelShapeImg = IMAGEMANAGER->findImage("UI-보석모양");

	//체력
	HPImg = IMAGEMANAGER->findImage("UI-체력");

	frameHP = TXTDATA.getCurrentPipData()->pipMaxHP; //전역변수 싱글톤인 텍스트데이터에서 현재 세이브파일의 핍 최대체력을 가져온다

	//스테이지1
	//물개
	checkSealS1.CheckImg = IMAGEMANAGER->findImage("UI-펫 발견");
	checkSealS1.isCheck = TXTDATA.getCurrentPipData()->isFindSealS1;
	checkSealS1.framePet = 2;
	checkSealS1.position = {903,40};
	//박쥐
	checkBatS1.CheckImg = IMAGEMANAGER->findImage("UI-펫 발견");
	checkBatS1.isCheck = TXTDATA.getCurrentPipData()->isFindBatS1;
	checkBatS1.framePet = 1;
	checkBatS1.position = { 1003,40 };
	//상어
	checkSharkS1.CheckImg = IMAGEMANAGER->findImage("UI-펫 발견");
	checkSharkS1.isCheck = TXTDATA.getCurrentPipData()->isFindSharkS1;
	checkSharkS1.framePet = 3;
	checkSharkS1.position = { 953,40 };

	//보스 스테이지
	//물개
	checkSealB.CheckImg = IMAGEMANAGER->findImage("UI-펫 발견");
	checkSealB.isCheck = false;
	checkSealB.framePet = 2;
	//박쥐
	checkBatB.CheckImg = IMAGEMANAGER->findImage("UI-펫 발견");
	checkBatB.isCheck = false;
	checkBatB.framePet = 1;
	//상어
	checkSharkB.CheckImg = IMAGEMANAGER->findImage("UI-펫 발견");
	checkSharkB.isCheck = false;
	checkSharkB.framePet = 3;


	return S_OK;
}

void UIClass::release()
{
}

void UIClass::update()
{
	if (KEYMANAGER->isOnceKeyDown('H'))
	{
		if (checkSealS1.isCheck)
			checkSealS1.isCheck = false;
		else
			checkSealS1.isCheck = true;
	}
	if (KEYMANAGER->isOnceKeyDown('Y'))
	{
		if (checkBatS1.isCheck)
			checkBatS1.isCheck = false;
		else
			checkBatS1.isCheck = true;
	}
	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		if (checkSharkS1.isCheck)
			checkSharkS1.isCheck = false;
		else
			checkSharkS1.isCheck = true;
	}

}

void UIClass::render()
{
	if (petsWhere == "Stage1")
	{
		if (checkSealS1.isCheck)
		{
			checkSealS1.CheckImg->frameRender(getMemDC(), checkSealS1.position.x, checkSealS1.position.y, checkSealS1.framePet, 0);
		}
		else
		{
			checkSealS1.CheckImg->frameRender(getMemDC(), checkSealS1.position.x, checkSealS1.position.y, 0, 0);
		}

		if (checkBatS1.isCheck)
		{
			checkBatS1.CheckImg->frameRender(getMemDC(), checkBatS1.position.x, checkBatS1.position.y, checkBatS1.framePet,0);
		}
		else
		{
			checkBatS1.CheckImg->frameRender(getMemDC(), checkBatS1.position.x, checkBatS1.position.y, 0, 0);
		}

		if (checkSharkS1.isCheck)
		{
			checkSharkS1.CheckImg->frameRender(getMemDC(), checkSharkS1.position.x, checkSharkS1.position.y, checkSharkS1.framePet,0);
		}
		else
		{
			checkSharkS1.CheckImg->frameRender(getMemDC(), checkSharkS1.position.x, checkSharkS1.position.y, 0, 0);
		}

	}
	else if (petsWhere == "BossStage")
	{

	}



	jewelShapeImg->render(getMemDC(), 1083, 40);

	HPImg->frameRender(getMemDC(), 70, 40, frameHP, 0);

}
