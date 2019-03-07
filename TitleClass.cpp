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

	//초기 위치 조정
	pip1->setX(0);
	pip1->setY(WINSIZEY / 2);

	pip2->setX(WINSIZEX);
	pip2->setY(WINSIZEY / 2);

	pip3->setX(WINSIZEX / 2 - pip3->getWidth() / 2 + 70);
	pip3->setY(WINSIZEY);

	titlelogo->setX(WINSIZEX / 2 - 300);
	titlelogo->setY(0);



	return S_OK;
}

void TitleClass::release(void)
{
	//new 해준것이 없으므로 릴리즈 없음
}

void TitleClass::update(void)
{
	if (pip1->getX() <= 400) pip1->setX(pip1->getX() + 15);
	if (pip2->getX() > 800) pip2->setX(pip2->getX() - 15);
	if (pip3->getY() > 320) pip3->setY(pip3->getY() - 15);
	if (titlelogo->getY() <= 80) titlelogo->setY(titlelogo->getY() + 5);

}

void TitleClass::render(void)
{
	titlebg->render(getMemDC());
	pip1->render(getMemDC(), pip1->getX(), pip1->getY());
	pip2->render(getMemDC(), pip2->getX(), pip2->getY());
	pip3->render(getMemDC(), pip3->getX(), pip3->getY());
	titlelogo->render(getMemDC(), titlelogo->getX(), titlelogo->getY());
}
