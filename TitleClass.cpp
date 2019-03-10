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

	//�ʱ� ��ġ ����
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

	counter = 0;
	SecondPhase = false;
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
	if (SecondPhase == false && counter < 17)
	{
		if (titleAlpha != 255) titleAlpha += 15;
		if (pip1->getX() <= 80) pip1->setX(pip1->getX() + 20); //320�̵�
		if (pip2->getX() > 1046) pip2->setX(pip2->getX() - 20); //320�̵�
		if (pip3->getY() > 360) pip3->setY(pip3->getY() - 26); //408 �̵�
		if (titlelogo->getY() <= 30) titlelogo->setY(titlelogo->getY() + 18); //284 �̵�
		if (esc->getY() > 640) esc->setY(esc->getY() - 15); //128 �̵�
		if (enter->getY() > 620) enter->setY(enter->getY() - 15); //148�̵� 
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
		if (counter < 17) //�ڽ��� ���ư��°� ������ ���� �������϶�
		{
			if (titleAlpha != 105) titleAlpha -= 15;
			if (pip1->getX() >= -pip1->getWidth()) pip1->setX(pip1->getX() - 20); //320�̵�
			if (pip2->getX() < WINSIZEX) pip2->setX(pip2->getX() + 20); //320�̵�
			if (pip3->getY() < WINSIZEY) pip3->setY(pip3->getY() + 26); //408 �̵�
			if (titlelogo->getY() >= -titlelogo->getHeight()) titlelogo->setY(titlelogo->getY() - 18); //284 �̵�
			if (esc->getY() < WINSIZEY) esc->setY(esc->getY() + 15); //128 �̵�
			if (enter->getY() < WINSIZEY) enter->setY(enter->getY() + 15); //148�̵� 
		}
		else if(counter >=17 && counter <35)
		{

		}
		else if(counter>=35)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
			{
				counter = 0; //ī���� 0���� ������ ��Ȱ��
				SecondPhase = false; //2�ܰ� ������ �������� �ٽ� ù°������� ���ư�
			}


		}


	}



}

void TitleClass::render(void)
{

		titlebg->alphaRender(getMemDC(), titleAlpha);
		pip1->render(getMemDC(), pip1->getX(), pip1->getY());
		pip2->render(getMemDC(), pip2->getX(), pip2->getY());
		pip3->render(getMemDC(), pip3->getX(), pip3->getY());
		titlelogo->render(getMemDC(), titlelogo->getX(), titlelogo->getY());
		esc->render(getMemDC(), esc->getX(), esc->getY());
		enter->render(getMemDC(), enter->getX(), enter->getY());

}
