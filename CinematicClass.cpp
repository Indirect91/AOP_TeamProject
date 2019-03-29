#include "stdafx.h"
#include "CinematicClass.h"

HRESULT CinematicClass::init(void)
{
	//ÇÁ·Ñ·Î±×
	prologueImg[0] = IMAGEMANAGER->findImage("¾À1");
	prologueImg[1] = IMAGEMANAGER->findImage("¾À2");
	prologueImg[2] = IMAGEMANAGER->findImage("¾À3");
	prologueImg[3] = IMAGEMANAGER->findImage("¾À4");
	prologueImg[4] = IMAGEMANAGER->findImage("¾À5");
	prologueImg[5] = IMAGEMANAGER->findImage("¾À6");
	prologueImg[6] = IMAGEMANAGER->findImage("¾À7");
	prologueImg[7] = IMAGEMANAGER->findImage("¾À8");
	prologueImg[8] = IMAGEMANAGER->findImage("¾À9");
	//¿¡ÇÊ·Î±×
	epilogueImg[0] = IMAGEMANAGER->findImage("¾À10");
	epilogueImg[1] = IMAGEMANAGER->findImage("¾À11");

	//ÀüÈ¯
	curtainImg = IMAGEMANAGER->findImage("Ä¿Æ°ÄÝ");
	curtainY = 0;									//Ä¿Æ°ÀÇ YÁÂÇ¥

	cinemaCount = 0;								//½Ã°£ÃÊ
	alpha[0] = 255;									
	for (int i = 1; i < 9; i++)
	{
		alpha[i] = 0;
	}
	
	cinemaStart = false;							//

	isWatch = false;

	firstAlpha = 255.f; //Ã¹ ¹öÆÛ ¾ËÆÄ°ª
	firstRising = false;

	secondAlpha = 0.f;  //µÑÂ°¹öÆÛ ¾ËÆÄ°ª
	secondRising = true;

	firstBuffer = IMAGEMANAGER->findImage("¾À1");
	secondBuffer = IMAGEMANAGER->findImage("¾À2");
	cineEnd = false;


	//ÇÁ·Ñ·Î±× Àå¸é
	isP1 = true;
	isP2 = false;
	isP3 = false;
	isP4 = false;
	isP5 = false;
	isP6 = false;
	isP7 = false;
	isP8 = false;
	isP9 = false;
	//¿¡ÇÊ·Î±× Àå¸é
	isE1 = false;
	isE2 = false;
	
	SOUNDMANAGER->play("½Ã³×¸¶Æ½", TXTDATA.refBGMSound());

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

	//½ÃÀÛ
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
			if (firstBuffer == IMAGEMANAGER->findImage("¾À1"))
			{
				firstBuffer = IMAGEMANAGER->findImage("¾À3");
			}
			else if (firstBuffer == IMAGEMANAGER->findImage("¾À3"))
			{
				firstBuffer = IMAGEMANAGER->findImage("¾À5");
			}
			else if (firstBuffer == IMAGEMANAGER->findImage("¾À5"))
			{
				firstBuffer = IMAGEMANAGER->findImage("¾À7");
			}
			else if (firstBuffer == IMAGEMANAGER->findImage("¾À7"))
			{
				firstBuffer = IMAGEMANAGER->findImage("¾À9");
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
			if (secondBuffer == IMAGEMANAGER->findImage("¾À2"))
			{
				secondBuffer = IMAGEMANAGER->findImage("¾À4");
			}
			else if (secondBuffer == IMAGEMANAGER->findImage("¾À4"))
			{
				secondBuffer = IMAGEMANAGER->findImage("¾À6");
			}
			else if (secondBuffer == IMAGEMANAGER->findImage("¾À6"))
			{
				secondBuffer = IMAGEMANAGER->findImage("¾À8");
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


	if (firstBuffer == IMAGEMANAGER->findImage("¾À9") && firstAlpha<=255.f/2.f)
	{
		cineEnd = true;
		//¿©±â »çÀÌ¿¡ ÄÚµùºÎÅ¹
		SOUNDMANAGER->pause("½Ã³×¸¶Æ½");
		SCENEMANAGER->loadScene("WorldMap");
	}

	

}

void CinematicClass::render(void)
{
	firstBuffer->alphaRender(getMemDC(), firstAlpha);
	secondBuffer->alphaRender(getMemDC(), secondAlpha);

	curtainImg->render(getMemDC(), 0, curtainY);

	//TextOutInt(getMemDC(), 10, 10, "Ä¿Æ°y", curtainY);
	//TextOutInt(getMemDC(), 10, 30, "Ä«¿îÆ®", cinemaCount);
	//TextOutInt(getMemDC(), 10, 50, "¾ËÆÄ", alpha[0]);
}
