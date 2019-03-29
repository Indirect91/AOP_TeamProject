#include "stdafx.h"
#include "CinematicClass.h"

HRESULT CinematicClass::init(void)
{
	//���ѷα�
	prologueImg[0] = IMAGEMANAGER->findImage("��1");
	prologueImg[1] = IMAGEMANAGER->findImage("��2");
	prologueImg[2] = IMAGEMANAGER->findImage("��3");
	prologueImg[3] = IMAGEMANAGER->findImage("��4");
	prologueImg[4] = IMAGEMANAGER->findImage("��5");
	prologueImg[5] = IMAGEMANAGER->findImage("��6");
	prologueImg[6] = IMAGEMANAGER->findImage("��7");
	prologueImg[7] = IMAGEMANAGER->findImage("��8");
	prologueImg[8] = IMAGEMANAGER->findImage("��9");
	//���ʷα�
	epilogueImg[0] = IMAGEMANAGER->findImage("��10");
	epilogueImg[1] = IMAGEMANAGER->findImage("��11");

	//��ȯ
	curtainImg = IMAGEMANAGER->findImage("Ŀư��");
	curtainY = 0;									//Ŀư�� Y��ǥ

	cinemaCount = 0;								//�ð���
	alpha[0] = 255;									
	for (int i = 1; i < 9; i++)
	{
		alpha[i] = 0;
	}
	
	cinemaStart = false;							//

	isWatch = false;

	firstAlpha = 255.f; //ù ���� ���İ�
	firstRising = false;

	secondAlpha = 0.f;  //��°���� ���İ�
	secondRising = true;

	firstBuffer = IMAGEMANAGER->findImage("��1");
	secondBuffer = IMAGEMANAGER->findImage("��2");
	cineEnd = false;


	//���ѷα� ���
	isP1 = true;
	isP2 = false;
	isP3 = false;
	isP4 = false;
	isP5 = false;
	isP6 = false;
	isP7 = false;
	isP8 = false;
	isP9 = false;
	//���ʷα� ���
	isE1 = false;
	isE2 = false;
	
	SOUNDMANAGER->play("�ó׸�ƽ", TXTDATA.refBGMSound());

	return S_OK;
}

void CinematicClass::release(void)
{
}

void CinematicClass::update(void)
{

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		cinemaStart = true;
	}

	if (cinemaStart == true)
	{
		isWatch = true;
		cinemaCount++;
	}

	//����
	if (isWatch == true)
	{
		curtainY -= 20;
		if (curtainY< -curtainImg->getHeight() && cinemaCount > 180)
		{
			curtainY = -curtainImg->getHeight();
			
		}
	}




	if (cineEnd == false && curtainY == -curtainImg->getHeight())
	{
		if (firstAlpha < 255 && firstRising)
			firstAlpha += 1.25f;
		else if (firstAlpha >= 255 && firstRising)
		{
			firstAlpha = 255;
			Sleep(2000);
			firstRising = false;
		}
		else if (firstAlpha > 0 && firstRising == false)
			firstAlpha -= 1.25f;
		else if (firstAlpha <= 0 && firstRising == false)
		{
			firstAlpha = 0;
			if (firstBuffer == IMAGEMANAGER->findImage("��1"))
			{
				firstBuffer = IMAGEMANAGER->findImage("��3");
			}
			else if (firstBuffer == IMAGEMANAGER->findImage("��3"))
			{
				firstBuffer = IMAGEMANAGER->findImage("��5");
			}
			else if (firstBuffer == IMAGEMANAGER->findImage("��5"))
			{
				firstBuffer = IMAGEMANAGER->findImage("��7");
			}
			else if (firstBuffer == IMAGEMANAGER->findImage("��7"))
			{
				firstBuffer = IMAGEMANAGER->findImage("��9");
			}

			firstRising = true;
		}

		if (secondAlpha < 255 && secondRising)
			secondAlpha += 1.25f;
		else if (secondAlpha >= 255 && secondRising)
		{
			secondAlpha = 255;
			Sleep(3000);
			secondRising = false;
		}
		else if (secondAlpha > 0 && secondRising == false)
			secondAlpha -= 1.25f;
		else if (secondAlpha <= 0 && secondRising == false)
		{
			secondAlpha = 0;
			if (secondBuffer == IMAGEMANAGER->findImage("��2"))
			{
				secondBuffer = IMAGEMANAGER->findImage("��4");
			}
			else if (secondBuffer == IMAGEMANAGER->findImage("��4"))
			{
				secondBuffer = IMAGEMANAGER->findImage("��6");
			}
			else if (secondBuffer == IMAGEMANAGER->findImage("��6"))
			{
				secondBuffer = IMAGEMANAGER->findImage("��8");
			}

			secondRising = true;
		}
	}

	else if(cineEnd == true)
	{
		if (firstAlpha >= 0)
		{
			firstAlpha -= 5.f;
			secondAlpha -= 5.f;
		}
	}


	if (firstBuffer == IMAGEMANAGER->findImage("��9") && firstAlpha<=255.f/2.f)
	{
		cineEnd = true;
		//���� ���̿� �ڵ���Ź
		SOUNDMANAGER->pause("�ó׸�ƽ");
		SCENEMANAGER->loadScene("WorldMap");
	}

	

}

void CinematicClass::render(void)
{
	firstBuffer->alphaRender(getMemDC(), firstAlpha);
	secondBuffer->alphaRender(getMemDC(), secondAlpha);

	curtainImg->render(getMemDC(), 0, curtainY);

	//TextOutInt(getMemDC(), 10, 10, "Ŀưy", curtainY);
	//TextOutInt(getMemDC(), 10, 30, "ī��Ʈ", cinemaCount);
	//TextOutInt(getMemDC(), 10, 50, "����", alpha[0]);
}
