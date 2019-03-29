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
	petsWhere = _petsWhere; //��� ������������ �̴��ߴ���

	//����
	jewelShapeImg = IMAGEMANAGER->findImage("UI-�������");
	//�ϴ� �ӽ÷� �迭
	for (int i = 0; i < 5; i++)
	{
		jewelCountImg[i] = IMAGEMANAGER->findImage("UI-����");
	}

	maxHp = TXTDATA.getCurrentPipData()->pipMaxHP; //�������� �̱����� �ؽ�Ʈ�����Ϳ��� ���� ���̺������� �� �ִ�ü���� �����´�

	//ü��
	for (UINT i = 0; i < maxHp; i++)
	{
		tagHeart temp;
		temp.frameHp = 1;											//ü���� 1�̸� ������Ʈ, 0�̸� ü���� ��ұ� ������ 0!
		temp.Hpimg = IMAGEMANAGER->findImage("UI-ü��");				//�̹��� �Ҵ�
		temp.position = { (LONG)(i * 70) + 70 , 40 };				//�̹��� ��ġ ����
		totalHeartV.push_back(temp);								//���Ϳ�  �־���~
	}

	isPurchasable = true;
	isInvenFull = true;
	isNoMoney = true;

	//��������1
	//����
	checkSealS1.CheckImg = IMAGEMANAGER->findImage("UI-�� �߰�");
	checkSealS1.isCheck = TXTDATA.getCurrentPipData()->isFindSealS1;
	checkSealS1.framePet = 0;
	//����
	checkBatS1.CheckImg = IMAGEMANAGER->findImage("UI-�� �߰�");
	checkBatS1.isCheck = TXTDATA.getCurrentPipData()->isFindBatS1;
	checkBatS1.framePet = 0;
	//���
	checkSharkS1.CheckImg = IMAGEMANAGER->findImage("UI-�� �߰�");
	checkSharkS1.isCheck = TXTDATA.getCurrentPipData()->isFindSharkS1;
	checkSharkS1.framePet = 0;

	//���� ��������
	//����
	checkSealB.CheckImg = IMAGEMANAGER->findImage("UI-�� �߰�");
	checkSealB.isCheck = TXTDATA.getCurrentPipData()->isFindSealB;
	checkSealB.framePet = 0;
	//����
	checkBatB.CheckImg = IMAGEMANAGER->findImage("UI-�� �߰�");
	checkBatB.isCheck = TXTDATA.getCurrentPipData()->isFindBatB;
	checkBatB.framePet = 0;
	//���
	checkSharkB.CheckImg = IMAGEMANAGER->findImage("UI-�� �߰�");
	checkSharkB.isCheck = TXTDATA.getCurrentPipData()->isFindSharkB;
	checkSharkB.framePet = 0;

	//����
	storeImg = IMAGEMANAGER->findImage("����");
	selectImg = IMAGEMANAGER->findImage("�����ۼ���");
	selectX = 582;
	selectY = 227;
	textImg = IMAGEMANAGER->findImage("��ǳ��");
	isShop = false;

	return S_OK;
}

void UIClass::release()
{
}

