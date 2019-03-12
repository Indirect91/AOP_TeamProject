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
	checkSealS1.framePet = 0;
	//����
	checkBatS1.CheckImg = IMAGEMANAGER->findImage("UI-�� �߰�");
	checkBatS1.isCheck = false;
	checkBatS1.framePet = 0;
	//���
	checkSharkS1.CheckImg = IMAGEMANAGER->findImage("UI-�� �߰�");
	checkSharkS1.isCheck = false;
	checkSharkS1.framePet = 0;

	//���� ��������
	//����
	checkSealB.CheckImg = IMAGEMANAGER->findImage("UI-�� �߰�");
	checkSealB.isCheck = false;
	checkSealB.framePet = 0;
	//����
	checkBatB.CheckImg = IMAGEMANAGER->findImage("UI-�� �߰�");
	checkBatB.isCheck = false;
	checkBatB.framePet = 0;
	//���
	checkSharkB.CheckImg = IMAGEMANAGER->findImage("UI-�� �߰�");
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

	jewelShapeImg->render(getMemDC(), 1083, 40);

	HPImg->frameRender(getMemDC(), 70, 40, frameHP, 0);

}
