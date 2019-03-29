#include "stdafx.h"
#include "UIClass.h"
//#include "ItemClass.h"
//#include "SearchAnimalClass.h"
//#include "FireRingClass.h"
//#include "potionClass.h"
#include "PlayerClass.h"
#include "TitleClass.h"

HRESULT UIClass::init(string _petsWhere)
{
	petsWhere = _petsWhere; //어느 스테이지에서 이닛했는지

	//보석
	jewelShapeImg = IMAGEMANAGER->findImage("UI-보석모양");
	//일단 임시로 배열
	for (int i = 0; i < 5; i++)
	{
		jewelCountImg[i] = IMAGEMANAGER->findImage("UI-숫자");
	}

	maxHp = TXTDATA.getCurrentPipData()->pipMaxHP; //전역변수 싱글톤인 텍스트데이터에서 현재 세이브파일의 핍 최대체력을 가져온다

	//체력
	for (UINT i = 0; i < maxHp; i++)
	{
		tagHeart temp;
		temp.frameHp = 1;											//체력이 1이면 빨간하트, 0이면 체력이 닳았기 때문에 0!
		temp.Hpimg = IMAGEMANAGER->findImage("UI-체력");				//이미지 할당
		temp.position = { (LONG)(i * 70) + 70 , 40 };				//이미지 위치 조정
		totalHeartV.push_back(temp);								//벡터에  넣어줘~
	}

	isPurchasable = true;
	isInvenFull = true;
	isNoMoney = true;

	//스테이지1
	//물개
	checkSealS1.CheckImg = IMAGEMANAGER->findImage("UI-펫 발견");
	checkSealS1.isCheck = TXTDATA.getCurrentPipData()->isFindSealS1;
	checkSealS1.framePet = 0;
	//박쥐
	checkBatS1.CheckImg = IMAGEMANAGER->findImage("UI-펫 발견");
	checkBatS1.isCheck = TXTDATA.getCurrentPipData()->isFindBatS1;
	checkBatS1.framePet = 0;
	//상어
	checkSharkS1.CheckImg = IMAGEMANAGER->findImage("UI-펫 발견");
	checkSharkS1.isCheck = TXTDATA.getCurrentPipData()->isFindSharkS1;
	checkSharkS1.framePet = 0;

	//보스 스테이지
	//물개
	checkSealB.CheckImg = IMAGEMANAGER->findImage("UI-펫 발견");
	checkSealB.isCheck = TXTDATA.getCurrentPipData()->isFindSealB;
	checkSealB.framePet = 0;
	//박쥐
	checkBatB.CheckImg = IMAGEMANAGER->findImage("UI-펫 발견");
	checkBatB.isCheck = TXTDATA.getCurrentPipData()->isFindBatB;
	checkBatB.framePet = 0;
	//상어
	checkSharkB.CheckImg = IMAGEMANAGER->findImage("UI-펫 발견");
	checkSharkB.isCheck = TXTDATA.getCurrentPipData()->isFindSharkB;
	checkSharkB.framePet = 0;

	//상점
	storeImg = IMAGEMANAGER->findImage("상점");
	selectImg = IMAGEMANAGER->findImage("아이템선택");
	selectX = 582;
	selectY = 227;
	textImg = IMAGEMANAGER->findImage("말풍선");
	isShop = false;

	return S_OK;
}

void UIClass::release()
{
}

