#include "stdafx.h"
#include "PetsClass.h"

//=============�ʱ�ȭ=============
HRESULT PetsClass::init(int _whichPet, float _petX, float _petY)
{
	whichPet = _whichPet;

	switch (whichPet)
	{
	case bat:
		petImage = IMAGEMANAGER->findImage("pets-����");
		break;

	case seal:
		petImage = IMAGEMANAGER->findImage("pets-����");
		break;

	case shark:
		petImage = IMAGEMANAGER->findImage("pets-���");
		break;
	}

	petX = _petX;
	petY = _petY;
	petSpeed = 0;
	isPetRight = true;
	isPetCatch = false;

	petImgCount = 0;
	frameX = 0;
	frameY = 0;


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
		case bat:
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

		case seal:
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

		case shark:
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
		case bat:
			petRc = RectMakeCenter(petX, petY, 84, 48);
			break;

		case seal:
			petRc = RectMakeCenter(petX, petY, 80, 65);
			break;

		case shark:
			petRc = RectMakeCenter(petX, petY, 80, 52);
			break;
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
		petImage->frameRender(getMemDC(), petRc.left - CAMERA.getCRc().left, petRc.top - CAMERA.getCRc().top, frameX, frameY);
	}
	
}
