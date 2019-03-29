#include "stdafx.h"
#include "VillageClass.h"
#include "PlayerClass.h"
#include "UIClass.h"

//=============초기화=============
HRESULT VillageClass::init(void)
{
	SOUNDMANAGER->play("마을", TXTDATA.refBGMSound());
	villageImg = IMAGEMANAGER->findImage("Village");
	villageBgImg = IMAGEMANAGER->findImage("Village 배경");

	merchantHiImg = IMAGEMANAGER->findImage("이펙트-말풍선");
	merchantImg = IMAGEMANAGER->findImage("NPC-상인");
	merchantRc = RectMakeCenter(1791, 665, 128, 132);
	imgVCount = 0;
	frameVX = 0;

	isMeet = false;

	vEmpty = { 0 };

	//플레이어 클래스 생성 및 초기화
	vPlayerPtr = new PlayerClass;
	vPlayerPtr->init(1594, 400, "VillageCollision");

	//UI 클래스 생성 및 초기화
	vUIPtr = new UIClass;
	vUIPtr->init("");

	return S_OK;
}
//=============해제=============
void VillageClass::release(void)
{
	//플레이어 클래스 해제
	vPlayerPtr->release();
	SAFE_DELETE(vPlayerPtr);

	//UI 클래스 해제
	vUIPtr->release();
	SAFE_DELETE(vUIPtr);
}
//=============업데이트=============
void VillageClass::update(void)
{
	loopX++;

	//플레이어 클래스 업데이트
	if (vUIPtr->getIsShop() == false) vPlayerPtr->update();

	//UI 클래스 업데이트
	vUIPtr->update();

	//상인과 만나면 말풍선이 나오고 그 상태에서 상점으로 들어감
	if (IntersectRect(&vEmpty, &vPlayerPtr->getRect(), &merchantRc)) isMeet = true;
	else isMeet = false;

	if (KEYMANAGER->isOnceKeyDown('M') && vUIPtr->getIsShop() == false)
	{
		vector<string> tempVec;
		char tempStr[50];

		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->pipMaxHP, tempStr, 10));
		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->pipRescued, tempStr, 10));
		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->pipMoney, tempStr, 10));
		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->pipCinematic, tempStr, 10));
		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->isFindSealS1, tempStr, 10));
		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->isFindBatS1, tempStr, 10));
		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->isFindSharkS1, tempStr, 10));
		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->isFindSealB, tempStr, 10));
		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->isFindBatB, tempStr, 10));
		tempVec.push_back(itoa(TXTDATA.getCurrentPipData()->isFindSharkB, tempStr, 10));
		tempVec.push_back(TXTDATA.getCurrentPipData()->firstItem);
		tempVec.push_back(TXTDATA.getCurrentPipData()->secondItem);
		tempVec.push_back(TXTDATA.getCurrentPipData()->thirdItem);

		TXTDATA.txtSave(TXTDATA.getWhichfile(), tempVec);


		SOUNDMANAGER->pause("마을");
		SCENEMANAGER->loadScene("WorldMap");
	}

	//상인에게서 아이템 사려고 말을 걸음
	if (KEYMANAGER->isStayKeyDown('J') && isMeet == true)
	{
		vUIPtr->setIsShop(true);
	}


	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE) && vUIPtr->getIsShop() == true)
	{
		vUIPtr->setSelectX(582);
		vUIPtr->setSelectY(227);
		vUIPtr->setIsShop(false);
	}




	//상인 애니메이션
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

	if (isMeet == true) merchantHiImg->render(getMemDC(), 1798 - CAMERA.getCRc().left, 549 - CAMERA.getCRc().top);
	merchantImg->frameRender(getMemDC(), merchantRc.left - CAMERA.getCRc().left, merchantRc.top - CAMERA.getCRc().top, frameVX, 0);

	//플레이어 렌더
	vPlayerPtr->render();

	//UI 렌더
	vUIPtr->render();

	/*좌표 확인용*/
	//SetBkMode(getMemDC(), TRANSPARENT);
	//TextOutfloat(getMemDC(), 10, 10, "마우스 X", _ptMouse.x + CAMERA.getCRc().left);
	//TextOutfloat(getMemDC(), 10, 30, "마우스 Y", _ptMouse.y + CAMERA.getCRc().top);
	//TextOutfloat(getMemDC(), 10, 50, "카메라 left", CAMERA.getCRc().left);
}
