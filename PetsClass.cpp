#include "stdafx.h"
#include "PetsClass.h"

//=============초기화=============
HRESULT PetsClass::init(PetsTypes _whichPet, float _petX, float _petY, bool _isFind)
{
	whichPet = _whichPet;

	switch (whichPet)
	{
	case PetsTypes::seal:
		petImg = IMAGEMANAGER->findImage("pets-물개");
		break;

	case PetsTypes::bat:
		petImg = IMAGEMANAGER->findImage("pets-박쥐");
		break;

	case PetsTypes::shark:
		petImg = IMAGEMANAGER->findImage("pets-상어");
		break;
	}

	petX = _petX;
	petY = _petY;
	petSpeed = 0;
	isPetRight = true;
	isPetFind = _isFind;
	isPetCatch = _isFind;

	petImgCount = 0;
	frameX = 0;
	frameY = 0;

	petHeartImg = IMAGEMANAGER->findImage("펫 하트");
	petHImgCount = 0;
	frameHX = 0;

	return S_OK;
}

//=============해제=============
void PetsClass::release(void)
{
}

//=============업데이트=============
void PetsClass::update(void)
{

	if (isPetCatch == false)
	{
		//이미지 프레임
		if (isPetRight == true)
		{
			frameY = 0;
		}
		else if (isPetRight == false)
		{
			frameY = 1;
		}

		petImgCount++;

		switch (whichPet)
		{
		case PetsTypes::seal:
			if (petImgCount % 5 == 0)
			{
				frameX++;
				if (isPetRight == true)
				{
					if (frameX > 11)
					{
						frameX = 0;
					}
				}
				else
				{
					if (frameX < 0)
					{
						frameX = 11;
					}
				}
			}
			break;

		case PetsTypes::bat:
			if (petImgCount % 5 == 0)
			{
				frameX++;
				if (isPetRight == true)
				{
					if (frameX > 9)
					{
						frameX = 0;
					}
				}
				else
				{
					if (frameX < 0)
					{
						frameX = 9;
					}
				}
			}
			break;

		case PetsTypes::shark:
			if (petImgCount % 10 == 0)
			{
				frameX++;
				if (isPetRight == true)
				{
					if (frameX > 3)
					{
						frameX = 0;
					}
				}
				else
				{
					if (frameX < 0)
					{
						frameX = 3;
					}
				}
			}
			break;
		}

		switch (whichPet)
		{
		case PetsTypes::seal:
			petRc = RectMakeCenter(petX, petY, 80, 65);
			break;

		case PetsTypes::bat:
			petRc = RectMakeCenter(petX, petY, 84, 48);
			break;

		case PetsTypes::shark:
			petRc = RectMakeCenter(petX, petY, 80, 52);
			break;
		}
	}

	if (isPetFind == true && isPetCatch == false)
	{
		//펫 하트 프레임
		petHImgCount++;
		if (petHImgCount % 5 == 0)
		{
			frameHX++;
			if (frameHX > 4)
			{
				frameHX = 0;
			}
		}

		if (petHImgCount % 120 == 0)
		{
			isPetCatch = true;
			isPetFind = false;
		}
	}

}

//=============렌더=============
void PetsClass::render(void)
{
	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), RelativeCameraRect(petRc));
	}

	if (isPetCatch == false)
	{
		petImg->frameRender(getMemDC(), petRc.left - CAMERA.getCRc().left, petRc.top - CAMERA.getCRc().top, frameX, frameY);
	}

	if (isPetFind == true && isPetCatch == false)
	{
		petHeartImg->frameRender(getMemDC(), petX - CAMERA.getCRc().left, petY - 80 - CAMERA.getCRc().top, frameHX, 0);
	}

}
