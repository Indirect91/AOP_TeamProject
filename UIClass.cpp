#include "stdafx.h"
#include "UIClass.h"

HRESULT UIClass::init(string _petsWhere)
{
	petsWhere = _petsWhere; //��� ������������ �̴��ߴ���

	//����
	jewelShapeImg = IMAGEMANAGER->findImage("UI-�������");

	//ü��
	HPImg = IMAGEMANAGER->findImage("UI-ü��");

	frameHP = TXTDATA.getCurrentPipData()->pipMaxHP; //�������� �̱����� �ؽ�Ʈ�����Ϳ��� ���� ���̺������� �� �ִ�ü���� �����´�

	//��������1
	//����
	checkSealS1.CheckImg = IMAGEMANAGER->findImage("UI-�� �߰�");
	checkSealS1.isCheck = TXTDATA.getCurrentPipData()->isFindSealS1;
	checkSealS1.framePet = 2;
	checkSealS1.position = {903,40};
	//����
	checkBatS1.CheckImg = IMAGEMANAGER->findImage("UI-�� �߰�");
	checkBatS1.isCheck = TXTDATA.getCurrentPipData()->isFindBatS1;
	checkBatS1.framePet = 1;
	checkBatS1.position = { 1003,40 };
	//���
	checkSharkS1.CheckImg = IMAGEMANAGER->findImage("UI-�� �߰�");
	checkSharkS1.isCheck = TXTDATA.getCurrentPipData()->isFindSharkS1;
	checkSharkS1.framePet = 3;
	checkSharkS1.position = { 953,40 };

	//���� ��������
	//����
	checkSealB.CheckImg = IMAGEMANAGER->findImage("UI-�� �߰�");
	checkSealB.isCheck = false;
	checkSealB.framePet = 2;
	//����
	checkBatB.CheckImg = IMAGEMANAGER->findImage("UI-�� �߰�");
	checkBatB.isCheck = false;
	checkBatB.framePet = 1;
	//���
	checkSharkB.CheckImg = IMAGEMANAGER->findImage("UI-�� �߰�");
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
