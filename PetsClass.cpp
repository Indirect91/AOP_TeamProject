#include "stdafx.h"
#include "PetsClass.h"

//=============�ʱ�ȭ=============
HRESULT PetsClass::init(PetsTypes _whichPet, float _petX, float _petY, bool _isFind)
{
	whichPet = _whichPet;

	switch (whichPet)
	{
	case PetsTypes::seal:
		petImg = IMAGEMANAGER->findImage("pets-����");
		break;

	case PetsTypes::bat:
		petImg = IMAGEMANAGER->findImage("pets-����");
		break;

	case PetsTypes::shark:
		petImg = IMAGEMANAGER->findImage("pets-���");
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

	petHeartImg = IMAGEMANAGER->findImage("�� ��Ʈ");
	petHImgCount = 0;
	frameHX = 0;

	return S_OK;
}

//=============����=============
void PetsClass::release(void)
{
}

//=============������Ʈ=============
void PetsClass::update(void)
{

	if (isPetCatch == false)
	{
		//�̹��� ������
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
		//�� ��Ʈ ������
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

//=============����=============
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
