#include "stdafx.h"
#include "VillageClass.h"
#include "PlayerClass.h"

//=============�ʱ�ȭ=============
HRESULT VillageClass::init(void)
{
	villageImg = IMAGEMANAGER->findImage("Village");
	villageBgImg = IMAGEMANAGER->findImage("Village ���");

	merchantImg = IMAGEMANAGER->findImage("NPC-����");
	merchantRc = RectMakeCenter(1791, 665, 128, 132);
	imgVCount = 0;
	frameVX = 0;

	vPlayerPtr = new PlayerClass;
	vPlayerPtr->init(WINSIZEX / 2, 400, "VillageCollision");


	return S_OK;
}
//=============����=============
void VillageClass::release(void)
{
	vPlayerPtr->release();
	SAFE_DELETE(vPlayerPtr);
}
//=============������Ʈ=============
void VillageClass::update(void)
{
	loopX++;

	vPlayerPtr->update();

	imgVCount++;
	if (imgVCount % 7 == 0)
	{
		frameVX++;
		if (frameVX > 11)
		{
			frameVX = 0;
		}
	}

	//ī�޶� �ޱ��� �÷��̾�� ��
	CAMERA.cameraFollow(vPlayerPtr->getX(), vPlayerPtr->getY());

	//���� ���
	CAMERA.cameraRevision(0, 0, 2750, 768);
}
//=============����=============
void VillageClass::render(void)
{
	RECT bgRc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	villageBgImg->loopRender(getMemDC(), &bgRc, loopX, 0);

	villageImg->render(getMemDC(), 0, 0, CAMERA.getCRc().left, CAMERA.getCRc().top, WINSIZEX, WINSIZEY);

	if (KEYMANAGER->isToggleKey('T'))
	{
		Rectangle(getMemDC(), RelativeCameraRect(merchantRc));
	}
	merchantImg->frameRender(getMemDC(), merchantRc.left - CAMERA.getCRc().left, merchantRc.top - CAMERA.getCRc().top, frameVX, 0);

	vPlayerPtr->render();

	/*��ǥ Ȯ�ο�*/
	SetBkMode(getMemDC(), TRANSPARENT);
	TextOutfloat(getMemDC(), 10, 10, "���콺 X", _ptMouse.x + CAMERA.getCRc().left);
	TextOutfloat(getMemDC(), 10, 30, "���콺 Y", _ptMouse.y + CAMERA.getCRc().top);
	TextOutfloat(getMemDC(), 10, 50, "ī�޶� left", CAMERA.getCRc().left);
}
