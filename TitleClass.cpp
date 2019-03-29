#include "stdafx.h"
#include "TitleClass.h"

HRESULT TitleClass::init(void)
{
	//▼이미지 할당
	titlebg = IMAGEMANAGER->findImage("titleBg");
	titlelogo = IMAGEMANAGER->findImage("titleLogo");
	pip1 = IMAGEMANAGER->findImage("pip1");
	pip2 = IMAGEMANAGER->findImage("pip2");
	pip3 = IMAGEMANAGER->findImage("pip3");
	esc = IMAGEMANAGER->findImage("PressEsc");
	enter = IMAGEMANAGER->findImage("PressEnter");
	fileSelect = IMAGEMANAGER->findImage("fileSelect");
	loadFile = IMAGEMANAGER->findImage("loadFile");
	ESC_YSetting = IMAGEMANAGER->findImage("ESC_YSetting");
	newEmpty = IMAGEMANAGER->findImage("newEmpty");
	selection = IMAGEMANAGER->findImage("selection");
	rescueAnimal = IMAGEMANAGER->findImage("UI-숫자");
	maxHeart = IMAGEMANAGER->findImage("UI-숫자");
	continueimg = IMAGEMANAGER->findImage("Continue");

	for (int i = 0; i < 4; i++)
	{
		moneyNum[i] = IMAGEMANAGER->findImage("UI-숫자");
	}
	SOUNDMANAGER->play("타이틀",TXTDATA.refBGMSound());
	slot1Pets = IMAGEMANAGER->findImage("UI-숫자");
	slot2Pets = IMAGEMANAGER->findImage("UI-숫자");
	slot3Pets = IMAGEMANAGER->findImage("UI-숫자");
	//▼세이브슬롯별 이닛
	if (TXTDATA.getPip1Cinematic() == 1)
	{
		saveSlot1 = IMAGEMANAGER->findImage("loadFile");
		slot1Pets = IMAGEMANAGER->findImage("UI-숫자");
	}
	else saveSlot1 = IMAGEMANAGER->findImage("newEmpty");
	if (TXTDATA.getPip2Cinematic() == 1)
	{
		saveSlot2 = IMAGEMANAGER->findImage("loadFile");
		slot2Pets = IMAGEMANAGER->findImage("UI-숫자");
	}
	else saveSlot2 = IMAGEMANAGER->findImage("newEmpty");
	if (TXTDATA.getPip3Cinematic() == 1)
	{
		saveSlot3 = IMAGEMANAGER->findImage("loadFile");
		slot3Pets = IMAGEMANAGER->findImage("UI-숫자");
	}
	else saveSlot3 = IMAGEMANAGER->findImage("newEmpty");



	//▼초기 위치 조정
	pip1->setX(0 - pip1->getWidth());
	pip1->setY(WINSIZEY / 2 - pip1->getHeight() / 2);
	pip2->setX(WINSIZEX);
	pip2->setY(WINSIZEY / 2 - pip2->getHeight() / 2);
	pip3->setX(WINSIZEX / 2 - pip3->getWidth() / 2);
	pip3->setY(WINSIZEY);
	titlelogo->setX(WINSIZEX / 2 - titlelogo->getWidth() / 2);
	titlelogo->setY(0 - titlelogo->getHeight());
	esc->setX(50);
	esc->setY(WINSIZEY);
	enter->setX(WINSIZEX - 50 - enter->getWidth());
	enter->setY(WINSIZEY);
	fileSelect->setX(WINSIZEX / 2 - fileSelect->getWidth() / 2);
	fileSelect->setY(-fileSelect->getHeight());
	selection->setX(fileSelect->getX());
	selection->setY(fileSelect->getY() + 150);
	ESC_YSetting->setX(WINSIZEX / 2 - ESC_YSetting->getWidth() / 2);
	ESC_YSetting->setY(WINSIZEY);
	
	saveSlot1Pos = { fileSelect->getX() + 90 , fileSelect->getY() + 205 };
	saveSlot2Pos = { fileSelect->getX() + 423 , fileSelect->getY() + 205 };
	saveSlot3Pos = { fileSelect->getX() + 759 , fileSelect->getY() + 205 };

	Pip1Pets = 0;
	Pip2Pets = 0;
	Pip3Pets = 0;

	if (TXTDATA.getData1().isFindBatS1 == true) Pip1Pets++;
	if (TXTDATA.getData1().isFindSealS1 == true) Pip1Pets++;
	if (TXTDATA.getData1().isFindSharkS1 == true) Pip1Pets++;
	if (TXTDATA.getData1().isFindBatB == true) Pip1Pets++;
	if (TXTDATA.getData1().isFindSealB == true) Pip1Pets++;
	if (TXTDATA.getData1().isFindSharkB == true) Pip1Pets++;

	if (TXTDATA.getData2().isFindBatS1 == true) Pip2Pets++;
	if (TXTDATA.getData2().isFindSealS1 == true) Pip2Pets++;
	if (TXTDATA.getData2().isFindSharkS1 == true) Pip2Pets++;
	if (TXTDATA.getData2().isFindBatB == true) Pip2Pets++;
	if (TXTDATA.getData2().isFindSealB == true) Pip2Pets++;
	if (TXTDATA.getData2().isFindSharkB == true) Pip2Pets++;

	if (TXTDATA.getData3().isFindBatS1 == true) Pip3Pets++;
	if (TXTDATA.getData3().isFindSealS1 == true) Pip3Pets++;
	if (TXTDATA.getData3().isFindSharkS1 == true) Pip3Pets++;
	if (TXTDATA.getData3().isFindBatB == true) Pip3Pets++;
	if (TXTDATA.getData3().isFindSealB == true) Pip3Pets++;
	if (TXTDATA.getData3().isFindSharkB == true) Pip3Pets++;



	counter = 0;
	SecondPhase = false;
	LastPhase = false;
	titleAlpha = 255;

	return S_OK;
}

