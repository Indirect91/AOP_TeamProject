#include "stdafx.h"
#include "UIClass.h"

HRESULT UIClass::init()
{
	moneyBar = IMAGEMANAGER->findImage("�� ǥ�� ��ġ");
	moneyBar->setX(1062);
	moneyBar->setY(48);

	return S_OK;
}

void UIClass::release()
{
}

void UIClass::update()
{
	
}

void UIClass::render()
{
	moneyBar->render(getMemDC(), moneyBar->getX(),moneyBar->getY());
}
