#include "stdafx.h"
#include "TitleClass.h"

HRESULT TitleClass::init(void)
{
	//���̹��� �Ҵ�
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

	//�弼�̺꽽�Ժ� �̴�
	if (TXTDATA.getPip1Cinematic()==1) saveSlot1 = IMAGEMANAGER->findImage("loadFile");
	else saveSlot1 = IMAGEMANAGER->findImage("newEmpty");
	if (TXTDATA.getPip2Cinematic()==1) saveSlot2 = IMAGEMANAGER->findImage("loadFile");
	else saveSlot2 = IMAGEMANAGER->findImage("newEmpty");
	if (TXTDATA.getPip3Cinematic()==1) saveSlot3 = IMAGEMANAGER->findImage("loadFile");
	else saveSlot3 = IMAGEMANAGER->findImage("newEmpty");



	//���ʱ� ��ġ ����
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

	counter = 0;
	SecondPhase = false;
	LastPhase = false;
	titleAlpha = 255;

	return S_OK;
}

void TitleClass::release(void)
{
	//new ���ذ��� �����Ƿ� ������ ����
}

void TitleClass::update(void)
{
	counter++;

	//��ù° ������ ȭ�� �ҷ����ºκ�
	if (SecondPhase == false && LastPhase==false && counter < 17)
	{
		if (titleAlpha != 255) titleAlpha += 15;
		if (pip1->getX() <= 80) pip1->setX(pip1->getX() + 20); //320�̵�
		if (pip2->getX() > 1046) pip2->setX(pip2->getX() - 20); //320�̵�
		if (pip3->getY() > 360) pip3->setY(pip3->getY() - 26); //408 �̵�
		if (titlelogo->getY() <= 30) titlelogo->setY(titlelogo->getY() + 18); //284 �̵�
		if (esc->getY() > 640) esc->setY(esc->getY() - 15); //128 �̵�
		if (enter->getY() > 620) enter->setY(enter->getY() - 15); //148�̵� 
		if (fileSelect->getY() >= -fileSelect->getHeight()) fileSelect->setY(fileSelect->getY() - 55); //540�̵�
		if (ESC_YSetting->getY() < WINSIZEY) ESC_YSetting->setY(ESC_YSetting->getY() + 15); //128 �̵�
		selection->setX(fileSelect->getX());
		selection->setY(fileSelect->getY() + 150);
		saveSlot1Pos = { fileSelect->getX() + 91 , fileSelect->getY() + 205 };
		saveSlot2Pos = { fileSelect->getX() + 425 , fileSelect->getY() + 205 };
		saveSlot3Pos = { fileSelect->getX() + 759 , fileSelect->getY() + 205 };
	}

	//��ù° ������ �̹����� �̵��� ���� �ĺ��� Ű�Էºκ�
	if (SecondPhase==false && counter > 18) //����̵��� 16�����Ӹ��� ������. ��� �� ���ĺ��� ���� �Է¹����� �ְ� ó��
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			SecondPhase = true; //��° ������� �Ѿ�� true
			counter = 0; //ī���� �ٽ� ����ϰ� 0���� ����
		}
		if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
		{
			PostMessage(_hWnd, WM_DESTROY, 0, 0); //ESC�Է½� ���� ������ ó��
		}
	}

	//���° ������ 
	if (SecondPhase)
	{
		if (counter < 18) //�ڽ��� ���ư��°� ������ ���� �������϶�
		{
			//�庹���ڵ�
			if (titleAlpha != 105) titleAlpha -= 15;
			if (pip1->getX() >= -pip1->getWidth()) pip1->setX(pip1->getX() - 20); //320�̵�
			if (pip2->getX() < WINSIZEX) pip2->setX(pip2->getX() + 20); //320�̵�
			if (pip3->getY() < WINSIZEY) pip3->setY(pip3->getY() + 26); //408 �̵�
			if (titlelogo->getY() >= -titlelogo->getHeight()) titlelogo->setY(titlelogo->getY() - 18); //284 �̵�
			if (esc->getY() < WINSIZEY) esc->setY(esc->getY() + 15); //128 �̵�
			if (enter->getY() < WINSIZEY) enter->setY(enter->getY() + 15); //148�̵� 

			//����� �ڵ�
			if (fileSelect->getY() <= 38) fileSelect->setY(fileSelect->getY() + 34); //540�̵�
			else if (fileSelect->getY() > 38) fileSelect->setY(38); //540�̵�
			if (ESC_YSetting->getY() > 640) ESC_YSetting->setY(ESC_YSetting->getY() - 8); //128 �̵�
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

				counter = 0; //ī���� 0���� ������ ��Ȱ��
				SecondPhase = false; //2�ܰ� ������ �������� �ٽ� ù°������� ���ư�

			}
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				if (selection->getX() != WINSIZEX / 2 - fileSelect->getWidth() / 2)
				{
					selection->setX(selection->getX() - 333);
				}

			}
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				if (selection->getX() != WINSIZEX / 2 - fileSelect->getWidth() / 2 + 666)
				{
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

		if (fileSelect->getY() >= -fileSelect->getHeight()) fileSelect->setY(fileSelect->getY() - 55); //540�̵�
		if (ESC_YSetting->getY() < WINSIZEY) ESC_YSetting->setY(ESC_YSetting->getY() + 15); //128 �̵�
		selection->setY(fileSelect->getY() + 150);
		saveSlot1Pos = { fileSelect->getX() + 91 , fileSelect->getY() + 205 };
		saveSlot2Pos = { fileSelect->getX() + 425 , fileSelect->getY() + 205 };
		saveSlot3Pos = { fileSelect->getX() + 759 , fileSelect->getY() + 205 };




		if (titleAlpha<=0)
		{
			if (selection->getX() < fileSelect->getX() + 10)
			{
				TXTDATA.setWhichSavefile("saveSlot1.txt");
				SCENEMANAGER->loadScene("BossStage");
			}
			else if (selection->getX() < fileSelect->getX() + 355)
			{
				TXTDATA.setWhichSavefile("saveSlot2.txt");
				SCENEMANAGER->loadScene("Stage1");
			}
			else if (selection->getX() < fileSelect->getX() + 355+343)
			{
				TXTDATA.setWhichSavefile("saveSlot3.txt");
				SCENEMANAGER->loadScene("WorldMap");
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
	TIMEMANAGER->render(getMemDC());
}