void TitleClass::release(void)
{
	//new 해준것이 없으므로 릴리즈 없음
}

void TitleClass::update(void)
{
	counter++;

	//▼첫째 페이즈 화면 불러오는부분
	if (SecondPhase == false && LastPhase==false && counter < 17)
	{
		if (titleAlpha != 255) titleAlpha += 15;
		if (pip1->getX() <= 80) pip1->setX(pip1->getX() + 20); //320이동
		if (pip2->getX() > 1046) pip2->setX(pip2->getX() - 20); //320이동
		if (pip3->getY() > 360) pip3->setY(pip3->getY() - 26); //408 이동
		if (titlelogo->getY() <= 30) titlelogo->setY(titlelogo->getY() + 18); //284 이동
		if (esc->getY() > 640) esc->setY(esc->getY() - 15); //128 이동
		if (enter->getY() > 620) enter->setY(enter->getY() - 15); //148이동 
		if (fileSelect->getY() >= -fileSelect->getHeight()) fileSelect->setY(fileSelect->getY() - 55); //540이동
		if (ESC_YSetting->getY() < WINSIZEY) ESC_YSetting->setY(ESC_YSetting->getY() + 15); //128 이동
		selection->setX(fileSelect->getX());
		selection->setY(fileSelect->getY() + 150);
		saveSlot1Pos = { fileSelect->getX() + 91 , fileSelect->getY() + 205 };
		saveSlot2Pos = { fileSelect->getX() + 425 , fileSelect->getY() + 205 };
		saveSlot3Pos = { fileSelect->getX() + 759 , fileSelect->getY() + 205 };
	}

	//▼첫째 페이즈 이미지들 이동이 끝난 후부터 키입력부분
	if (SecondPhase==false && counter > 18) //모션이동은 16프레임만에 끝난다. 모션 끝 이후부터 엔터 입력받을수 있게 처리
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			SOUNDMANAGER->play("메뉴선택", TXTDATA.refSFXSound());
			SecondPhase = true; //둘째 페이즈로 넘어가게 true
			counter = 0; //카운터 다시 사용하게 0으로 돌림
		}
		if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
		{
			PostMessage(_hWnd, WM_DESTROY, 0, 0); //ESC입력시 게임 꺼지게 처리
		}
	}

	//▼둘째 페이즈 
	if (SecondPhase)
	{
		if (counter < 18) //박스들 돌아가는거 스르륵 아직 진행중일때
		{
			//▼복귀코드
			if (titleAlpha != 105) titleAlpha -= 15;
			if (pip1->getX() >= -pip1->getWidth()) pip1->setX(pip1->getX() - 20); //320이동
			if (pip2->getX() < WINSIZEX) pip2->setX(pip2->getX() + 20); //320이동
			if (pip3->getY() < WINSIZEY) pip3->setY(pip3->getY() + 26); //408 이동
			if (titlelogo->getY() >= -titlelogo->getHeight()) titlelogo->setY(titlelogo->getY() - 18); //284 이동
			if (esc->getY() < WINSIZEY) esc->setY(esc->getY() + 15); //128 이동
			if (enter->getY() < WINSIZEY) enter->setY(enter->getY() + 15); //148이동 

			//▼띄우는 코드
			if (fileSelect->getY() <= 38) fileSelect->setY(fileSelect->getY() + 34); //540이동
			else if (fileSelect->getY() > 38) fileSelect->setY(38); //540이동
			if (ESC_YSetting->getY() > 640) ESC_YSetting->setY(ESC_YSetting->getY() - 8); //128 이동
			selection->setX(fileSelect->getX());
			selection->setY(fileSelect->getY() + 150);
			saveSlot1Pos = { fileSelect->getX() + 91 , fileSelect->getY() + 205 };
			saveSlot2Pos = { fileSelect->getX() + 425 , fileSelect->getY() + 205 };
			saveSlot3Pos = { fileSelect->getX() + 759 , fileSelect->getY() + 205 };
			

		}

		else
		{
			if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
			{

				counter = 0; //카운터 0으로 돌려서 재활용
				SecondPhase = false; //2단계 페이즈 꺼버리면 다시 첫째페이즈로 돌아감

			}
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				if (selection->getX() != WINSIZEX / 2 - fileSelect->getWidth() / 2)
				{
					SOUNDMANAGER->play("메뉴이동", TXTDATA.refSFXSound());
					selection->setX(selection->getX() - 333);
				}

			}
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				if (selection->getX() != WINSIZEX / 2 - fileSelect->getWidth() / 2 + 666)
				{
					SOUNDMANAGER->play("메뉴이동", TXTDATA.refSFXSound());
					selection->setX(selection->getX() + 333);
				}

			}
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				LastPhase = true;
				SecondPhase = false;
				counter = 0;
			}

		}


	}

	if (LastPhase)
	{
		if (titleAlpha != 0) titleAlpha -= 5;

		if (fileSelect->getY() >= -fileSelect->getHeight()) fileSelect->setY(fileSelect->getY() - 55); //540이동
		if (ESC_YSetting->getY() < WINSIZEY) ESC_YSetting->setY(ESC_YSetting->getY() + 15); //128 이동
		selection->setY(fileSelect->getY() + 150);
		saveSlot1Pos = { fileSelect->getX() + 91 , fileSelect->getY() + 205 };
		saveSlot2Pos = { fileSelect->getX() + 425 , fileSelect->getY() + 205 };
		saveSlot3Pos = { fileSelect->getX() + 759 , fileSelect->getY() + 205 };




		if (titleAlpha<=0)
		{
			if (selection->getX() < fileSelect->getX() + 10)
			{
				
				SOUNDMANAGER->play("세이브", TXTDATA.refSFXSound());
				TXTDATA.setWhichSavefile("saveSlot1.txt");
				if(TXTDATA.getPip1Cinematic()==1) SCENEMANAGER->loadScene("WorldMap");
				else if (TXTDATA.getPip1Cinematic() == 0)
				{
					SOUNDMANAGER->pause("타이틀");
					SCENEMANAGER->loadScene("Cinema");
				}

			}
			else if (selection->getX() < fileSelect->getX() + 355)
			{
				
				SOUNDMANAGER->play("세이브", TXTDATA.refSFXSound());
				TXTDATA.setWhichSavefile("saveSlot2.txt");
				if (TXTDATA.getPip2Cinematic() == 1) SCENEMANAGER->loadScene("WorldMap");
				else if (TXTDATA.getPip2Cinematic() == 0)
				{
					SOUNDMANAGER->pause("타이틀");
					SCENEMANAGER->loadScene("Cinema");
				}
			}
			else if (selection->getX() < fileSelect->getX() + 355+343)
			{
				SOUNDMANAGER->play("세이브", TXTDATA.refSFXSound());
				TXTDATA.setWhichSavefile("saveSlot3.txt");
				if (TXTDATA.getPip3Cinematic() == 1) SCENEMANAGER->loadScene("WorldMap");
				else if (TXTDATA.getPip3Cinematic() == 0)
				{
					SOUNDMANAGER->pause("타이틀");
					SCENEMANAGER->loadScene("Cinema");
				}
				
				
			}
		}
	}






}