void UIClass::update()
{
	//동물 체크
	if (checkSealS1.isCheck == true) checkSealS1.framePet = 1;
	if (checkSealB.isCheck == true) checkSealB.framePet = 1;
	if (checkBatS1.isCheck == true) checkBatS1.framePet = 2;
	if (checkBatB.isCheck == true) checkBatB.framePet = 2;
	if (checkSharkS1.isCheck == true) checkSharkS1.framePet = 3;
	if (checkSharkB.isCheck == true) checkSharkB.framePet = 3;

	/*
		하트 : 582,227
		힌트 : 721,227
		포션 : 582,337
		불 : 721,337
	*/
	//상점
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && isShop == true) if (selectX == 582) selectX = 721;
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && isShop == true) if (selectX == 721) selectX = 582;
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && isShop == true) if (selectY == 227) selectY = 337;
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && isShop == true) if (selectY == 337) selectY = 227;
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && isShop)
	{
		if (selectX == 582 && selectY == 227)
		{

			if (TXTDATA.getCurrentPipData()->pipMoney > 0)
			{
				if (TXTDATA.getCurrentPipData()->pipMaxHP != 5)
				{
					TXTDATA.getCurrentPipData()->pipMaxHP += 1;
					TXTDATA.getCurrentPipData()->pipMoney -= 15;
					tagHeart temp;
					temp.frameHp = 1;																					//체력이 1이면 빨간하트, 0이면 체력이 닳았기 때문에 0!
					temp.Hpimg = IMAGEMANAGER->findImage("UI-체력");														//이미지 할당
					temp.position = { (LONG)((TXTDATA.getCurrentPipData()->pipMaxHP - 1) * 70) + 70 , 40 };				//이미지 위치 조정
					totalHeartV.push_back(temp);
				}
				else
				{
					isPurchasable = false;
				}
			}
			else
			{
				isNoMoney = false;
			}
		}
		//동물찾기 아이템
		else if (selectX == 721 && selectY == 227)
		{
			if (TXTDATA.getCurrentPipData()->pipMoney > 7)
			{
				//돈이 있고 인벤토리 숫자가 0이면 아이템을 넣을 수 있음
				//111
				if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					isInvenFull = false;
				}
				//110
				else if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 5;
					TXTDATA.getCurrentPipData()->thirdItem = "동물찾기";
				}
				//100
				else if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 5;
					TXTDATA.getCurrentPipData()->secondItem = "동물찾기";
				}
				//101
				else if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 5;
					TXTDATA.getCurrentPipData()->secondItem = "동물찾기";
				}
				//011
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 5;
					TXTDATA.getCurrentPipData()->firstItem = "동물찾기";
				}
				//010
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 5;
					TXTDATA.getCurrentPipData()->firstItem = "동물찾기";
				}
				//000
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 5;
					TXTDATA.getCurrentPipData()->firstItem = "동물찾기";
				}
				//001
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 5;
					TXTDATA.getCurrentPipData()->firstItem = "동물찾기";
				}
			}
			else
			{
				isNoMoney = false;
			}
		}
		//체력증가 아이템
		else if (selectX == 582 && selectY == 337)
		{
			if (TXTDATA.getCurrentPipData()->pipMoney > 7)
			{
				//0이면 아이템을 넣을 수 있음
				//111
				if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					isInvenFull = false;
				}
				//110
				else if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 7;
					TXTDATA.getCurrentPipData()->thirdItem = "체력증가";
				}
				//100
				else if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 7;
					TXTDATA.getCurrentPipData()->secondItem = "체력증가";
				}
				//101
				else if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 7;
					TXTDATA.getCurrentPipData()->secondItem = "체력증가";
				}
				//011
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 7;
					TXTDATA.getCurrentPipData()->firstItem = "체력증가";
				}
				//010
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 7;
					TXTDATA.getCurrentPipData()->firstItem = "체력증가";
				}
				//000
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 7;
					TXTDATA.getCurrentPipData()->firstItem = "체력증가";
				}
				//001
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 7;
					TXTDATA.getCurrentPipData()->firstItem = "체력증가";
				}
			}
			else
			{
				isNoMoney = false;
			}
		}
		//불보호막 아이템
		else if (selectX == 721 && selectY == 337)
		{
			if (TXTDATA.getCurrentPipData()->pipMoney > 7)
			{
				//0이면 아이템을 넣을 수 있음
				//111
				if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					isInvenFull = false;
				}
				//110
				else if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 12;
					TXTDATA.getCurrentPipData()->thirdItem = "불보호막";
				}
				//100
				else if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 12;
					TXTDATA.getCurrentPipData()->secondItem = "불보호막";
				}
				//101
				else if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 12;
					TXTDATA.getCurrentPipData()->secondItem = "불보호막";
				}
				//011
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 12;
					TXTDATA.getCurrentPipData()->firstItem = "불보호막";
				}
				//010
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 12;
					TXTDATA.getCurrentPipData()->firstItem = "불보호막";
				}
				//000
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 12;
					TXTDATA.getCurrentPipData()->firstItem = "불보호막";
				}
				//001
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 12;
					TXTDATA.getCurrentPipData()->firstItem = "불보호막";
				}
			}
		}
		else
		{
			isNoMoney = false;
		}
	}
}

