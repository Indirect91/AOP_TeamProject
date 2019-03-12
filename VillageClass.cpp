#include "stdafx.h"
#include "VillageClass.h"
#include "PlayerClass.h"

//=============초기화=============
HRESULT VillageClass::init(void)
{
	villageImg = IMAGEMANAGER->findImage("Village");
	villageBgImg = IMAGEMANAGER->findImage("Village 배경");

	merchantImg = IMAGEMANAGER->findImage("NPC-상인");
	merchantRc = RectMakeCenter(1791, 665, 128, 132);
	imgVCount = 0;
	frameVX = 0;

	vPlayerPtr = new PlayerClass;
	vPlayerPtr->init(WINSIZEX / 2, 400, "VillageCollision");


	return S_OK;
}
//=============해제=============
void VillageClass::release(void)
{
	vPlayerPtr->release();
	SAFE_DELETE(vPlayerPtr);
}
//=============업데이트=============
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

	//카메라 앵글을 플레이어에게 줌
	CAMERA.cameraFollow(vPlayerPtr->getX(), vPlayerPtr->getY());

	//구도 잡기
	CAMERA.cameraRevision(0, 0, 2750, 768);
}
//=============렌더=============
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

	/*좌표 확인용*/
	SetBkMode(getMemDC(), TRANSPARENT);
	TextOutfloat(getMemDC(), 10, 10, "마우스 X", _ptMouse.x + CAMERA.getCRc().left);
	TextOutfloat(getMemDC(), 10, 30, "마우스 Y", _ptMouse.y + CAMERA.getCRc().top);
	TextOutfloat(getMemDC(), 10, 50, "카메라 left", CAMERA.getCRc().left);
}