void TitleClass::render(void)
{
	titlebg->alphaRender(getMemDC(), titleAlpha);
	if (!(SecondPhase&&counter > 17))
	{
		pip1->render(getMemDC(), pip1->getX(), pip1->getY());
		pip2->render(getMemDC(), pip2->getX(), pip2->getY());
		pip3->render(getMemDC(), pip3->getX(), pip3->getY());
		titlelogo->render(getMemDC(), titlelogo->getX(), titlelogo->getY());
		esc->render(getMemDC(), esc->getX(), esc->getY());
		enter->render(getMemDC(), enter->getX(), enter->getY());
	}
	selection->render(getMemDC(), selection->getX(), selection->getY());
	fileSelect->render(getMemDC(), fileSelect->getX(), fileSelect->getY());
	ESC_YSetting->render(getMemDC(), ESC_YSetting->getX(), ESC_YSetting->getY());

	saveSlot1->render(getMemDC(), saveSlot1Pos.x, saveSlot1Pos.y);
	saveSlot2->render(getMemDC(), saveSlot2Pos.x, saveSlot2Pos.y);
	saveSlot3->render(getMemDC(), saveSlot3Pos.x, saveSlot3Pos.y);

	//slot1Pets->frameRender(getMemDC(), 400, 300, Pip1Pets, 0);
	//slot1Pets->frameRender(getMemDC(), 600, 300, Pip2Pets, 0);
	//slot1Pets->frameRender(getMemDC(), 900, 300, Pip3Pets, 0);


	if (SecondPhase && TXTDATA.getPip1Cinematic() == 1) slot1Pets->frameRender(getMemDC(), saveSlot1Pos.x + 85, saveSlot1Pos.y + 160, Pip1Pets, 0);
	if (SecondPhase && TXTDATA.getPip2Cinematic() == 1) slot2Pets->frameRender(getMemDC(), saveSlot2Pos.x + 85, saveSlot2Pos.y + 160, Pip2Pets, 0);
	if (SecondPhase&& TXTDATA.getPip3Cinematic() == 1) slot3Pets->frameRender(getMemDC(), saveSlot3Pos.x + 85, saveSlot3Pos.y + 160, Pip3Pets, 0);

	//1Slot Hp
	if (SecondPhase && TXTDATA.getPip1Cinematic()==1)
	{
		continueimg->render(getMemDC(), saveSlot1Pos.x+30 , saveSlot1Pos.y+3 );
		heratNum = TXTDATA.getData1().pipMaxHP;

		switch (heratNum)
		{
		case 0:
			maxHeart->frameRender(getMemDC(), saveSlot1Pos.x, saveSlot1Pos.y, 0, 0);
			break;

		case 1:
			maxHeart->frameRender(getMemDC(), 410, 354, 1, 0);
			break;

		case 2:
			maxHeart->frameRender(getMemDC(), 410, 354, 2, 0);
			break;

		case 3:
			maxHeart->frameRender(getMemDC(), saveSlot1Pos.x+130, saveSlot1Pos.y+103, 3, 0);
			break;

		case 4:
			maxHeart->frameRender(getMemDC(), saveSlot1Pos.x + 130, saveSlot1Pos.y + 103, 4, 0);
			break;

		case 5:
			maxHeart->frameRender(getMemDC(), saveSlot1Pos.x + 130, saveSlot1Pos.y + 103, 5, 0);
			break;
		}
	}

	//2Slot Hp
	if (SecondPhase && TXTDATA.getPip2Cinematic() == 1)
	{
		continueimg->render(getMemDC(), saveSlot2Pos.x + 30, saveSlot2Pos.y + 3);
		heratNum = TXTDATA.getData2().pipMaxHP;
	
		switch (heratNum)
		{
		case 0:
			maxHeart->frameRender(getMemDC(), 765, 354, 0, 0);
			break;
	
		case 1:
			maxHeart->frameRender(getMemDC(), 765, 354, 1, 0);
			break;
	
		case 2:
			maxHeart->frameRender(getMemDC(), 765, 354, 2, 0);
			break;
	
		case 3:
			maxHeart->frameRender(getMemDC(), saveSlot2Pos.x + 130, saveSlot2Pos.y + 103, 3, 0);
			break;
	
		case 4:
			maxHeart->frameRender(getMemDC(), saveSlot2Pos.x + 130, saveSlot2Pos.y + 103, 4, 0);
			break;
	
		case 5:
			maxHeart->frameRender(getMemDC(), saveSlot2Pos.x + 130, saveSlot2Pos.y + 103, 5, 0);
			break;
		}
	}

	//3Slot Hp
	if (SecondPhase&& TXTDATA.getPip3Cinematic() == 1)
	{
		continueimg->render(getMemDC(), saveSlot3Pos.x + 30, saveSlot3Pos.y + 3);
		heratNum = TXTDATA.getData3().pipMaxHP;

		switch (heratNum)
		{
		case 0:
			maxHeart->frameRender(getMemDC(), 1077, 354, 0, 0);
			break;

		case 1:
			maxHeart->frameRender(getMemDC(), 1077, 354, 1, 0);
			break;

		case 2:
			maxHeart->frameRender(getMemDC(), 1077, 354, 2, 0);
			break;

		case 3:
			maxHeart->frameRender(getMemDC(), saveSlot3Pos.x + 130, saveSlot3Pos.y + 103, 3, 0);
			break;

		case 4:
			maxHeart->frameRender(getMemDC(), saveSlot3Pos.x + 130, saveSlot3Pos.y + 103, 4, 0);
			break;

		case 5:
			maxHeart->frameRender(getMemDC(), saveSlot3Pos.x + 130, saveSlot3Pos.y + 103, 5, 0);
			break;
		}
	}

	//1Slot Money
	if (SecondPhase && TXTDATA.getPip1Cinematic()==1)
	{
		for (int i = 0; i < 5; i++)
		{
			if (i == 0)
			{
				jNum = TXTDATA.getData1().pipMoney % 10;
				switch (jNum)
				{
				case 0:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 0, 0);
					break;

				case 1:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 1, 0);
					break;

				case 2:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 2, 0);
					break;

				case 3:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 3, 0);
					break;

				case 4:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 4, 0);
					break;

				case 5:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 5, 0);
					break;

				case 6:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 6, 0);
					break;

				case 7:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 7, 0);
					break;

				case 8:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 8, 0);
					break;

				case 9:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 9, 0);
					break;
				}
			}
			if (i == 1)
			{
				jNum = TXTDATA.getData1().pipMoney / 10;
				jNum = jNum % 10;
				switch (jNum)
				{
				case 0:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 0, 0);
					break;

				case 1:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 1, 0);
					break;

				case 2:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 2, 0);
					break;

				case 3:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 3, 0);
					break;

				case 4:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 4, 0);
					break;

				case 5:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 5, 0);
					break;

				case 6:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 6, 0);
					break;

				case 7:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 7, 0);
					break;

				case 8:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 8, 0);
					break;

				case 9:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 9, 0);
					break;
				}
			}
			if (i == 2)
			{
				jNum = TXTDATA.getData1().pipMoney / 100;
				jNum = jNum % 10;
				switch (jNum)
				{
				case 0:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 0, 0);
					break;

				case 1:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 1, 0);
					break;

				case 2:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 2, 0);
					break;

				case 3:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 3, 0);
					break;

				case 4:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 4, 0);
					break;

				case 5:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 5, 0);
					break;

				case 6:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 6, 0);
					break;

				case 7:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 7, 0);
					break;

				case 8:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 8, 0);
					break;

				case 9:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 9, 0);
					break;
				}
			}
			if (i == 4)
			{
				jNum = TXTDATA.getData1().pipMoney / 1000;
				jNum = jNum % 10;
				switch (jNum)
				{
				case 0:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 0, 0);
					break;

				case 1:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 1, 0);
					break;

				case 2:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 2, 0);
					break;

				case 3:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 3, 0);
					break;

				case 4:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 4, 0);
					break;

				case 5:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 5, 0);
					break;

				case 6:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 6, 0);
					break;

				case 7:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 7, 0);
					break;

				case 8:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 8, 0);
					break;

				case 9:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 9, 0);
					break;
				}
			}

			if (i == 3)
			{
				moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 150 - 20 * i, saveSlot1Pos.y + 218, 11, 0);
				continue;
			}
			if (i == 0 && TXTDATA.getData1().pipMoney < 10) break;
			else if (i == 1 && TXTDATA.getData1().pipMoney < 100) break;
			else if (i == 2 && TXTDATA.getData1().pipMoney < 1000) break;
			else if (i == 4 && TXTDATA.getData1().pipMoney < 10000) break;
		}
	}

	//2Slot Money
	if (SecondPhase&& TXTDATA.getPip2Cinematic() == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			if (i == 0)
			{
				jNum = TXTDATA.getData2().pipMoney % 10;
				switch (jNum)
				{
				case 0:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 0, 0);
					break;
	
				case 1:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 1, 0);
					break;
	
				case 2:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 2, 0);
					break;
	
				case 3:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 3, 0);
					break;
	
				case 4:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 4, 0);
					break;
	
				case 5:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 5, 0);
					break;
	
				case 6:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 6, 0);
					break;
	
				case 7:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 7, 0);
					break;
	
				case 8:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 8, 0);
					break;
	
				case 9:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 9, 0);
					break;
				}
			}
			if (i == 1)
			{
				jNum = TXTDATA.getData2().pipMoney / 10;
				jNum = jNum % 10;
				switch (jNum)
				{
				case 0:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 0, 0);
					break;
	
				case 1:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 1, 0);
					break;
	
				case 2:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 2, 0);
					break;
	
				case 3:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 3, 0);
					break;
	
				case 4:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 4, 0);
					break;
	
				case 5:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 5, 0);
					break;
	
				case 6:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 6, 0);
					break;
	
				case 7:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 7, 0);
					break;
	
				case 8:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 8, 0);
					break;
	
				case 9:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 9, 0);
					break;
				}
			}
			if (i == 2)
			{
				jNum = TXTDATA.getData2().pipMoney / 100;
				jNum = jNum % 10;
				switch (jNum)
				{
				case 0:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 0, 0);
					break;
	
				case 1:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 1, 0);
					break;
	
				case 2:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 2, 0);
					break;
	
				case 3:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 3, 0);
					break;
	
				case 4:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 4, 0);
					break;
	
				case 5:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 5, 0);
					break;
	
				case 6:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 6, 0);
					break;
	
				case 7:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 7, 0);
					break;
	
				case 8:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 8, 0);
					break;
	
				case 9:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 9, 0);
					break;
				}
			}
			if (i == 4)
			{
				jNum = TXTDATA.getData2().pipMoney / 1000;
				jNum = jNum % 10;
				switch (jNum)
				{
				case 0:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 0, 0);
					break;
	
				case 1:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 1, 0);
					break;
	
				case 2:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 2, 0);
					break;
	
				case 3:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 3, 0);
					break;
	
				case 4:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 4, 0);
					break;
	
				case 5:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 5, 0);
					break;
	
				case 6:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 6, 0);
					break;
	
				case 7:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 7, 0);
					break;
	
				case 8:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 8, 0);
					break;
	
				case 9:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 9, 0);
					break;
				}
			}
	
			if (i == 3)
			{
				moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 490 - 20 * i, saveSlot1Pos.y + 218, 11, 0);
				continue;
			}
			if (i == 0 && TXTDATA.getData2().pipMoney < 10) break;
			else if (i == 1 && TXTDATA.getData2().pipMoney < 100) break;
			else if (i == 2 && TXTDATA.getData2().pipMoney < 1000) break;
			else if (i == 4 && TXTDATA.getData2().pipMoney < 10000) break;
		}
	}

	//3Slot Money
	if (SecondPhase&& TXTDATA.getPip3Cinematic() == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			if (i == 0)
			{
				jNum = TXTDATA.getData3().pipMoney % 10;
				switch (jNum)
				{
				case 0:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 0, 0);
					break;

				case 1:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 1, 0);
					break;

				case 2:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 2, 0);
					break;

				case 3:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 3, 0);
					break;

				case 4:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 4, 0);
					break;

				case 5:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 5, 0);
					break;

				case 6:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 6, 0);
					break;

				case 7:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 7, 0);
					break;

				case 8:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 8, 0);
					break;

				case 9:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 9, 0);
					break;
				}
			}
			if (i == 1)
			{
				jNum = TXTDATA.getData3().pipMoney / 10;
				jNum = jNum % 10;
				switch (jNum)
				{
				case 0:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 0, 0);
					break;

				case 1:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 1, 0);
					break;

				case 2:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 2, 0);
					break;

				case 3:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 3, 0);
					break;

				case 4:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 4, 0);
					break;

				case 5:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 5, 0);
					break;

				case 6:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 6, 0);
					break;

				case 7:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 7, 0);
					break;

				case 8:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 8, 0);
					break;

				case 9:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 9, 0);
					break;
				}
			}
			if (i == 2)
			{
				jNum = TXTDATA.getData3().pipMoney / 100;
				jNum = jNum % 10;
				switch (jNum)
				{
				case 0:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 0, 0);
					break;

				case 1:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 1, 0);
					break;

				case 2:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 2, 0);
					break;

				case 3:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 3, 0);
					break;

				case 4:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 4, 0);
					break;

				case 5:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 5, 0);
					break;

				case 6:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 6, 0);
					break;

				case 7:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 7, 0);
					break;

				case 8:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 8, 0);
					break;

				case 9:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 9, 0);
					break;
				}
			}
			if (i == 4)
			{
				jNum = TXTDATA.getData3().pipMoney / 1000;
				jNum = jNum % 10;
				switch (jNum)
				{
				case 0:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 0, 0);
					break;

				case 1:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 1, 0);
					break;

				case 2:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 2, 0);
					break;

				case 3:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 3, 0);
					break;

				case 4:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 4, 0);
					break;

				case 5:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 5, 0);
					break;

				case 6:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 6, 0);
					break;

				case 7:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 7, 0);
					break;

				case 8:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 8, 0);
					break;

				case 9:
					moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 9, 0);
					break;
				}
			}

			if (i == 3)
			{
				moneyNum[i]->frameRender(getMemDC(), saveSlot1Pos.x + 825 - 20 * i, saveSlot1Pos.y + 218, 11, 0);
				continue;
			}
			if (i == 0 && TXTDATA.getData3().pipMoney < 10) break;
			else if (i == 1 && TXTDATA.getData3().pipMoney < 100) break;
			else if (i == 2 && TXTDATA.getData3().pipMoney < 1000) break;
			else if (i == 4 && TXTDATA.getData3().pipMoney < 10000) break;
		}
	}
	
}