void UIClass::render()
{
	//펫을 찾았는지 보여주는 UI
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

	//보석
	jewelShapeImg->render(getMemDC(), 1135, 36);
	//보석 개수 보여주기
	for (int i = 0; i < 5; i++)
	{
		if (i == 0)
		{
			jNum = TXTDATA.getCurrentPipData()->pipMoney % 10;
			switch (jNum)
			{
			case 0:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 0, 0);
				break;

			case 1:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 1, 0);
				break;

			case 2:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 2, 0);
				break;

			case 3:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 3, 0);
				break;

			case 4:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 4, 0);
				break;

			case 5:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 5, 0);
				break;

			case 6:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 6, 0);
				break;

			case 7:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 7, 0);
				break;

			case 8:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 8, 0);
				break;

			case 9:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 9, 0);
				break;
			}
		}
		if (i == 1)
		{
			jNum = TXTDATA.getCurrentPipData()->pipMoney / 10;
			jNum = jNum % 10;
			switch (jNum)
			{
			case 0:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 0, 0);
				break;

			case 1:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 1, 0);
				break;

			case 2:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 2, 0);
				break;

			case 3:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 3, 0);
				break;

			case 4:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 4, 0);
				break;

			case 5:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 5, 0);
				break;

			case 6:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 6, 0);
				break;

			case 7:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 7, 0);
				break;

			case 8:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 8, 0);
				break;

			case 9:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 9, 0);
				break;
			}
		}
		if (i == 2)
		{
			jNum = TXTDATA.getCurrentPipData()->pipMoney / 100;
			jNum = jNum % 10;
			switch (jNum)
			{
			case 0:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 0, 0);
				break;

			case 1:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 1, 0);
				break;

			case 2:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 2, 0);
				break;

			case 3:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 3, 0);
				break;

			case 4:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 4, 0);
				break;

			case 5:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 5, 0);
				break;

			case 6:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 6, 0);
				break;

			case 7:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 7, 0);
				break;

			case 8:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 8, 0);
				break;

			case 9:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 9, 0);
				break;
			}
		}
		if (i == 4)
		{
			jNum = TXTDATA.getCurrentPipData()->pipMoney / 1000;
			jNum = jNum % 10;
			switch (jNum)
			{
			case 0:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 0, 0);
				break;

			case 1:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 1, 0);
				break;

			case 2:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 2, 0);
				break;

			case 3:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 3, 0);
				break;

			case 4:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 4, 0);
				break;

			case 5:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 5, 0);
				break;

			case 6:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 6, 0);
				break;

			case 7:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 7, 0);
				break;

			case 8:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 8, 0);
				break;

			case 9:
				jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 9, 0);
				break;
			}
		}

		if (i == 3)
		{
			jewelCountImg[i]->frameRender(getMemDC(), 1256 - 20 * i, 40, 11, 0);
			continue;
		}
		if (i == 0 && TXTDATA.getCurrentPipData()->pipMoney < 10) break;
		else if (i == 1 && TXTDATA.getCurrentPipData()->pipMoney < 100) break;
		else if (i == 2 && TXTDATA.getCurrentPipData()->pipMoney < 1000) break;
		else if (i == 4 && TXTDATA.getCurrentPipData()->pipMoney < 10000) break;
	}

	if (petsWhere == "Stage1")
	{
		//체력
		for (UINT i = 0; i < uiPlayerPtr->getPipHp(); i++)
		{
			totalHeartV[i].Hpimg->frameRender(getMemDC(), totalHeartV[i].position.x, totalHeartV[i].position.y, totalHeartV[i].frameHp, 0);
		}
	}
	else if (petsWhere == "BossStage")
	{
		//체력
		for (UINT i = 0; i < uiPlayerPtr->getPipHp(); i++)
		{
			totalHeartV[i].Hpimg->frameRender(getMemDC(), totalHeartV[i].position.x, totalHeartV[i].position.y, totalHeartV[i].frameHp, 0);
		}
	}
	else
	{
		//체력
		for (UINT i = 0; i < TXTDATA.getCurrentPipData()->pipMaxHP; i++)
		{
			totalHeartV[i].Hpimg->frameRender(getMemDC(), totalHeartV[i].position.x, totalHeartV[i].position.y, totalHeartV[i].frameHp, 0);
		}
	}



	//상점
	if (isShop == true)
	{
		storeImg->render(getMemDC(), 433, 146);
		selectImg->render(getMemDC(), selectX, selectY);
		/*
		왼쪽 위 : 149,81 -> 582,227
		오른쪽 위 : 288,81 -> 721,227
		왼쪽 아래 : 149,191 -> 582,337
		오른쪽 아래 : 288,191 -> 721,337
		*/
		textImg->render(getMemDC(), 333, 518);

		if (isPurchasable != true)
		{
			string temp = "더이상 구매하지 못합니다.";
			TextOut(getMemDC(), 600, 593, temp.c_str(), temp.size());
		}
		if (isInvenFull != true)
		{
			string temp = "인벤토리가 가득 찼습니다.";
			TextOut(getMemDC(), 600, 613, temp.c_str(), temp.size());
		}
		if (isNoMoney != true)
		{
			string temp = "돈이 부족합니다";
			TextOut(getMemDC(), 600, 633, temp.c_str(), temp.size());
		}
	}

	string temp1 = TXTDATA.getCurrentPipData()->firstItem;
	if(TXTDATA.getCurrentPipData()->firstItem !="0") 
		TextOut(getMemDC(), 100, 200, temp1.c_str(), temp1.size());

	string temp2 = TXTDATA.getCurrentPipData()->secondItem;
	if (TXTDATA.getCurrentPipData()->secondItem != "0")  
		TextOut(getMemDC(), 100, 220, temp2.c_str(), temp2.size());
	
	string temp3 = TXTDATA.getCurrentPipData()->thirdItem;
	if (TXTDATA.getCurrentPipData()->thirdItem != "0")  
		TextOut(getMemDC(), 100, 240, temp3.c_str(), temp3.size());

}