void UIClass::update()
{
	//���� üũ
	if (checkSealS1.isCheck == true) checkSealS1.framePet = 1;
	if (checkSealB.isCheck == true) checkSealB.framePet = 1;
	if (checkBatS1.isCheck == true) checkBatS1.framePet = 2;
	if (checkBatB.isCheck == true) checkBatB.framePet = 2;
	if (checkSharkS1.isCheck == true) checkSharkS1.framePet = 3;
	if (checkSharkB.isCheck == true) checkSharkB.framePet = 3;

	/*
		��Ʈ : 582,227
		��Ʈ : 721,227
		���� : 582,337
		�� : 721,337
	*/
	//����
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
					temp.frameHp = 1;																					//ü���� 1�̸� ������Ʈ, 0�̸� ü���� ��ұ� ������ 0!
					temp.Hpimg = IMAGEMANAGER->findImage("UI-ü��");														//�̹��� �Ҵ�
					temp.position = { (LONG)((TXTDATA.getCurrentPipData()->pipMaxHP - 1) * 70) + 70 , 40 };				//�̹��� ��ġ ����
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
		//����ã�� ������
		else if (selectX == 721 && selectY == 227)
		{
			if (TXTDATA.getCurrentPipData()->pipMoney > 7)
			{
				//���� �ְ� �κ��丮 ���ڰ� 0�̸� �������� ���� �� ����
				//111
				if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					isInvenFull = false;
				}
				//110
				else if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 5;
					TXTDATA.getCurrentPipData()->thirdItem = "����ã��";
				}
				//100
				else if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 5;
					TXTDATA.getCurrentPipData()->secondItem = "����ã��";
				}
				//101
				else if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 5;
					TXTDATA.getCurrentPipData()->secondItem = "����ã��";
				}
				//011
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 5;
					TXTDATA.getCurrentPipData()->firstItem = "����ã��";
				}
				//010
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 5;
					TXTDATA.getCurrentPipData()->firstItem = "����ã��";
				}
				//000
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 5;
					TXTDATA.getCurrentPipData()->firstItem = "����ã��";
				}
				//001
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 5;
					TXTDATA.getCurrentPipData()->firstItem = "����ã��";
				}
			}
			else
			{
				isNoMoney = false;
			}
		}
		//ü������ ������
		else if (selectX == 582 && selectY == 337)
		{
			if (TXTDATA.getCurrentPipData()->pipMoney > 7)
			{
				//0�̸� �������� ���� �� ����
				//111
				if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					isInvenFull = false;
				}
				//110
				else if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 7;
					TXTDATA.getCurrentPipData()->thirdItem = "ü������";
				}
				//100
				else if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 7;
					TXTDATA.getCurrentPipData()->secondItem = "ü������";
				}
				//101
				else if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 7;
					TXTDATA.getCurrentPipData()->secondItem = "ü������";
				}
				//011
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 7;
					TXTDATA.getCurrentPipData()->firstItem = "ü������";
				}
				//010
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 7;
					TXTDATA.getCurrentPipData()->firstItem = "ü������";
				}
				//000
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 7;
					TXTDATA.getCurrentPipData()->firstItem = "ü������";
				}
				//001
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 7;
					TXTDATA.getCurrentPipData()->firstItem = "ü������";
				}
			}
			else
			{
				isNoMoney = false;
			}
		}
		//�Һ�ȣ�� ������
		else if (selectX == 721 && selectY == 337)
		{
			if (TXTDATA.getCurrentPipData()->pipMoney > 7)
			{
				//0�̸� �������� ���� �� ����
				//111
				if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					isInvenFull = false;
				}
				//110
				else if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 12;
					TXTDATA.getCurrentPipData()->thirdItem = "�Һ�ȣ��";
				}
				//100
				else if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 12;
					TXTDATA.getCurrentPipData()->secondItem = "�Һ�ȣ��";
				}
				//101
				else if (TXTDATA.getCurrentPipData()->firstItem != "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 12;
					TXTDATA.getCurrentPipData()->secondItem = "�Һ�ȣ��";
				}
				//011
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 12;
					TXTDATA.getCurrentPipData()->firstItem = "�Һ�ȣ��";
				}
				//010
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem != "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 12;
					TXTDATA.getCurrentPipData()->firstItem = "�Һ�ȣ��";
				}
				//000
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem == "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 12;
					TXTDATA.getCurrentPipData()->firstItem = "�Һ�ȣ��";
				}
				//001
				else if (TXTDATA.getCurrentPipData()->firstItem == "0" && TXTDATA.getCurrentPipData()->secondItem == "0" && TXTDATA.getCurrentPipData()->thirdItem != "0")
				{
					TXTDATA.getCurrentPipData()->pipMoney -= 12;
					TXTDATA.getCurrentPipData()->firstItem = "�Һ�ȣ��";
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
	//���� ã�Ҵ��� �����ִ� UI
	if (petsWhere == "Stage1")
	{
		//����
		checkSealS1.CheckImg->frameRender(getMemDC(), 840, 30, checkSealS1.framePet, 0);
		//����
		checkBatS1.CheckImg->frameRender(getMemDC(), 890, 30, checkBatS1.framePet, 0);
		//���
		checkSharkS1.CheckImg->frameRender(getMemDC(), 940, 30, checkSharkS1.framePet, 0);
	}
	else if (petsWhere == "BossStage")
	{
		//����
		checkSealB.CheckImg->frameRender(getMemDC(), 840, 30, checkSealB.framePet, 0);
		//����
		checkBatB.CheckImg->frameRender(getMemDC(), 890, 30, checkBatB.framePet, 0);
		//���
		checkSharkB.CheckImg->frameRender(getMemDC(), 940, 30, checkSharkB.framePet, 0);
	}

	//����
	jewelShapeImg->render(getMemDC(), 1135, 36);
	//���� ���� �����ֱ�
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
		//ü��
		for (UINT i = 0; i < uiPlayerPtr->getPipHp(); i++)
		{
			totalHeartV[i].Hpimg->frameRender(getMemDC(), totalHeartV[i].position.x, totalHeartV[i].position.y, totalHeartV[i].frameHp, 0);
		}
	}
	else if (petsWhere == "BossStage")
	{
		//ü��
		for (UINT i = 0; i < uiPlayerPtr->getPipHp(); i++)
		{
			totalHeartV[i].Hpimg->frameRender(getMemDC(), totalHeartV[i].position.x, totalHeartV[i].position.y, totalHeartV[i].frameHp, 0);
		}
	}
	else
	{
		//ü��
		for (UINT i = 0; i < TXTDATA.getCurrentPipData()->pipMaxHP; i++)
		{
			totalHeartV[i].Hpimg->frameRender(getMemDC(), totalHeartV[i].position.x, totalHeartV[i].position.y, totalHeartV[i].frameHp, 0);
		}
	}



	//����
	if (isShop == true)
	{
		storeImg->render(getMemDC(), 433, 146);
		selectImg->render(getMemDC(), selectX, selectY);
		/*
		���� �� : 149,81 -> 582,227
		������ �� : 288,81 -> 721,227
		���� �Ʒ� : 149,191 -> 582,337
		������ �Ʒ� : 288,191 -> 721,337
		*/
		textImg->render(getMemDC(), 333, 518);

		if (isPurchasable != true)
		{
			string temp = "���̻� �������� ���մϴ�.";
			TextOut(getMemDC(), 600, 593, temp.c_str(), temp.size());
		}
		if (isInvenFull != true)
		{
			string temp = "�κ��丮�� ���� á���ϴ�.";
			TextOut(getMemDC(), 600, 613, temp.c_str(), temp.size());
		}
		if (isNoMoney != true)
		{
			string temp = "���� �����մϴ�";
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

