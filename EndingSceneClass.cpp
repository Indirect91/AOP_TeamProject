#include "stdafx.h"
#include "EndingSceneClass.h"

HRESULT EndingSceneClass::init(void)
{
	firstImage = IMAGEMANAGER->findImage("��10");
	secondImage = IMAGEMANAGER->findImage("��11");

	curtain = IMAGEMANAGER->findImage("Ŀư��");
	curtainY = -IMAGEMANAGER->findImage("Ŀư��")->getHeight();

	alpha1 = 255;
	alpha2 = 0;
	firstDone = false;
	secondDone = false;
	SOUNDMANAGER->play("�ó׸�ƽ");
	return S_OK;
}

void EndingSceneClass::release(void)
{
}

void EndingSceneClass::update(void)
{

	if (!firstDone)
	{
		if (alpha1 > 0)
			alpha1 -= 1.25f;
		else if (alpha1 <= 0)
		{
			alpha1 = 0;
			firstDone = true;
		}
	}
	else if (!secondDone && firstDone)
	{
		if (alpha2 <= 255)
			alpha2 += 1.25f;
		else if (alpha2 > 255)
		{
			alpha2 = 255;
			secondDone = true;
		}
	}
	else
	{
		if (curtainY < 0)
			curtainY += 20.f;
		else if (curtainY >= 0)
		{
			curtainY = 0;
			Sleep(1000);
			SOUNDMANAGER->pause("�ó׸�ƽ");
			SCENEMANAGER->loadScene("Title");
		}
	}
}

void EndingSceneClass::render(void)
{
	firstImage->alphaRender(getMemDC(), alpha1);
	secondImage->alphaRender(getMemDC(), alpha2);
	curtain->render(getMemDC(), 0, curtainY);

}
