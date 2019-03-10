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

	//초기 위치 조정
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
	//new 해준것이 없으므로 릴리즈 없음
}

void TitleClass::update(void)
{
	counter++;

	//▼첫째 페이즈 화면 불러오는부분
	if (SecondPhase == false && counter < 17)
	{
		if (titleAlpha != 255) titleAlpha += 15;
		if (pip1->getX() <= 80) pip1->setX(pip1->getX() + 20); //320이동
		if (pip2->getX() > 1046) pip2->setX(pip2->getX() - 20); //320이동
		if (pip3->getY() > 360) pip3->setY(pip3->getY() - 26); //408 이동
		if (titlelogo->getY() <= 30) titlelogo->setY(titlelogo->getY() + 18); //284 이동
		if (esc->getY() > 640) esc->setY(esc->getY() - 15); //128 이동
		if (enter->getY() > 620) enter->setY(enter->getY() - 15); //148이동 
	}

	//▼첫째 페이즈 이미지들 이동이 끝난 후부터 키입력부분
	if (SecondPhase==false && counter > 18) //모션이동은 16프레임만에 끝난다. 모션 끝 이후부터 엔터 입력받을수 있게 처리
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
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
		if (counter < 17) //박스들 돌아가는거 스르륵 아직 진행중일때
		{
			if (titleAlpha != 105) titleAlpha -= 15;
			if (pip1->getX() >= -pip1->getWidth()) pip1->setX(pip1->getX() - 20); //320이동
			if (pip2->getX() < WINSIZEX) pip2->setX(pip2->getX() + 20); //320이동
			if (pip3->getY() < WINSIZEY) pip3->setY(pip3->getY() + 26); //408 이동
			if (titlelogo->getY() >= -titlelogo->getHeight()) titlelogo->setY(titlelogo->getY() - 18); //284 이동
			if (esc->getY() < WINSIZEY) esc->setY(esc->getY() + 15); //128 이동
			if (enter->getY() < WINSIZEY) enter->setY(enter->getY() + 15); //148이동 
		}
		else if(counter >=17 && counter <35)
		{

		}
		else if(counter>=35)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
			{
				counter = 0; //카운터 0으로 돌려서 재활용
				SecondPhase = false; //2단계 페이즈 꺼버리면 다시 첫째페이즈로 돌아감
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
