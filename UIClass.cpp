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
	checkSealS1.framePet = 0;
	//박쥐
	checkBatS1.CheckImg = IMAGEMANAGER->findImage("UI-펫 발견");
	checkBatS1.isCheck = false;
	checkBatS1.framePet = 0;
	//상어
	checkSharkS1.CheckImg = IMAGEMANAGER->findImage("UI-펫 발견");
	checkSharkS1.isCheck = false;
	checkSharkS1.framePet = 0;

	//보스 스테이지
	//물개
	checkSealB.CheckImg = IMAGEMANAGER->findImage("UI-펫 발견");
	checkSealB.isCheck = false;
	checkSealB.framePet = 0;
	//박쥐
	checkBatB.CheckImg = IMAGEMANAGER->findImage("UI-펫 발견");
	checkBatB.isCheck = false;
	checkBatB.framePet = 0;
	//상어
	checkSharkB.CheckImg = IMAGEMANAGER->findImage("UI-펫 발견");
	checkSharkB.isCheck = false;
	checkSharkB.framePet = 0;


	return S_OK;
}

void UIClass::release()
{
}

void UIClass::update()
{
	if (checkSealS1.isCheck == true) checkSealS1.framePet = 1;
	if (checkSealB.isCheck == true) checkSealB.framePet = 1;
	if (checkBatS1.isCheck == true) checkBatS1.framePet = 2;
	if (checkBatB.isCheck == true) checkBatB.framePet = 2;
	if (checkSharkS1.isCheck == true) checkSharkS1.framePet = 3;
	if (checkSharkB.isCheck == true) checkSharkB.framePet = 3;



}

void UIClass::render()
{
	if (petsWhere == "Stage1")
	{
		//물개
		checkSealS1.CheckImg->frameRender(getMemDC(), 840, 30, checkSealS1.framePet, 0);
		//박쥐
		checkBatS1.CheckImg->frameRender(getMemDC(), 890, 30, checkBatS1.framePet, 0);
		//상어
		checkSharkS1.CheckImg->frameRender(getMemDC(), 940, 30, checkSharkS1.framePet, 0);
	}
	else if (petsWhere == "BossStage")
	{
		//물개
		checkSealB.CheckImg->frameRender(getMemDC(), 840, 30, checkSealB.framePet, 0);
		//박쥐
		checkBatB.CheckImg->frameRender(getMemDC(), 890, 30, checkBatB.framePet, 0);
		//상어
		checkSharkB.CheckImg->frameRender(getMemDC(), 940, 30, checkSharkB.framePet, 0);
	}

	jewelShapeImg->render(getMemDC(), 1083, 40);

	HPImg->frameRender(getMemDC(), 70, 40, frameHP, 0);

}
